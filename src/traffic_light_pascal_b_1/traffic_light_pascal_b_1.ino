class TrafficLight
{
  private:
    int red_lamp_pin;
    int orange_lamp_pin;
    int green_lamp_pin;
  public:
    TrafficLight(const int redPin, const int orangePin, const int greenPin);
    void setLampsState(const int redState, const int orangeState, const int greenState) const;
    void setState(const String state) const;
};
TrafficLight::TrafficLight(const int redPin, const int orangePin, const int greenPin)
{
  red_lamp_pin = redPin;
  orange_lamp_pin = orangePin;
  green_lamp_pin = greenPin;
}
void TrafficLight::setLampsState(const int redState, const int orangeState, const int greenState) const
{
  digitalWrite(red_lamp_pin, redState);
  digitalWrite(orange_lamp_pin, orangeState);
  digitalWrite(green_lamp_pin, greenState);
}
void TrafficLight::setState(const String state) const
{
  if(state == "stop")
  {
    this->setLampsState(HIGH, LOW, LOW);
  }
  else if(state == "beforeStop")
  {
    this->setLampsState(LOW, HIGH, LOW);
  }
  else if(state == "beforeGo")
  {
    this->setLampsState(HIGH, HIGH, LOW);
  }
  else if(state == "go")
  {
    this->setLampsState(LOW, LOW, HIGH);
  }
  else if(state == "all")
  {
    this->setLampsState(HIGH, HIGH, HIGH);
  }
  else if(state == "none")
  {
    this->setLampsState(LOW, LOW, LOW);
  }
}
/**
* @author Ronan Messuwe
* @version 1 2018-08-14
* latest update: 2018-08-17
* 
*/
const int RED_LAMP_PIN = 2;
const int ORANGE_LAMP_PIN = 3;
const int GREEN_LAMP_PIN = 4;

const int CD4511_A_PIN = 9;
const int CD4511_B_PIN = 10;
const int CD4511_C_PIN = 11;
const int CD4511_D_PIN = 12;

const int MODE_BUTTON_PIN = 8;

const int NB_MODES = 8;

const int SEQUENCE_1_NB_STEPS = 3;
const int SEQUENCE_2_NB_STEPS = 4;
const int SEQUENCE_3_NB_STEPS = 2;
const int SEQUENCE_4_NB_STEPS = 1;
const int SEQUENCE_5_NB_STEPS = 1;
const int SEQUENCE_6_NB_STEPS = 1;
const int SEQUENCE_7_NB_STEPS = 1;
const int SEQUENCE_8_NB_STEPS = 4;

const int TIME_BETWEEN_STOP_AND_GO = 12000; // <= 120s
const int TIME_BETWEEN_GO_AND_INTERMEDIARY = 6000; // >= 6s
const int TIME_BETWEEN_INTERMEDIARY_AND_STOP = 3000; // 3s (agglo) ou 6s (hors agglo)
// Voir le document suivant pour les temps : 
// INSTRUCTION INTERMINISTÉRIELLE SUR LA SIGNALISATION ROUTIÈRE
// 6ème PARTIE : Feux de circulation permanents
// http://www.equipementsdelaroute.equipement.gouv.fr/IMG/pdf/IISR_6ePARTIE_vc20120402_cle573dda.pdf

bool modeButtonIsPressed = false;

int currentSequenceMaxSteps;

unsigned long uptime = 0;

int modeNum = 1;
int currentStep = 1;
unsigned long nextStepUptimeVal = 0;

TrafficLight trafficLight(RED_LAMP_PIN, ORANGE_LAMP_PIN, GREEN_LAMP_PIN);

void setup()
{
  pinMode(MODE_BUTTON_PIN, INPUT_PULLUP);
  pinMode(RED_LAMP_PIN, OUTPUT);
  pinMode(ORANGE_LAMP_PIN, OUTPUT);
  pinMode(GREEN_LAMP_PIN, OUTPUT);
  
  pinMode(CD4511_A_PIN, OUTPUT);
  pinMode(CD4511_B_PIN, OUTPUT);
  pinMode(CD4511_C_PIN, OUTPUT);
  pinMode(CD4511_D_PIN, OUTPUT);

  
  //pinMode(13, OUTPUT);
  //digitalWrite(13, LOW);
  
  setMode(modeNum);
}

void loop()
{
  delay(50);
  uptime = millis();
  
  // Si le bouton n'était pas pressé mais qu'il l'est maintenant
  if(!modeButtonIsPressed && (digitalRead(MODE_BUTTON_PIN) == LOW)) // LOW et non pas HIGH car INPUT_PULLUP
  {
    // Le bouton est appuyé
    modeButtonIsPressed = true;
    
    // Si on est au dernier mode
    if(modeNum == NB_MODES){
      // Retourne au premier mode
      modeNum = 1;
    } else {
      // Passe au mode suivant
      modeNum++; 
    }

    setMode(modeNum);
    
  // Ou si le bouton était pressé mais qu'il ne l'est plus
  } 
  else if(modeButtonIsPressed && (digitalRead(MODE_BUTTON_PIN) == HIGH)) // HIGH et non pas LOW car INPUT_PULLUP
  {
    // Le bouton est relaché
    modeButtonIsPressed = false;
  }
  
  // Si on est arrivé à l'uptime de la prochaine étape...
  if(uptime >= nextStepUptimeVal)
  {
    // Calcule l'uptime de la prochaine étape
    switch(modeNum)
    {
      case 1:
        nextStepUptimeVal = uptime + setTrafficLightSequence1Step(currentStep);
        break;
      case 2:
        nextStepUptimeVal = uptime + setTrafficLightSequence2Step(currentStep);
        break;
      case 3:
        nextStepUptimeVal = uptime + setTrafficLightSequence3Step(currentStep);
        break;
      case 4:
        nextStepUptimeVal = uptime + setTrafficLightSequence4Step(currentStep);
        break;
      case 5:
        nextStepUptimeVal = uptime + setTrafficLightSequence5Step(currentStep);
        break;
      case 6:
        nextStepUptimeVal = uptime + setTrafficLightSequence6Step(currentStep);
        break;
      case 7:
        nextStepUptimeVal = uptime + setTrafficLightSequence7Step(currentStep);
        break;
      case 8:
        nextStepUptimeVal = uptime + setTrafficLightSequence8Step(currentStep);
        break;
    }
    
    // Si on arrive à la dernière étape
    if(currentStep == currentSequenceMaxSteps)
    {
      // Retourne à la première étape
      currentStep = 1;
    } else {
      // Passe à l'étape suivante
      currentStep++;
    }
  }
}

void setMode(int mode)
{
  // Reinit current step at 1
  currentStep = 1;
  // Reset
  nextStepUptimeVal = 0;
  switch(mode)
  {
    case 1:
      // 1
      setCD4511(B1, B0, B0, B0);
    
      currentSequenceMaxSteps = SEQUENCE_1_NB_STEPS;
      break;
    case 2:
      // 2
      setCD4511(B0, B1, B0, B0);
    
      currentSequenceMaxSteps = SEQUENCE_2_NB_STEPS;
      break;
    case 3:
      // 3
      setCD4511(B1, B1, B0, B0);
      
      currentSequenceMaxSteps = SEQUENCE_3_NB_STEPS;
      break;
    case 4:
      // 4
      setCD4511(B0, B0, B1, B0);
    
      currentSequenceMaxSteps = SEQUENCE_4_NB_STEPS;
      break;
    case 5:
      // 5
      setCD4511(B1, B0, B1, B0);
      
      currentSequenceMaxSteps = SEQUENCE_5_NB_STEPS;
      break;
    case 6:
      // 6
      setCD4511(B0, B1, B1, B0);
    
      currentSequenceMaxSteps = SEQUENCE_6_NB_STEPS;
      break;
    case 7:
      // 7
      setCD4511(B1, B1, B1, B0);
    
      currentSequenceMaxSteps = SEQUENCE_7_NB_STEPS;
      break;
    case 8:
      // 8
      setCD4511(B0, B0, B0, B1);
    
      currentSequenceMaxSteps = SEQUENCE_8_NB_STEPS;
      break;
  }
}

void setCD4511(byte a, byte b, byte c, byte d)
{
  digitalWrite(CD4511_A_PIN, a);
  digitalWrite(CD4511_B_PIN, b);
  digitalWrite(CD4511_C_PIN, c);
  digitalWrite(CD4511_D_PIN, d);
}

// ========= SEQUENCES =========

// Séquence 1 FR/US
int setTrafficLightSequence1Step(int step)
{
  switch(step){
    case 1:
      trafficLight.setState("stop");
      return TIME_BETWEEN_STOP_AND_GO;
      break;
    case 2:
      trafficLight.setState("go");
      return TIME_BETWEEN_GO_AND_INTERMEDIARY;
      break;
    case 3:
      trafficLight.setState("beforeStop");
      return TIME_BETWEEN_INTERMEDIARY_AND_STOP;
      break;
  }
}
// Séquence 2 UK
int setTrafficLightSequence2Step(int step)
{
  switch(step){
    case 1:
      trafficLight.setState("stop");
      return TIME_BETWEEN_STOP_AND_GO;
      break;
    case 2:
      trafficLight.setState("beforeGo");
      return TIME_BETWEEN_INTERMEDIARY_AND_STOP;
      break;
    case 3:
      trafficLight.setState("go");
      return TIME_BETWEEN_GO_AND_INTERMEDIARY;
      break;
    case 4:
      trafficLight.setState("beforeStop");
      return TIME_BETWEEN_INTERMEDIARY_AND_STOP;
      break;
  }
}
// Séquence 3 orange clignotant
int setTrafficLightSequence3Step(int step)
{
  switch(step){
    case 1:
      trafficLight.setState("beforeStop");
      return 500;
      break;
    case 2:
      trafficLight.setState("none");
      return 500;
      break;
  }
}
// Séquence 4 rouge fixe
int setTrafficLightSequence4Step(int step)
{
  switch(step){
    case 1:
      trafficLight.setState("stop");
      return 10000;
      break;
  }
}
// Séquence 5 orange fixe
int setTrafficLightSequence5Step(int step)
{
  switch(step){
    case 1:
      trafficLight.setState("beforeStop");
      return 10000;
      break;
  }
}
// Séquence 6 vert fixe
int setTrafficLightSequence6Step(int step)
{
  switch(step){
    case 1:
      trafficLight.setState("go");
      return 10000;
      break;
  }
}
// Séquence 7 rouge, orange, vert fixe
int setTrafficLightSequence7Step(int step)
{
  switch(step){
    case 1:
      trafficLight.setState("all");
      return 10000;
      break;
  }
}
// Séquence 8 chenillard
int setTrafficLightSequence8Step(int step)
{
  switch(step){
    case 1:
      trafficLight.setState("stop");
      return 500;
      break;
    case 2:
      trafficLight.setState("beforeStop");
      return 500;
      break;
    case 3:
      trafficLight.setState("go");
      return 500;
      break;
    case 4:
      trafficLight.setState("beforeStop");
      return 500;
      break;
  }
}
