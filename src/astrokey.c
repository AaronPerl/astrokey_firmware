//-----------------------------------------------------------------------------
// astrokey.c
//-----------------------------------------------------------------------------
// Copyright 2018 AstroKey
// https://github.com/AstroKey/astrokey_firmware/blob/master/LICENSE
//
// File Description:
//
// Implementation of AstroKey input polling and other device-specific functionality.
//

#include "astrokey.h"
#include "InitDevice.h"
#include "efm8_usb.h"
#include "descriptors.h"
#include "idle.h"
#include "delay.h"
#include "flash.h"
#include "leds.h"

// ----------------------------------------------------------------------------
// Variables
// ----------------------------------------------------------------------------
// Number of keys currently being pressed by the workflow
uint8_t keysPressed = 0;
// The current report to send the
volatile KeyReport_TypeDef SI_SEG_XDATA keyReport =
{
  0,
  0,
  {0, 0, 0, 0, 0, 0}
};

volatile bool keyReportSent = false;
volatile int8_t workflowUpdated = -1;

// The current action being run
Action_TypeDef curAction;

// Index of current workflow running (i.e. 0 for 1st key, etc.)
uint8_t workflowIndex = NO_WORKFLOW;

// Index of current action in current workflow running;
uint8_t actionIndices[NUM_SWITCHES] = {0};

// Current device layer
uint8_t layer = 0;

// Layer of the current workflow being run
uint8_t workflowLayer;

// Previous states of layer buttons
bool b0Prev = false;
bool b1Prev = false;

// Checks if a key is currently pressed by the workflow
// Returns the index of the key in array of keys currently pressed,
// -1 if the key is not currently being pressed
int8_t keyIsPressed(uint8_t key)
{
  uint8_t i;
  for (i = 0; i < WORKFLOW_MAX_KEYS; i++)
  {
    if (keyReport.keys[i] == key)
      return i;
  }
  return -1;
}

// Presses down a key
void pressKey(uint8_t key)
{
  if (keyIsPressed(key) == -1 && keysPressed < WORKFLOW_MAX_KEYS)
  {
    keyReport.keys[keysPressed] = key;
    keysPressed++;
  }
  // Switch case seems to use 1 more byte of code than cascaded if else ifs with many conditions,
  // but runs faster
  switch (key)
  {
    case USAGE_LEFTCTRL:
      keyReport.modifiers |= MODIFIER_LEFTCTRL;
      break;
    case USAGE_LEFTSHIFT:
      keyReport.modifiers |= MODIFIER_LEFTSHIFT;
      break;
    case USAGE_LEFTALT:
      keyReport.modifiers |= MODIFIER_LEFTALT;
      break;
    case USAGE_LEFTGUI:
      keyReport.modifiers |= MODIFIER_LEFTGUI;
      break;
  }
}

// Releases a key currently being pressed
void releaseKey(uint8_t key)
{
  uint8_t keyIndex;
  if ((keyIndex = keyIsPressed(key)) != -1)
  {
    // Switch last key pressed to position of key being released
    keyReport.keys[keyIndex] = keyReport.keys[keysPressed - 1];
    // Release last key
    keyReport.keys[keysPressed - 1] = 0;
    keysPressed--;
  }
  switch (key)
  {
    case USAGE_LEFTCTRL:
      keyReport.modifiers &= ~MODIFIER_LEFTCTRL;
      break;
    case USAGE_LEFTSHIFT:
      keyReport.modifiers &= ~MODIFIER_LEFTSHIFT;
      break;
    case USAGE_LEFTALT:
      keyReport.modifiers &= ~MODIFIER_LEFTALT;
      break;
    case USAGE_LEFTGUI:
      keyReport.modifiers &= ~MODIFIER_LEFTGUI;
      break;
  }
}

bool curPressDown = false;
bool delayStarted = false;
uint32_t SI_SEG_XDATA delayStartTime;

// Advances the workflow one action forward, ending it if the end is reached
void stepWorkflow()
{
  IE_EA = 0;
  loadWorkflowAction(&curAction, workflowLayer, workflowIndex, actionIndices[workflowIndex]);
  IE_EA = 1;
  switch (curAction.actionType)
  {
    case WORKFLOW_ACTION_DOWN:
      pressKey(curAction.value);
      actionIndices[workflowIndex]++;
      break;
    case WORKFLOW_ACTION_UP:
      releaseKey(curAction.value);
      actionIndices[workflowIndex]++;
      break;
    case WORKFLOW_ACTION_PRESS:
      if (curPressDown)
      {
        releaseKey(curAction.value);
        curPressDown = false;
        actionIndices[workflowIndex]++;
      }
      else
      {
        pressKey(curAction.value);
        curPressDown = true;
      }
      break;
    case WORKFLOW_ACTION_DELAY:
      if (!delayStarted)
      {
        delayStarted = true;
        delayStartTime = getMillis();
      }
      else if ((getMillis() - delayStartTime) > ((uint32_t)curAction.value * 10))
      {
        delayStarted = false;
        actionIndices[workflowIndex]++;
      }
      break;
    default:
      actionIndices[workflowIndex]++;
      break;
  }

  keyReportSent = false;

  if (curAction.actionType == 0x00 || curAction.actionType == WORKFLOW_ACTION_UNPROGRAMMED ||
      actionIndices[workflowIndex] == WORKFLOW_MAX_SIZE)
  {
    workflowIndex = NO_WORKFLOW;
  }
  else if (curAction.actionType == WORKFLOW_ACTION_PAUSE)
  {
    actionIndices[workflowIndex]++;
    workflowIndex = NO_WORKFLOW;
  }
}

void eraseWorkflow(uint8_t layer, uint8_t eraseIndex)
{
  uint8_t i;
  for (i = 0; i < WORKFLOW_BLOCKS; i++)
  {
    eraseFlashBlock(
     (                                                         // Calculate block index
       WORKFLOW_START_BLOCK +                                    // Skip blocks before workflows
       (layer * NUM_SWITCHES + eraseIndex) * WORKFLOW_BLOCKS +   // Skip blocks of previous workflows
       (uint32_t)i                                               // Skip blocks already erased
     ) * FLASH_4K_BLOCK_SIZE);                                 // Multiply by block size
  }
}

void saveWorkflowPacket(SI_VARIABLE_SEGMENT_POINTER(workflowData, uint8_t, SI_SEG_GENERIC),
                        uint8_t layer, uint8_t saveIndex, uint8_t packetIndex, uint16_t length)
{
  uint32_t flashAddr = WORKFLOW_START_ADDRESS +
                       WORKFLOW_BYTES * (layer * NUM_SWITCHES + saveIndex) +
                       USB_EP0_SIZE * packetIndex;
  writeFlashBytes(flashAddr, workflowData, length);
}

void loadWorkflowPacket(SI_VARIABLE_SEGMENT_POINTER(workflowData, uint8_t, SI_SEG_GENERIC),
                        uint8_t layer, uint8_t loadIndex, uint8_t packetIndex)
{
  uint32_t flashAddr = WORKFLOW_START_ADDRESS +
                       WORKFLOW_BYTES * (layer * NUM_SWITCHES + loadIndex) +
                       USB_EP0_SIZE * packetIndex;
  readFlashBytes(flashAddr, workflowData, USB_EP0_SIZE);
}

void loadWorkflowAction(SI_VARIABLE_SEGMENT_POINTER(action, Action_TypeDef, SI_SEG_GENERIC),
                        uint8_t layer, uint8_t workflowIndex, uint8_t actionIndex)
{
  uint32_t flashAddr = WORKFLOW_START_ADDRESS +
                       WORKFLOW_BYTES * (layer * NUM_SWITCHES + workflowIndex) +
                       ACTION_BYTES * actionIndex;
  readFlashBytes(flashAddr, (uint8_t*) action, ACTION_BYTES);
}

// Starts running a workflow
void startWorkflow(uint8_t index)
{
  workflowIndex = index;
  actionIndices[workflowIndex] = 0;
  workflowLayer = layer;

  //loadWorkflow(workflow, index);
  stepWorkflow();
}

void resumeWorkflow(uint8_t index)
{
  workflowIndex = index;

  //loadWorkflow(workflow, index);
  stepWorkflow();
}

uint8_t wasPressed = 0x00;

uint8_t checkKeyPressed(uint8_t bitMask, uint8_t pressed)
{
  uint8_t retVal = 0;

  if (pressed)
  {
    if (0 == (wasPressed & bitMask))
      retVal = 1;
    wasPressed |= bitMask;
  }

  return retVal;
}

uint8_t checkKeyReleased(uint8_t bitMask, uint8_t pressed)
{
  uint8_t retVal = 0;

  if (!pressed)
  {
    if (wasPressed & bitMask)
      retVal = 1;
    wasPressed &= ~bitMask;
  }

  return retVal;
}

void astrokeyInit()
{
  enter_ButtonMode_from_RESET();
}

bool flashMode = false;

// Returns true if the mode changed, false otherwise
bool astrokeyEnterFlashMode()
{
  if (!flashMode)
  {
    enter_FlashMode_from_ButtonMode();
    flashMode = true;
    return true;
  }
  return false;
}

// Returns true if the mode changed, false otherwise
bool astrokeyEnterButtonMode()
{
  if (flashMode)
  {
    enter_ButtonMode_from_FlashMode();
    flashMode = false;
    return true;
  }
  return false;
}

void astrokeyPoll()
{
  if (PRESSED(S0) && PRESSED(S4))
  {
    *((uint8_t SI_SEG_DATA *) 0x00) = 0xA5;
    RSTSRC = RSTSRC_SWRSF__SET | RSTSRC_PORSF__SET;
  }

  // Layer checking
  // Disable interrupts, prevent mode from changing
  IE_EA = 0;
  // Poll buttons if not in flash mode
  if (!flashMode)
  {
    if (!BTN0 && b0Prev && layer < (NUM_LAYERS - 1))
    {
      layer++;
    }
    if (!BTN1 && b1Prev && layer > 0)
    {
      layer--;
    }
    // Record button states
    b0Prev = BTN0;
    b1Prev = BTN1;

    setLayerLEDs(layer);
  }
  // Reenable interrupts
  IE_EA = 1;

  // Workflow currently running
  if (workflowIndex != NO_WORKFLOW)
  {
    if (keyReportSent)
      stepWorkflow();
  }
  // No workflow running, scan switches
  else
  {
    if (workflowUpdated != -1)
    {
      //saveWorkflow(tmpWorkflow, workflowUpdated);
      workflowUpdated = -1;
    }


    if (checkKeyPressed(1 << 0, PRESSED(S0)))
      startWorkflow(0);
    else if (checkKeyReleased(1 << 0, PRESSED(S0)))
      resumeWorkflow(0);

    else if (checkKeyPressed(1 << 1, PRESSED(S1)))
      startWorkflow(1);
    else if (checkKeyReleased(1 << 1, PRESSED(S1)))
      resumeWorkflow(1);

    else if (checkKeyPressed(1 << 2, PRESSED(S2)))
      startWorkflow(2);
    else if (checkKeyReleased(1 << 2, PRESSED(S2)))
      resumeWorkflow(2);

    else if (checkKeyPressed(1 << 3, PRESSED(S3)))
      startWorkflow(3);
    else if (checkKeyReleased(1 << 3, PRESSED(S3)))
      resumeWorkflow(3);

    else if (checkKeyPressed(1 << 4, PRESSED(S4)))
      startWorkflow(4);
    else if (checkKeyReleased(1 << 4, PRESSED(S4)))
      resumeWorkflow(4);
  }
}
