/*
 * SMART CAR WASHING - Assignment #02 - ESIOT a.y. 2023-2024
 * 
 * Solution sketch by AR
 * 
 */
#include <Arduino.h>
#include "config.h"
#include "kernel/Scheduler.h"
#include "kernel/Logger.h"
#include "kernel/MsgService.h"
#include "model/HWPlatform.h"
#include "model/UserPanel.h"
#include "model/Dashboard.h"
#include "tasks/TestHWTask.h"
#include "tasks/WasteDisposalTask.h"
#include "tasks/ContainerHealthCheckTask.h"
#include "tasks/OperatorManTask.h"

Scheduler sched;

HWPlatform* pHWPlatform;
UserPanel* pUserPanel;
WasteContainer* pWasteContainer;
Dashboard* pDashboard; 

void setup() {
  MsgService.init();
  sched.init(100);

  Logger.log(":::::: Smart Waste Disposal ::::::");
  
  pHWPlatform = new HWPlatform();
  pHWPlatform->init();

  pUserPanel = new UserPanel(pHWPlatform);
  pUserPanel->init();

  pWasteContainer = new WasteContainer(pHWPlatform);
  pWasteContainer->init();

  pDashboard = new Dashboard(pWasteContainer);
  pDashboard->init();

/*
  Task* pTestHWTask = new TestHWTask(pHWPlatform);
  pTestHWTask->init(1000);
*/
  Task* pWasteDisposalTask = new WasteDisposalTask(pWasteContainer, pUserPanel);
  pWasteDisposalTask->init(50);

  Task* pContainerHealthCheckTask = new ContainerHealthCheckTask(pWasteContainer);
  pContainerHealthCheckTask->init(100);

  Task* pOperatorManTask = new OperatorManTask(pWasteContainer, pDashboard);
  pOperatorManTask->init(200);

  sched.addTask(pContainerHealthCheckTask);
  sched.addTask(pWasteDisposalTask);
  sched.addTask(pOperatorManTask);

}

void loop() {
    sched.schedule();
}