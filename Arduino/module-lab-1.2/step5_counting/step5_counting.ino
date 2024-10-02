#define BUTTON_PIN 2

volatile int count;
int prev;

void setup()
{
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), inc, RISING); 
  count = 0;
  prev = 0;  
}

void loop()
{
  noInterrupts();
  int current = count;
  interrupts();

  Serial.println(current);
  /*  
  noInterrupts();
  int current = count;
  interrupts();

  if (current != prev){
    Serial.println(current);
    prev = current;
  }*/
}


void inc()
{
  count++;
  delayMicroseconds(20000);
}
