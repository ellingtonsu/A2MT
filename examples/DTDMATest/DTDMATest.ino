#include <DTDMA.h>

int led1 = 4;
int led2 = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led1, OUTPUT); 
  pinMode(led2, OUTPUT); 

  // Blink LED 1 per 200 ms
  DTDMA.addTaskList(); DTDMA.addTask(led1On, 100);  DTDMA.addTask(led1Off, 100);
  // Blink LED 2 per 2000 ms
  DTDMA.addTaskList(); DTDMA.addTask(led2On, 1000); DTDMA.addTask(led2Off, 1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  DTDMA.start();
}

void led1On() { digitalWrite(led1, HIGH);}
void led1Off(){ digitalWrite(led1, LOW); }

void led2On() { digitalWrite(led2, HIGH);}
void led2Off(){ digitalWrite(led2, LOW); }
