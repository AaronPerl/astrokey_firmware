//-----------------------------------------------------------------------------
// main.c
//-----------------------------------------------------------------------------
// Copyright 2018 AstroKey
// https://github.com/AstroKey/astrokey_firmware/blob/master/LICENSE
//
// Program Description:
//
// AstroKey is an open-source platform for automating keyboard workflows.
// This program is the firmware running on the microcontroller found in AstroKey.
// It enumerates as a USB device with 2 interfaces, 1 to implement WebUSB and the other a HID.
// The WebUSB Interface allows the AstroKey website to save workflows created by the user to the device.
// The HID Interface plays back macros.
//
// File Description:
//
// The main source code file for the AstroKey firmware.
//
#include "astrokey.h"
#include "leds.h"
#include "delay.h"
#include "fast_hsv2rgb.h"
#include <stdint.h>

// ----------------------------------------------------------------------------
// main() Routine
// ---------------------------------------------------------------------------
//
// Initializes AstroKey functionality and polls the device inputs.
//
// ----------------------------------------------------------------------------

uint32_t prevTransitionTime;

int16_t main(void)
{
  uint16_t h = 0;
  uint8_t i, r, g, b;

  astrokeyInit();

  prevTransitionTime = getMillis();

  while (1)
  {
    if ((uint32_t)(getMillis() - prevTransitionTime) >= 10UL)
    {
      prevTransitionTime = getMillis();
      for (i = 0; i < 5; i++)
      {
        fast_hsv2rgb_8bit((h + i * (HSV_HUE_MAX / 25)) % HSV_HUE_MAX, HSV_SAT_MAX, HSV_VAL_MAX / 10, &r, &g, &b);
        setRGBLED(i, r,g,b);
        //setRGBLED(i, 0x0F, 0x0F, 0x0F);
      }
      h += HSV_HUE_MAX / 250;
      h %= HSV_HUE_MAX;
      refreshRGBLEDs();
    }

    astrokeyPoll();
  }
}
