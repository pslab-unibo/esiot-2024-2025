#include "HWPlatform.h"
#include <Arduino.h>
#include "devices/ButtonImpl.h"
#include "kernel/MsgService.h"
#include "config.h"
#include "devices/Led.h"
#include "devices/LightSensorImpl.h"
#include "devices/TempSensorTMP36.h"
#include "devices/TempSensorLM35.h"
#include "devices/servo_motor_impl.h"
#include "kernel/Logger.h"

void wakeUp(){}

HWPlatform::HWPlatform(){
  pLcd = new  LiquidCrystal_I2C(0x27,20,4);
  pButtonOpen = new ButtonImpl(BT_OPEN_PIN);
  pButtonClose = new ButtonImpl(BT_CLOSE_PIN);
  pLedOn = new Led(LED_ON_PIN);
  pLedInMaintenance = new Led(LED_MAINTENANCE_PIN);
  pSonarWasteDetector = new Sonar(SONAR_ECHO_PIN, SONAR_TRIG_PIN, 10000);
  pPirUserDetector = new Pir(PIR_PIN);
  pTempSensor = new TempSensorLM35(TEMP_SENSOR_PIN);
  pMotorDoor = new ServoMotorImpl(MOTOR_PIN);
}


void HWPlatform::init(){
  pLcd->init();
  pLcd->backlight();
  attachInterrupt(digitalPinToInterrupt(PIR_PIN), wakeUp, RISING); 

  // pPirUserDetector->calibrate();
}

  Button* HWPlatform::getOpenButton(){
    return this->pButtonOpen;
  }

  Button* HWPlatform::getCloseButton(){
    return this->pButtonClose;
  }

  Led*  HWPlatform::getOnLed(){
    return this->pLedOn;
  }

  Led*  HWPlatform::getNotAvailLed(){
    return this->pLedInMaintenance;
  }

  LiquidCrystal_I2C* HWPlatform::getUserPanelLcd(){
    return this->pLcd;
  }

  Pir*  HWPlatform::getUserDetectorPir(){
    return this->pPirUserDetector;
  }

  Sonar* HWPlatform::getWasteDetectorSonar(){
    return this->pSonarWasteDetector;
  }

  TempSensor* HWPlatform::getTempSensor(){
    return this->pTempSensor;
  }

  ServoMotor* HWPlatform::getDoorMotor(){
    return this->pMotorDoor;
  }


void HWPlatform::test(){
  pPirUserDetector->sync();
  pButtonClose->sync();
  pButtonOpen->sync();
  bool detected = pPirUserDetector->isDetected();
  float dist = pSonarWasteDetector->getDistance();
  bool openPressed = pButtonOpen->isPressed();
  bool closePressed = pButtonClose->isPressed();
  float temp = pTempSensor->getTemperature();  
  pLedOn->switchOn();
  pLedInMaintenance->switchOn();
  pLcd->setCursor(0,0);
  pLcd->print("hello");
  pMotorDoor->on();
  pMotorDoor->setPosition(90);
  Logger.log("Pir: " + String((detected ? "detected" : "not detected")));
  Logger.log("Sonar: " + String(dist) + "m");
  Logger.log("Button Open: " + String(openPressed ? "pressed" : " not pressed"));
  Logger.log("Button Close: " + String(closePressed ? "pressed" : " not pressed"));
  Logger.log("Temperature: " + String(temp) + "°C");
  delay(1000);
  pMotorDoor->setPosition(0);
  delay(1000);
  pMotorDoor->off();
  pLcd->clear();
  pLedOn->switchOff();
  pLedInMaintenance->switchOff();
}

