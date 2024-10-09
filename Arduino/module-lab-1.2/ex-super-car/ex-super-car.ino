
#define N_LEDS 4
int led_pins[N_LEDS] = { 3, 4, 5, 6};

int current = 0;
int step = 1;
int how_long_on_max = 1000;

void test(){
  for (int i = 0; i < N_LEDS; i++){
    digitalWrite(led_pins[i],HIGH);
  }
}

void setup() {
  for (int i = 0; i < N_LEDS; i++){
    pinMode(led_pins[i],OUTPUT);
  }
  /* testing */
  // test();
}


void loop() {
  // int speed = analogRead(A0);
  // float factor = ((float)speed)/1024;

  digitalWrite(led_pins[current],HIGH);
  delay(how_long_on_max*factor);
  digitalWrite(led_pins[current],LOW);

  current += step;

  if (current == N_LEDS){
    current = N_LEDS - 2; 
    step = -step;
  } else if (current < 0){
    current = 1;
    step = -step;
  }
}
