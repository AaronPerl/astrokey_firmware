/*
 * rgb.c
 *
 *  Created on: Feb 2, 2018
 *      Author: Aaron
 */

#include "SI_EFM8UB1_Register_Enums.h"
#include "leds.h"
#include "astrokey.h"

uint8_t bufferRGB[NUM_SWITCHES * RGB_NUM_CHANNELS] = 0;

void setRGBLED(uint8_t pos, uint8_t r, uint8_t g, uint8_t b)
{
  // Store LEDs in reverse order
  pos = NUM_SWITCHES - pos - 1;
  // WS2812 has color order grb
  bufferRGB[pos * RGB_NUM_CHANNELS + 0] = g;
  bufferRGB[pos * RGB_NUM_CHANNELS + 1] = r;
  bufferRGB[pos * RGB_NUM_CHANNELS + 2] = b;
}

void refreshRGBLEDs()
{
  uint8_t i;
  uint8_t j;
  uint8_t curByte;
  // Disable interrupts
  IE_EA = 0;
  for (i = 0; i < RGB_NUM_CHANNELS * NUM_SWITCHES; i++)
  {
    curByte = bufferRGB[i];
    for (j = 0x80; j != 0; j >>= 1)
    {
      D_LED = 1;
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
      D_LED = ((curByte & j) != 0);
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
      D_LED = 0;
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
      NOP();
    }
  }
  // Enable interrupts
  IE_EA = 1;
}

void setLayerLEDs(uint8_t layer)
{
  L2 = layer & 0x01;
  L0 = layer < 2 ? !L2 : L2;
  L1 = (layer >= 2 && layer < 4) ? !L2 : L2;
}
