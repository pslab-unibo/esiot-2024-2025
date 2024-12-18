#ifndef __WASTE_CONTAINER__
#define __WASTE_CONTAINER__

#include "config.h"
#include "model/HWPlatform.h"

class WasteContainer {

public:
  WasteContainer(HWPlatform* hw);
  void init();

  bool isFull();  
  bool isAvailable();
  bool isInMaintenance();
  void reset();
  void setMaintenance();
   
  int getWasteLevelPercentage();
  float getCurrentTemperature();

  void startOpeningDoor();
  void stopOpeningDoor();
  void startClosingDoor();
  void stopClosingDoor();
  void startOpeningForDischarging();
  void stopOpeningForDischarging();
  void startClosingForDischarging();
  void stopClosingForDischarging();

  void notifyDischargingCompleted();
  void notifyMaintenanceCompleted();  

  void sync();

private:
  bool sensorsCanBeUsed();

  HWPlatform* pHW;

  int wasteLevelPercentage;
  float currentTemp;
  bool isAvail; 
  bool _isFull;
  float lastDistance;
  float lastTemperature;
};

#endif
