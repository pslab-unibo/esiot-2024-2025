#include "ContainerHealthCheckTask.h"
#include <Arduino.h>
#include "config.h"
#include "kernel/Logger.h"

#define MAXTEMP 30
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
        /*
        static int i = 0;
        i++;
        if (i % 50 == 0){
            Logger.log("Temp: " + String(pContainer->getCurrentTemperature()));
        }
        */
       /*
        if (pContainer->getCurrentTemperature() > MAXTEMP){
            setState(PREALARM);
        }
        */
        if (elapsedTimeInState() > 10000){
            setState(PREALARM);
        }
        break;
    }
    case PREALARM: {        
        if (this->checkAndSetJustEntered()){
            Logger.log(F("[CHC] pre-alarm"));
        }
        /*
        if (pContainer->getCurrentTemperature() < MAXTEMP){
            setState(NORMAL);
        }
        if (elapsedTimeInState() > MAXTEMPTIME){
            setState(ALARM);
        }*/
        if (elapsedTimeInState() > 10000){
            setState(ALARM);
        }
        break;       
    }
    case ALARM: {
        if (this->checkAndSetJustEntered()){
            Logger.log(F("[CHC] alarm"));
            pContainer->setMaintenance();
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
