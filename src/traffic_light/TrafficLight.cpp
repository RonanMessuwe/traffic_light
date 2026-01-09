#include "Arduino.h"
#include "TrafficLight.h"

TrafficLight::TrafficLight(uint8_t r, uint8_t o, uint8_t g)
  : redPin(r), orangePin(o), greenPin(g) {}

void TrafficLight::begin() {
  pinMode(redPin, OUTPUT);
  pinMode(orangePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void TrafficLight::apply(const Step& s) {
  digitalWrite(redPin,    s.red    ? HIGH : LOW);
  digitalWrite(orangePin, s.orange ? HIGH : LOW);
  digitalWrite(greenPin,  s.green  ? HIGH : LOW);
}
