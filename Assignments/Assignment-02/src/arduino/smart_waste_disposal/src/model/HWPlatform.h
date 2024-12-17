#ifndef __HW_PLATFORM__
#define __HW_PLATFORM__

#include "config.h"
#include "devices/Button.h"
#include "devices/Led.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "devices/Pir.h"
#include "devices/Sonar.h"
#include "devices/TempSensor.h"
#include "devices/Led.h"
#include "devices/servo_motor.h"

class HWPlatform {

public:
  HWPlatform();
  void init();
  void test();

  Button* getOpenButton();
  Button* getCloseButton();
  Led*  getOnLed();
  Led*  getNotAvailLed();
  LiquidCrystal_I2C* getUserPanelLcd();
  Pir*  getUserDetectorPir();
  Sonar* getWasteDetectorSonar();
  TempSensor* getTempSensor();  
  ServoMotor* getDoorMotor();

private:
  Button* pButtonOpen;
  Button* pButtonClose; 
  Led* pLedOn;
  Led* pLedInMaintenance;
  LiquidCrystal_I2C* pLcd; 
  ServoMotor* pMotorDoor;
  Pir* pPirUserDetector;
  Sonar* pSonarWasteDetector;
  TempSensor* pTempSensor;

};

#endif
