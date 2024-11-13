#include "Scheduler.h"
#include "BlinkTask.h"
#include "PrintTask.h"

Scheduler sched;

void setup(){

  Serial.begin(9600);
  sched.init(50);
 
  Task* t0 = new BlinkTask(13);
  t0->init(150);

  Task* t1 = new PrintTask();
  t1->init(500);
  
  sched.addTask(t0);
  sched.addTask(t1);
}

void loop(){
  sched.schedule();
}
