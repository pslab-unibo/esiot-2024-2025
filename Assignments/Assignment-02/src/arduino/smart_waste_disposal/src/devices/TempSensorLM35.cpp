#include "TempSensorLM35.h"
#include "Arduino.h"
#include "kernel/Logger.h"

#define VCC ((float)5)

TempSensorLM35::TempSensorLM35(int p) : pin(p){
} 
  
float TempSensorLM35::getTemperature(){
  float values[5];
  float max = -1;
  float min = 100; 
  
  /* 
     simple strategy for input conditioning: 
     - doing multiple measurements, discarding mix and max and returning the average
  */
  
  for (int i = 0; i < 5; i++){
    int value = analogRead(pin);
    float valueInVolt = value*VCC/1023;  
    float valueInCelsius = valueInVolt/0.01;
    values[i] = valueInCelsius;    
    if (valueInCelsius < min){
      min = valueInCelsius;
    } else if (valueInCelsius > max){
      max = valueInCelsius;
    }
  }
  float sum = 0;
  int count = 0;
  for (int i = 0; i < 5; i++){
    if ((values[i] > min) && (values[i] < max)){
      sum = sum + values[i];
      count++;
    }
  }
  if (count == 0){
    return values[0];
  } else {
    return sum/count;
  }
}
