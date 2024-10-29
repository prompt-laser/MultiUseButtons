#include "MultiUseButton.h"

MultiUseButton btn1 = new MultiUseButton(9);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(9),btn_pushed,CHANGE);
  btn1.SetDelayTimer(1000);
  btn1.AttachInstantFunction(m_Instant);
  btn1.AttachDelayFunction(m_Delay);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10);
  btn1.Run();
}

void btn_pushed(){
  btn1.Toggle();
}

void m_Instant(){
  Serial.println("This is the instant function!");
}

void m_Delay(){
  Serial.println("This is the delay function!");
}