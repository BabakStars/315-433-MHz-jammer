#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(1);
  pinMode(9, OUTPUT);
  tone(9, 1000);
}

void loop() {
  if (mySwitch.available()) {

    Serial.print("Button Code is: ");
    Serial.println( mySwitch.getReceivedValue() );
    mySwitch.resetAvailable();
  }
  
}
