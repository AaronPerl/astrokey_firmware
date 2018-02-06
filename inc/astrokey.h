//-----------------------------------------------------------------------------
// astrokey.h
//-----------------------------------------------------------------------------
// Copyright 2018 AstroKey
// https://github.com/AstroKey/astrokey_firmware/blob/master/LICENSE
//
// File Description:
//
// AstroKey-specific definitions and function declarations.
//

#ifndef INC_ASTROKEY_H_
#define INC_ASTROKEY_H_

#include <SI_EFM8UB1_Defs.h>
#include <stdint.h>
#include <flash.h>
#include "efm8_usb.h"

// Astrokey USB protocol

// wIndex values
#define ASTROKEY_SET_WORKFLOW 0x01
#define ASTROKEY_GET_WORKFLOW 0x02

// Switch configuration
#define NUM_SWITCHES 5
#define S0       P2_B0
#define S1       P1_B0
#define S2       P0_B7
#define S3       P0_B6
#define S4       P0_B5
#define D_LED    P0_B3
#define L0       P1_B1
#define L1       P1_B2
#define L2       P3_B1
#define FLASH_CS P0_B4

// Switch pressed
#define PRESSED(x) (!x)

// No macro running
#define NO_WORKFLOW 0xFF

// Macro action types
#define WORKFLOW_ACTION_DOWN  1
#define WORKFLOW_ACTION_UP    2
#define WORKFLOW_ACTION_PRESS 3
#define WORKFLOW_ACTION_DELAY 16
#define WORKFLOW_ACTION_PAUSE 128 // Pauses a macro until key release
#define WORKFLOW_ACTION_UNPROGRAMMED 255 // Unprogrammed flash memory

#define USAGE_LEFTCTRL  224
#define USAGE_LEFTSHIFT 225
#define USAGE_LEFTALT   226
#define USAGE_LEFTGUI   227

#define MODIFIER_LEFTCTRL  0x01
#define MODIFIER_LEFTSHIFT 0x02
#define MODIFIER_LEFTALT   0x04
#define MODIFIER_LEFTGUI   0x08

// Macro action struct
typedef struct {
  uint8_t actionType;
  uint8_t value;
} Action_TypeDef;

// Starting block for macro storage in external flash
#define WORKFLOW_START_BLOCK 1
// Starting address for macro storage in external flash
#define WORKFLOW_START_ADDRESS (WORKFLOW_START_BLOCK * FLASH_4K_BLOCK_SIZE)
// Number of blocks per macro
#define WORKFLOW_BLOCKS 1
// Number of bytes per macro
#define WORKFLOW_BYTES (WORKFLOW_BLOCKS * FLASH_4K_BLOCK_SIZE)
// Maximum number of actions in a macro
#define WORKFLOW_MAX_SIZE 64//((WORKFLOW_BYTES) / sizeof(Action_TypeDef))
// Max number of keys simultaneously held by macro
#define WORKFLOW_MAX_KEYS 6

void eraseWorkflow(uint8_t eraseIndex);
void saveWorkflowPacket(SI_VARIABLE_SEGMENT_POINTER(workflowData, uint8_t, SI_SEG_GENERIC),
                        uint8_t saveIndex, uint8_t packetIndex, uint16_t length);
void loadWorkflowPacket(SI_VARIABLE_SEGMENT_POINTER(workflowData, uint8_t, SI_SEG_GENERIC),
                        uint8_t loadIndex, uint8_t packetIndex);

extern uint8_t workflowNumActions;
extern volatile int8_t workflowUpdated;

extern SI_SEGMENT_VARIABLE(myUsbDevice, USBD_Device_TypeDef, MEM_MODEL_SEG);

extern uint32_t prevTransitionTime;
void astrokeyInit();
void astrokeyPoll();

bool astrokeyEnterFlashMode();
bool astrokeyEnterButtonMode();

#endif /* INC_ASTROKEY_H_ */
