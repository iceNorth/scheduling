// schedulingMethods.h

#ifndef _SCHEDULING_METHODS_H
#define _SCHDEULING_METHODS_H

#include<vector>
#include"taskNode.h"

void FCFS(std::vector<TaskNode> taskQ);
void speedupBased(std::vector<TaskNode> taskQ);

#endif
