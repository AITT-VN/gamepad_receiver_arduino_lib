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
	Serial.print((int)gamepad.isConnected);
	Serial.print(" "); Serial.print(gamepad.dpad_left);
  Serial.print(" "); Serial.print(gamepad.dpad_right);
  Serial.print(" "); Serial.print(gamepad.dpad_up);
  Serial.print(" "); Serial.print(gamepad.dpad_down);
  Serial.print(" "); Serial.print(gamepad.aLx);
  Serial.print(" "); Serial.print(gamepad.aLy);
  Serial.print(" "); Serial.print(gamepad.aRx);
  Serial.print(" "); Serial.print(gamepad.aRy);
  Serial.print(" "); Serial.print(gamepad.al2);
  Serial.print(" "); Serial.print(gamepad.ar2);
  Serial.print(" "); Serial.print(gamepad.a);
  Serial.print(" "); Serial.print(gamepad.b);
  Serial.print(" "); Serial.print(gamepad.x);
  Serial.print(" "); Serial.print(gamepad.y);
  Serial.print(" "); Serial.print(gamepad.l1);
  Serial.print(" "); Serial.print(gamepad.l2);
  Serial.print(" "); Serial.print(gamepad.r1);
  Serial.print(" "); Serial.print(gamepad.r2);
  Serial.print(" "); Serial.print(gamepad.sys);
  
	Serial.println();
	
	delay(100);
}
