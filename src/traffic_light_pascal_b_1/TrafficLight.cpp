#include "Arduino.h"
#include "TrafficLight.h"

TrafficLight::TrafficLight(int r, int o, int g)
  : redPin(r), orangePin(o), greenPin(g) {}

void TrafficLight::begin() {
  pinMode(redPin, OUTPUT);
  pinMode(orangePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void TrafficLight::set(LightColor color) {
  digitalWrite(redPin, LOW);
  digitalWrite(orangePin, LOW);
  digitalWrite(greenPin, LOW);

  switch (color) {
    case LightColor::RED:
      digitalWrite(redPin, HIGH);
      break;
    case LightColor::ORANGE:
      digitalWrite(orangePin, HIGH);
      break;
    case LightColor::GREEN:
      digitalWrite(greenPin, HIGH);
      break;
  }
}

void TrafficLight::apply(const Step& s) {
  digitalWrite(redPin,    s.red    ? HIGH : LOW);
  digitalWrite(orangePin, s.orange ? HIGH : LOW);
  digitalWrite(greenPin,  s.green  ? HIGH : LOW);
}
