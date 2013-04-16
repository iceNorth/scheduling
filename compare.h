// compare.h

#ifndef _COMPARE_H
#define _COMPARE_H

#include"taskNode.h"

inline bool arriveTimeCMP(TaskNode a, TaskNode b)
{
  return a.arriveTime < b.arriveTime;
}

inline bool CPUexecutionTimeCMP(TaskNode a, TaskNode b)
{
  return a.CPUexecutionTime < b.CPUexecutionTime;
}

inline bool GPUexecutionTimeCMP(TaskNode a, TaskNode b)
{
  return a.GPUexecutionTime < b.GPUexecutionTime;
}

inline bool priorityCMP(TaskNode a, TaskNode b)
{
  return a.priority < b.priority;
}

inline bool speedupCMP(TaskNode a, TaskNode b)
{
  return a.speedup < b.speedup;
}

#endif
