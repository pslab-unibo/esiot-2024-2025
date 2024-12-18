#include "TempSensorTMP36.h"
#include "Arduino.h"
#include "kernel/Logger.h"

#define VCC ((float)5)

/*
 * TMP36: sensing interval [-40°C,  +125°C] mapped linearly in [0.1Vdc, 1.7Vdc]
 * so 
 * - 0°C => tension: 500mV
 * - a change of 1 °C => change of 10mV
 * - precision: +- 2°C
 * formula °C = ((ADC value * 0.00488) - 0.5) / 0.01
 * where:
 * -  ADC value = analogue value read 
 * - 0.00488 =  5Vdc/1024 = ADC precision
 * - 0.5 = Tension at zero degree
 * - 0.01 = stepVoltPerDegree
 *
 * IMPROVEMENTS to augment the precision
 * -  connecting AREF pin to 3.3Vdc - setting analogReference(EXTERNAL);
 * - instead of 0.00488 (i.e. 5Vdc/1024 = 0.00488) => 0.0032 (3.3Vdc/1024)/
 */
TempSensorTMP36::TempSensorTMP36(int p) : pin(p){
} 
  
float TempSensorTMP36::getTemperature(){
  float values[5];
  float max = -1;
  float min = 100; 
  
  /* 
     simple strategy for input conditioning: 
     - doing multiple measurements, discarding mix and max and returning the average
  */
  
  for (int i = 0; i < 5; i++){
    int value = analogRead(pin);
    /* this is the formula for the TMP36*/
    float valueInCelsius = ((value * 0.00488) - 0.5) / 0.01;
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
