// taskNode.h
#ifndef _TASK_NODE
#define _TASK_NODE

#include<iostream>

using namespace std;

class TaskNode {
  public:
  //private:
    long arriveTime;
    long CPUexecutionTime;
    long GPUexecutionTime;
    long priority;
    long turnaroundTime;
    double speedup;
    enum tag{cpu, gpu, unvisited};
    tag deviceQ;
  //public:
    TaskNode(long arriveT=999, long CPUexeT=0, long GPUexeT=0, long pri=0)
	: arriveTime(arriveT), CPUexecutionTime(CPUexeT), 
	GPUexecutionTime(GPUexeT), priority(pri){
      //arriveTime = arriveT;
      //CPUexecutionTime = CPUexeT;
      //GPUexecutionTime = GPUexeT;
      //priority = pri;
      turnaroundTime = 0;
      speedup = double(CPUexecutionTime) / double(GPUexecutionTime);
      deviceQ = unvisited;
    }

    friend ostream& operator<<(ostream& os, const TaskNode& tasknode) {
      os << tasknode.arriveTime << "\t" << tasknode.CPUexecutionTime << "\t"
	 << tasknode.GPUexecutionTime << "\t" << tasknode.priority << "\t"
	 << tasknode.speedup << "\t" << tasknode.turnaroundTime;
      return os;
    }

    ~TaskNode() {}
};

template <class T> void print_info(T & task)
{
    typename T::iterator pos;

  for (pos=task.begin(); pos!=task.end(); ++pos){
    cout << (*pos).arriveTime << " ";
    cout << (*pos).CPUexecutionTime << " ";
    cout << (*pos).GPUexecutionTime << " ";
    cout << (*pos).priority << " ";
    cout << (*pos).speedup << " ";
    cout << (*pos).turnaroundTime << " ";
    if ((*pos).deviceQ == TaskNode::unvisited)
        cout << "unvisited";
    else if ((*pos).deviceQ == TaskNode::cpu)
        cout << "CPU";
    else if ((*pos).deviceQ == TaskNode::gpu)
        cout << "GPU";
    cout << std::endl;
  }
}


/*
struct TaskNode {
  long arriveTime;
  long CPUexecutionTime;
  long GPUexecutionTime;
  long priority;
};
*/
#endif 
