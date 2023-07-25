#ifndef _LIB_ADAFRUIT_INA219_
#define _LIB_ADAFRUIT_INA219_

#include "Arduino.h"
#include "I2C_8Bit.h"
#include "I2C_16Bit.h"
#include <Wire.h>


#define _GAMEPAD_RECEIVER_ADDRESS (0x55)
#define _REG_SET_LED_COLOR (0x01)
#define _REG_SET_LED_PLAYER (0x02)

uint16_t _read16Bit (uint8_t i2cAddr);
uint32_t _read32Bit (uint8_t i2cAddr);
 

/*!
 *   @brief  Class that stores state and functions for interacting with Gamepad rêciver
 */
class Gamepad_Receiver {
public:
  Gamepad_Receiver(uint8_t addr = _GAMEPAD_RECEIVER_ADDRESS);
  ~Gamepad_Receiver();
  uint8_t isConnected;
  uint8_t dpad;
  uint8_t dpad_left;
  uint8_t dpad_right;
  uint8_t dpad_up;
  uint8_t dpad_down;
  uint32_t aLx;
  uint32_t aLy;
  uint32_t aRx;
  uint32_t aRy;
  uint16_t buttons;
  uint16_t misc_buttons;
  uint8_t a;
  uint8_t b;
  uint8_t x;
  uint8_t y;
  uint8_t l1;
  uint8_t r1;
  uint8_t l2;
  uint8_t r2;
  uint32_t al2;
  uint32_t ar2; 
  uint8_t m1;
  uint8_t m2;
  uint8_t sys;
  void begin();
  uint8_t setLedColor(uint8_t red, uint8_t green, uint8_t blue);
  void setPlayerLed(uint8_t led);
  void update();


private:
  uint8_t i2cAddr = -1;
};

#endif
