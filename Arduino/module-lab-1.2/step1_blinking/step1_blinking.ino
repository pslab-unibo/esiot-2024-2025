#define LED_PIN 13

void setup() {                
  pinMode(LED_PIN, OUTPUT); 
  Serial.begin(9600);     
  Serial.println("READY"); 
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  Serial.println("ON");
  delay(1000);             
  digitalWrite(LED_PIN, LOW);
  Serial.println("OFF");   
  delay(1000);              
}
