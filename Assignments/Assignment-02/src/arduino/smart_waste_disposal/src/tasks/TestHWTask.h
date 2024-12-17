#ifndef __TEST_HW_TASK__
#define __TEST_HW_TASK__

#include "kernel/Task.h"
#include "model/HWPlatform.h"

class TestHWTask: public Task {

public:
  TestHWTask(HWPlatform* pHW); 
  void tick();

private:  
  HWPlatform* pHW;
};

#endif