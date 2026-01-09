#include "Arduino.h"
#include "TrafficLight.h"

TrafficLight::TrafficLight(int r, int o, int g)
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
