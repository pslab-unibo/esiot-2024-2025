#include "tasks/OperatorManTask.h"
#include <Arduino.h>
#include "config.h"
#include "kernel/Logger.h"

#define DISCHARGE_TIME 5000
#define OPENING_DISCHARGING_TIME 1000
#define CLOSING_DISCHARGING_TIME 1000

OperatorManTask::OperatorManTask(WasteContainer* pContainer, Dashboard* pDashboard): 
    pContainer(pContainer), pDashboard(pDashboard){
    setState(NORMAL);
}
  
void OperatorManTask::tick(){
    pDashboard->sync();
    pDashboard->notifyNewState();
    switch (state){    
    case NORMAL: {
        if (this->checkAndSetJustEntered()){
            Logger.log(F("[OM] normal."));
        }
        if (pContainer->isInMaintenance()){
            setState(WAITING_FOR_MAINTENANCE);
        } else if (pContainer->isFull()){
            setState(WAITING_FOR_DISCHARGING);
        }
        break;
    }
    case WAITING_FOR_DISCHARGING: {
        if (this->checkAndSetJustEntered()){
            Logger.log(F("[OM] waiting for disch."));
        }
        if (pDashboard->checkAndResetDischargeRequest()){
            Logger.log(F("Discharging request"));
            setState(OPENING_DISCHARGING);
        }
        break;
    }
    case OPENING_DISCHARGING: {
        if (this->checkAndSetJustEntered()){
            Logger.log(F("[OM] open discharging."));
            pContainer->startOpeningForDischarging();
        }
        if (elapsedTimeInState() > OPENING_DISCHARGING_TIME){
            pContainer->stopOpeningForDischarging();
            setState(DISCHARGING);
        }
       break;
    }
    case DISCHARGING: {
        if (this->checkAndSetJustEntered()){
            Logger.log(F("[OM] discharging."));
        }
        if (elapsedTimeInState() > DISCHARGE_TIME){
            setState(CLOSING_DISCHARGING);
        }
        break;
    }
    case CLOSING_DISCHARGING: {
        if (this->checkAndSetJustEntered()){
            pContainer->startClosingForDischarging();
            Logger.log(F("[OM] close discharging."));
        }
        if (elapsedTimeInState() > CLOSING_DISCHARGING_TIME){
            pContainer->stopClosingForDischarging();
            pContainer->notifyDischargingCompleted();
            setState(NORMAL);
        }
        break;
    }
    case WAITING_FOR_MAINTENANCE: {
        if (this->checkAndSetJustEntered()){
            Logger.log(F("[OM] waiting for maintenance."));
        }
        if (pDashboard->checkAndResetMaintenanceDone()){
            Logger.log(F("Maintenance done"));
            pContainer->notifyMaintenanceCompleted();
            setState(NORMAL);
        }
        break;
    }
    }
}


void OperatorManTask::setState(int s){
    state = s;
    stateTimestamp = millis();
    justEntered = true;
}

long OperatorManTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}

bool OperatorManTask::checkAndSetJustEntered(){
    bool bak = justEntered;
    if (justEntered){
      justEntered = false;
    }
    return bak;
}
