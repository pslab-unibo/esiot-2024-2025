#include "tasks/TestHWTask.h"
#include <Arduino.h>
#include "config.h"


TestHWTask::TestHWTask(HWPlatform* pHW): pHW(pHW){
}
  
void TestHWTask::tick(){
    pHW->test();
}


