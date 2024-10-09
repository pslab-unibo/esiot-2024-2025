#define BUTTON_PIN 2
#define DEBOUNCE_TIME 40

volatile int count = 0;
int prev = 0;
long prevts = 0;

void setup()
{
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), inc, RISING); 
}

void loop()
{
  noInterrupts();
  int current = count;
  interrupts();
  if (current != prev){
    Serial.println(current);
    prev = current;
  }
}

void inc()
{
  long ts = millis();
  if (ts - prevts > DEBOUNCE_TIME){
    count++;
    prevts = ts;
  }
}
