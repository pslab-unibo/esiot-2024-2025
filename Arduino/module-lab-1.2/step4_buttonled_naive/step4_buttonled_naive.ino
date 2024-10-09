#define BUTTON_PIN 2  
#define LED_PIN 13  

bool ledAlreadyOn;

void setup() {
  pinMode(LED_PIN, OUTPUT);      
  pinMode(BUTTON_PIN, INPUT);    
  ledAlreadyOn = false;
  Serial.begin(9600); 
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == HIGH && !ledAlreadyOn) {
    Serial.println("PRESSED");
    digitalWrite(LED_PIN, HIGH);  
    ledAlreadyOn = true;
  } else if (buttonState == LOW && ledAlreadyOn) {
    Serial.println("NOT PRESSED");
    digitalWrite(LED_PIN, LOW); 
    ledAlreadyOn = false;
  }
}
