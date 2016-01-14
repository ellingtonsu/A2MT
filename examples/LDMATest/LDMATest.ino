#include <LDMA.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  LDMA.addTask(getSensor, 10);
  LDMA.addTask(sendSensor);  
}

void loop() {
  // put your main code here, to run repeatedly:
  LDMA.start();
}
void getSensor(){
  Serial.print(".");
  delay(100);
}

void sendSensor(){
  Serial.println("Send 10 sensor values"); 
}

