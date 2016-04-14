#include <LDMA.h>

int led1 = 4;
int led2 = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led1, OUTPUT); 
  pinMode(led2, OUTPUT); 
  LDMA.addTask(led1flash, 10);
  LDMA.addTask(led2flash);  
}

void loop() {
  // put your main code here, to run repeatedly:
  LDMA.start();
}
void led1flash(){
  digitalWrite(led1, HIGH);
  delay(100);
  digitalWrite(led1, LOW);
  delay(100);
}

void led2flash(){
  digitalWrite(led2, HIGH);
  delay(1000);
  digitalWrite(led2, LOW);
  delay(1000); 
}