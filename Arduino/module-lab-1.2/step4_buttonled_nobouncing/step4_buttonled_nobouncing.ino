#define BUTTON_PIN 2  
#define LED_PIN 13  

int count;
bool already_pressed;

void setup() {
  pinMode(LED_PIN, OUTPUT);      
  pinMode(BUTTON_PIN, INPUT);     
  Serial.begin(9600);
  count = 0; 
  already_pressed = false;
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == HIGH && !already_pressed) {
    digitalWrite(LED_PIN, HIGH);  
    count++;
    Serial.println(String("Pressed - count: ") + count);
    already_pressed = true;   
    delay(100);
  } else {
    digitalWrite(LED_PIN, LOW); 
    already_pressed = false;
  }
  
  /* this delay is used to avoid bouncing */
  /* the value can change depending on the quality of the button */
    
  delay(50);
}
