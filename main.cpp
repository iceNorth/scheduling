// main.cpp

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<list>
#include<iterator>
#include<algorithm>
#include<stdlib.h>
#include "taskNode.h"
#include "schedulingMethods.h"
#include "compare.h"

using namespace std;

/*
bool arriveTimeCMP(TaskNode a, TaskNode b)
{
  return a.arriveTime < b.arriveTime;
}

bool CPUexecutionTimeCMP(TaskNode a, TaskNode b)
{
  return a.CPUexecutionTime < b.CPUexecutionTime;
}

bool GPUexecutionTimeCMP(TaskNode a, TaskNode b)
{
  return a.GPUexecutionTime < b.GPUexecutionTime;
}

bool priorityCMP(TaskNode a, TaskNode b)
{
  return a.priority < b.priority;
}

bool speedupCMP(TaskNode a, TaskNode b)
{
  return a.speedup < b.speedup;
}

*/

// read input data
void initialization(vector<TaskNode>& taskqueue)
{
  ifstream infile("data.txt");
  
  if(infile == NULL){
    cout << "ERROR: fail to open data.txt" << endl;
    exit(0);
  }

  long aT, cpuT, gpuT, prio;
  int i = 0;
  while(infile >> aT >> cpuT >> gpuT >> prio){
  /*while(infile >> taskqueue[i].arriveTime >> taskqueue[i].CPUexecutionTime 
	>> taskqueue[i].GPUexecutionTime >> taskqueue[i].priority){*/
    //cout << "aT: " << aT << " ";
    //cout << "cpuT: " << cpuT << " ";
    //cout << "gpuT: " << gpuT << " ";
    //cout << "prio: " << prio << " ";
    //cout << endl;
    
    taskqueue.push_back(TaskNode(aT, cpuT, gpuT, prio));
    
  }
  
}


/*
void PRINT_NODE_INFO(vector<TaskNode>& node)
{
  vector<TaskNode>::iterator pos1;
  for (pos1 = node.begin(); pos1 != node.end(); ++pos1){
    cout << (*pos1).arriveTime << " ";
    cout << (*pos1).CPUexecutionTime << " ";
    cout << (*pos1).GPUexecutionTime << " ";
    cout << (*pos1).priority << " ";
    cout << (*pos1).speedup << " ";
    cout << endl;
  }
}
*/


long CPUsum(vector<TaskNode>& node)
{
  vector<TaskNode>::iterator pos;
  long sum = 0;
  for(pos = node.begin(); pos != node.end(); ++pos){
    sum += (*pos).CPUexecutionTime;
  }
  return sum;
}

long GPUsum(vector<TaskNode>& node)
{
  vector<TaskNode>::iterator pos;
  long sum = 0;
  for(pos = node.begin(); pos != node.end(); ++pos){
    sum += (*pos).GPUexecutionTime;
  }
  return sum;
}





int main()
{
  vector<TaskNode> taskQ;
  list<TaskNode> taskPool;
  list<TaskNode> CPUQueue;
  list<TaskNode> GPUQueue; 

  long clock;
 
  initialization(taskQ);
 
  print_info <vector<TaskNode> >(taskQ);
  cout << endl;

  cout << "sort according to arriveTime" << endl;
  sort(taskQ.begin(), taskQ.end(), arriveTimeCMP);
  
  cout << endl;

  cout << endl;
  cout << "Here using my template..." << endl;
  print_info <vector<TaskNode> >(taskQ);
  cout << endl << endl;

  cout << "sort according to CPU execution time" << endl;
  sort(taskQ.begin(), taskQ.end(), CPUexecutionTimeCMP);
  print_info<vector<TaskNode> >(taskQ);
  cout << endl;

  cout << "sort according to GPU execution time" << endl;
  sort(taskQ.begin(), taskQ.end(), GPUexecutionTimeCMP);
  print_info<vector<TaskNode> >(taskQ);
  cout << endl;

  cout << "sort according to priority" << endl;
  sort(taskQ.begin(), taskQ.end(), priorityCMP);
  print_info<vector<TaskNode> >(taskQ);
  cout << endl;

  cout << "sort according to speedup" << endl;
  sort(taskQ.begin(), taskQ.end(), speedupCMP);
  print_info<vector<TaskNode> >(taskQ);
  cout << endl;

  cout << "CPU time:" << endl;
  cout << CPUsum(taskQ) << endl;

  cout << "GPU time:" << endl;
  cout << GPUsum(taskQ) << endl;

  cout << "the size of taskQ is: " << taskQ.size() << endl;

  //vector<TaskNode> coll;
  //coll = taskQ;
  //cout << "new vector coll" << endl;
  //PRINT_NODE_INFO(coll);
  //cout << endl;

  FCFS(taskQ);

  cout << endl << endl << "After scheduling, the taskQ is: " << endl;
  print_info(taskQ);

  cout << endl << "speedup based taskQ:" << endl;
  speedupBased(taskQ);
  
}
