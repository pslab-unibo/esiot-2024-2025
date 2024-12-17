#ifndef __WASTE_DISPOSAL_TASK__
#define __WASTE_DISPOSAL_TASK__

#include "kernel/Task.h"
#include "model/WasteContainer.h"
#include "model/UserPanel.h"

class WasteDisposalTask: public Task {

public:
  WasteDisposalTask(WasteContainer* pContainer, UserPanel* pPanel); 
  void tick();

private:  
  void setState(int state);
  long elapsedTimeInState();
  void log(const String& msg);
  
  bool checkAndSetJustEntered();
  
  enum { READY, DOOR_OPENING, SPILLING, DOOR_CLOSING, WASTE_RECEIVED, FULL, SLEEPING, MAINTENANCE} state;
  long stateTimestamp;
  bool justEntered;

  WasteContainer* pContainer;
  UserPanel* pPanel;
};

#endif