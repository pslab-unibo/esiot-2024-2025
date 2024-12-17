#ifndef __CONTAINER_HEALTH_CHECK_TASK__
#define __CONTAINER_HEALTH_CHECK_TASK__

#include "kernel/Task.h"
#include "model/WasteContainer.h"
#include "model/UserPanel.h"

class ContainerHealthCheckTask: public Task {

public:
  ContainerHealthCheckTask(WasteContainer* pContainer); 
  void tick();

private:  
  void setState(int state);
  long elapsedTimeInState();
  void log(const String& msg);
  
  bool checkAndSetJustEntered();
  
  enum { NORMAL, PREALARM, ALARM} state;
  long stateTimestamp;
  bool justEntered;

  WasteContainer* pContainer;
};

#endif