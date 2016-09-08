#define TRIGGER 8
#define ECHO 9
#define TRY 5
#define ON 1
#define ALARM 7
#define TOLERANCE 50 //obtain the value with try and error approach

int i = 0;
int init_counter = 0;
int calc_counter = 0;
float total_signal = 0;
float container;
float average_signal;

void setup() {
  Serial.begin(9600);
  pinMode(TRIGGER, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  if (!(init_counter)) {
    initiate(TRIGGER);
    container = pulseIn(ECHO, HIGH);
    total_signal = total_signal + container;
    i++;
    if (i == TRY)
      init_counter = ON;
  } else {
    if (!(calc_counter)) {
      average_signal = total_signal / TRY;
      calc_counter = ON;
    }
    initiate(TRIGGER);
    container = pulseIn(ECHO, HIGH);
    Serial.println(container * 0.01657); //get a cm (sudah di kalibrasi !)
    if (container < average_signal - TOLERANCE) {
      alarm(ALARM);
      delay(500); //remember to delay, to give a chance for ultrasonic wave
    }
  }
}

void initiate (int trig_pin)
{
  //awalan trigger
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(5);
  //mulai trigger
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
}

void alarm (int alarm_pin)
{
  digitalWrite(alarm_pin, HIGH);
  delay(100);
  digitalWrite(alarm_pin, LOW);
}
