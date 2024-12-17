#ifndef __DASHBOARD__
#define __DASHBOARD__

#include "config.h"
#include "HWPlatform.h"
#include "model/WasteContainer.h"

class Dashboard {

public:
  Dashboard(WasteContainer* pContainer);

  void init();
  
  void notifyNewState();
  
  bool checkAndResetDischargeRequest();
  bool checkAndResetMaintenanceDone();

  void sync();

 private:
  WasteContainer* pContainer;
  bool dischargeCmdRequested;
  bool maintenanceDoneNotified;
};

#endif
