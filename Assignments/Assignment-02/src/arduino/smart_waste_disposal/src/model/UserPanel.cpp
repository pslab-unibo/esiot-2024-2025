#include "UserPanel.h"
#include <Arduino.h>
#include "config.h"
#include "kernel/Logger.h"
#include "model/HWPlatform.h"

UserPanel::UserPanel(HWPlatform* pHW) {
    pLcd = pHW->getUserPanelLcd();
    pButtonOpen = pHW->getOpenButton();
    pButtonClose = pHW->getCloseButton();
}

void UserPanel::init(){
  pLcd->init();
  pLcd->backlight();
  pLcd->noDisplay();
  turnOnDisplay();
}

void UserPanel::turnOnDisplay(){
  pLcd->display();
  pLcd->clear();
}

void UserPanel::turnOffDisplay(){
  pLcd->noDisplay();
}

void UserPanel::displayReadyToGetWaste(){
  pLcd->clear();
  pLcd->setCursor(0, 0); 
  pLcd->print("PRESS OPEN");
  pLcd->setCursor(0,1);
  pLcd->print("TO ENTER WASTE");
}

void UserPanel::displayGettingWaste(){
  pLcd->clear();
  pLcd->setCursor(0, 0); 
  pLcd->print("PRESS CLOSE");
  pLcd->setCursor(0,1);
  pLcd->print("WHEN DONE");
}

void UserPanel::displayWasteReceived(){
  pLcd->clear();
  pLcd->setCursor(0, 0); 
  pLcd->print("WASTE RECEIVED");
}

void UserPanel::displayContainerFull(){
  pLcd->clear();
  pLcd->setCursor(0, 0); 
  pLcd->print("CONTAINER FULL");
}

void UserPanel::displayOpening(){
  pLcd->clear();
  pLcd->setCursor(0, 0); 
  pLcd->print("OPENING...");
}

void UserPanel::displayClosing(){
  pLcd->clear();
  pLcd->setCursor(0, 0); 
  pLcd->print("CLOSING...");
}

void UserPanel::displayInMaintenance(){
  pLcd->clear();
  pLcd->setCursor(0, 0); 
  pLcd->print("IN MAINTENANCE");
}


void UserPanel::prepareToSleep(){
  pLcd->noDisplay();
}

void UserPanel::resumeFromSleeping(){
  pLcd->display();  
}

bool UserPanel::pressedOpen(){
  return openPressed;
}

bool UserPanel::pressedClose(){
  return closePressed;
}

void UserPanel::sync(){
  pButtonOpen->sync();
  pButtonClose->sync();
  openPressed = pButtonOpen->isPressed();
  closePressed = pButtonClose->isPressed();
}



