#include "SerialArdu.hpp"

#define green_led 14
#define red_led 15

SerialArdu ardu;

void setup() {
  Serial.begin(115200);
  pinMode(green_led, OUTPUT);
  pinMode(red_led, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  ardu.SendData("led_on");
  ardu.ledStatus(green_led, red_led);

  String led_State = ardu.ReceiveData();

  if (led_State == "led_on")
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  if (led_State == "led_off")
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
