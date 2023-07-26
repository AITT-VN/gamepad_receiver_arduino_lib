#include <Wire.h>
#include "gamepad.h"

Gamepad_Receiver gamepad;

void setup() {
  Serial.begin(115200);
  gamepad.begin();
  Serial.println("Begin");
}

void loop() {
  //Serial.println("Set led color: ");
	//Serial.println(gamepad.setLedColor(0, 255, 0));
	
	gamepad.update();
  Serial.println((int)gamepad.readJoystick(0));
  //Serial.println((int)gamepad.j_distance);
  Serial.println((int)gamepad.axis_x);
  Serial.println((int)gamepad.axis_y);
  Serial.println((int)gamepad.dir);
	  
	Serial.println();
	
	delay(100);
}
