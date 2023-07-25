#include "Arduino.h"
#include <Wire.h>
#include "gamepad.h"

/*!
 *  @brief  Instantiates a new Gamepad receiver class
 *  @param addr the I2C address the device can be found on. Default is 0x55
 */
Gamepad_Receiver::Gamepad_Receiver(uint8_t addr) {
  i2cAddr = addr;
}

/*!
 *  @brief Gamepad receiver class destructor
 */
Gamepad_Receiver::~Gamepad_Receiver() { }

void Gamepad_Receiver::begin(){
    Wire.begin();
}

void Gamepad_Receiver::setPlayerLed(uint8_t led){
    if (led < 0 || led > 255) {
        return 0;
    }
    I2C_16Bit_writeToModule(i2cAddr, led);

}

uint8_t Gamepad_Receiver::setLedColor(uint8_t red, uint8_t green, uint8_t blue){
    if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255){
        return 0;
    }
    Wire.beginTransmission(i2cAddr);
    Wire.write(_REG_SET_LED_COLOR);
    Wire.write(red);
    Wire.write(green);
    Wire.write(blue);
    Wire.endTransmission();
    return 1;
}

uint32_t _read32Bit (uint8_t i2cAddr) {
    uint8_t byteCount = 4;
    //Wire.beginTransmission(i2cAddr);
    //Wire.endTransmission();
    //Wire.requestFrom(i2cAddr, byteCount);
    if (Wire.available()) {
      uint8_t firstByte = Wire.read();
      uint8_t secondByte = Wire.read();
      uint8_t thirdByte = Wire.read();
      uint8_t fourthByte = Wire.read();
      int32_t raw = (firstByte << 24) + (secondByte << 16) + (thirdByte << 8) + fourthByte;
      //Serial.println(firstByte);
      //Serial.println(secondByte);
      //Serial.println(thirdByte);
      //Serial.println(fourthByte);
      //return (fourthByte << 24) + (thirdByte << 16) + (secondByte << 8) + firstByte;
      if (raw & (1UL << 31))  { // sign bit is set
          Serial.print("Negative: ");
          Serial.print(raw);
          Serial.println();
          return ((1UL << 32) - raw) * -1;
      } else {
          return raw;
      }
    }
    return 0;
}

uint16_t _read16Bit (uint8_t i2cAddr) {
    uint8_t byteCount = 2;
    //Wire.beginTransmission(i2cAddr);
    //Wire.endTransmission();
    //Wire.requestFrom(i2cAddr, byteCount);
    if (Wire.available()) {
      uint8_t firstByte = Wire.read();
      uint8_t secondByte = Wire.read();
      return (firstByte << 8) + secondByte ;
    }

  return 0;
}

void Gamepad_Receiver::update() {
    
    Wire.beginTransmission(i2cAddr);
    Wire.endTransmission();
    Wire.requestFrom(i2cAddr, 30);
    if (Wire.available()){
      isConnected = Wire.read();
      dpad = Wire.read();
      aLx = _read32Bit(i2cAddr);
      aLy = _read32Bit(i2cAddr);
      aRx = _read32Bit(i2cAddr);
      aRy = _read32Bit(i2cAddr);
      al2 = _read32Bit(i2cAddr);
      ar2 = _read32Bit(i2cAddr);
      buttons = _read16Bit(i2cAddr);
      misc_buttons = _read16Bit(i2cAddr);  
        
    } else {
      isConnected = 0;
      dpad = 0;
      aLx = 0;
      aLy = 0;
      aRx = 0;
      aRy = 0;
      al2 = 0;
      ar2 = 0;
      buttons = 0;
      misc_buttons = 0;
    }    
    //decode Buttons PS4
    dpad_left = (dpad >> 3) & 1;
    dpad_right = (dpad >> 2) & 1;
    dpad_up = (dpad >> 0) & 1;
    dpad_down = (dpad >> 1) & 1;
    a = (buttons >> 0) & 1;
    b = (buttons >> 1) & 1;
    x = (buttons >> 2) & 1;
    y = (buttons >> 3) & 1;
    l1 = (buttons >> 4) & 1;
    r1 = (buttons >> 5) & 1;
    l2 = (buttons >> 6) & 1;
    r2 = (buttons >> 7) & 1;
    m1  = (misc_buttons >> 1) & 1;
    m2 = (misc_buttons >> 2) & 1;
    sys = (misc_buttons >> 0) & 1;

}
