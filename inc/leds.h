/*
 * rgb.h
 *
 *  Created on: Feb 2, 2018
 *      Author: Aaron
 */

#ifndef INC_LEDS_H_
#define INC_LEDS_H_

#include <stdint.h>

#define RGB_NUM_CHANNELS 3

void setRGBLED(uint8_t pos, uint8_t r, uint8_t g, uint8_t b);
void refreshRGBLEDs();

void setLayerLEDs(uint8_t layer);
//void resetRGBLEDs();

#endif /* INC_LEDS_H_ */
