#include "WasteContainer.h"
#include <Arduino.h>
#include "devices/ButtonImpl.h"
#include "kernel/MsgService.h"
#include <avr/sleep.h>
#include "config.h"
#include "devices/Led.h"
#include "devices/LightSensorImpl.h"
#include "devices/TempSensorLM35.h"
#include "devices/servo_motor_impl.h"
#include "kernel/Logger.h"

#define MIN_DIST_WASTE 0.10
#define MAX_DIST_WASTE 1.00

WasteContainer::WasteContainer(HWPlatform* pHW):pHW(pHW){
}


void WasteContainer::init(){
  wasteLevelPercentage = 0;
  _isFull = false;
  this->reset();
  isAvail = true;
  pHW->getDoorMotor()->on();
  pHW->getOnLed()->switchOn();
  pHW->getNotAvailLed()->switchOff();
  pHW->getDoorMotor()->off();
}

bool WasteContainer::isFull(){
  return wasteLevelPercentage >= 100;
}

int WasteContainer::getWasteLevelPercentage(){
  return wasteLevelPercentage;
}
  
void WasteContainer::sync(){
  currentTemp = pHW->getTempSensor()->getTemperature();
  if (!_isFull && canSenseDistance()){
    float dist = pHW->getWasteDetectorSonar()->getDistance();
    float dd = (MAX_DIST_WASTE - dist);    
    wasteLevelPercentage = dd*100/(MAX_DIST_WASTE - MIN_DIST_WASTE);
    if (wasteLevelPercentage < 0){
      wasteLevelPercentage = 0;
    } else if (wasteLevelPercentage >= 100){
      wasteLevelPercentage = 100;
      _isFull = true;
      pHW->getOnLed()->switchOff();
      pHW->getNotAvailLed()->switchOn();
    }
    /*
    static int i = 0;    
    i++;
    if (i % 25 == 0){
      Logger.log("Dist: " + String(dist) + " perc: " + String(wasteLevelPercentage) + " isFull: " + String(_isFull));
    }*/ 
  }
}

bool WasteContainer::canSenseDistance(){
  return !pHW->getDoorMotor()->isOn();
}

void WasteContainer::startOpeningDoor(){
  if (isAvail){
    pHW->getDoorMotor()->on();
    pHW->getDoorMotor()->setPosition(180);
  }
}

void WasteContainer::stopOpeningDoor(){
  pHW->getDoorMotor()->off();
}

void WasteContainer::startClosingDoor(){
  pHW->getDoorMotor()->on();
  pHW->getDoorMotor()->setPosition(90);
}

void WasteContainer::stopClosingDoor(){
  pHW->getDoorMotor()->off();
}

void WasteContainer::startOpeningForDischarging(){
  pHW->getDoorMotor()->on();
  pHW->getDoorMotor()->setPosition(0);
}

void WasteContainer::stopOpeningForDischarging(){
  pHW->getDoorMotor()->setPosition(90);
}

void WasteContainer::startClosingForDischarging(){
  pHW->getDoorMotor()->on();
  pHW->getDoorMotor()->setPosition(0);
}

void WasteContainer::stopClosingForDischarging(){
  pHW->getDoorMotor()->setPosition(90);
}

void WasteContainer::notifyDischargingCompleted(){
  _isFull = false;
  wasteLevelPercentage = 0;
  this->reset();
}

bool WasteContainer::isAvailable(){
  return isAvail;
}

bool WasteContainer::isInMaintenance(){
  return !isAvail;
}

void WasteContainer::notifyMaintenanceCompleted(){
  this->reset();
}

void WasteContainer::reset(){
  isAvail = true;
  pHW->getOnLed()->switchOn();
  pHW->getNotAvailLed()->switchOff();
  pHW->getDoorMotor()->off();
}

void WasteContainer::setMaintenance(){
  isAvail = false;
  pHW->getOnLed()->switchOff();
  pHW->getNotAvailLed()->switchOn();
  pHW->getDoorMotor()->off();
}

float WasteContainer::getCurrentTemperature(){
  return this->currentTemp;
}

