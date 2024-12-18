#include "ContainerHealthCheckTask.h"
#include <Arduino.h>
#include "config.h"
#include "kernel/Logger.h"

#define MAXTEMP 100
#define MAXTEMPTIME 10000

ContainerHealthCheckTask::ContainerHealthCheckTask(WasteContainer* pContainer): 
    pContainer(pContainer){
    setState(NORMAL);
}
  
void ContainerHealthCheckTask::tick(){
    pContainer->sync();
    switch (state){    
    case NORMAL: {
        if (this->checkAndSetJustEntered()){
            Logger.log(F("[CHC] normal"));
            pContainer->reset();
        }
        if (pContainer->getCurrentTemperature() > MAXTEMP){
            setState(PREALARM);
        }
        break;
    }
    case PREALARM: {        
        if (this->checkAndSetJustEntered()){
            Logger.log(F("[CHC] pre-alarm"));
        }
        
        if (pContainer->getCurrentTemperature() < MAXTEMP){
            setState(NORMAL);
        } else if (elapsedTimeInState() > MAXTEMPTIME){
            setState(WAITING_MAINTENANCE);
        }
        break;       
    }
    case WAITING_MAINTENANCE: {
        if (this->checkAndSetJustEntered()){
            Logger.log(F("[CHC] alarm"));
            pContainer->setMaintenance();
        }

        if (pContainer->isAvailable()){
            setState(NORMAL);
        }
        break;
    }    
    }
}

void ContainerHealthCheckTask::setState(int s){
    state = s;
    stateTimestamp = millis();
    justEntered = true;
}

long ContainerHealthCheckTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}

bool ContainerHealthCheckTask::checkAndSetJustEntered(){
    bool bak = justEntered;
    if (justEntered){
      justEntered = false;
    }
    return bak;
}
