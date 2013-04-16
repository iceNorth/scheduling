// schedulingMethod.cpp

#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
#include<iterator>
#include<sys/time.h>
#include"taskNode.h"
#include"compare.h"

using namespace std;

/*
void print_info(list<TaskNode> coll)
{
  list<TaskNode>::iterator pos;

  for (pos=coll.begin(); pos!=coll.end(); ++pos){
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
*/


long accumulateTimeCPU = 0;
long accumulateTimeGPU = 0;

struct timeval time;

long currentTime()
{
  gettimeofday(&tv, NULL);
  return (time.tv_sec * 1000000 + time.tv_usec);
}

void init(list<TaskNode>& coll)
{
  accumulateTimeCPU = 0;
  accumulateTimeGPU = 0;

  list<TaskNode>::iterator pos;

  for(pos=coll.begin(); pos!=coll.end(); ++pos){
    (*pos).turnaroundTime = 0;
  }
}

//long accumulateTimeCPU=0;
//long accumulateTimeGPU=0;

long RunonCPU(TaskNode& task)
{
  if(task.deviceQ == TaskNode::unvisited){
    accumulateTimeCPU += task.CPUexecutionTime;
    task.turnaroundTime = accumulateTimeCPU - task.arriveTime;
    task.deviceQ = TaskNode::cpu;
  }
  else if (task.deviceQ == TaskNode::cpu){
    cout << "warning: this task already done." << endl;
    //continue;
  }
  else if (task.deviceQ == TaskNode::gpu){
    cout << "warning: queuing in the wrong queue. The task should go to GPU queue" << endl;
  }
  else{
    cout << "Error: in deliver task." << endl;
    exit(1);
  }
}

long RunonGPU(TaskNode& task)
{
  if(task.deviceQ == TaskNode::unvisited){
    accumulateTimeGPU += task.GPUexecutionTime;
    task.turnaroundTime = accumulateTimeGPU - task.arriveTime;
    task.deviceQ = TaskNode::gpu;
  }
  else if (task.deviceQ == TaskNode::gpu){
    cout << "warning: this task already done." << endl;
    //continue;
  }
  else if (task.deviceQ == TaskNode::cpu){
    cout << "warning: queuing in the wrong queue. The task should go to CPU queue." << endl;
  }
  else{
    cout << "Error: in deliver task." << endl;
    exit(1);
  }
}

double averageTurnaroundTime(list<TaskNode> task, TaskNode::tag deviceQ)
{
  list<TaskNode>::iterator pos;
  //int cpuTaskCount = 0;
  //int gpuTaskCount = 0;
  int count = 0;
  long turnaroundTimeSum = 0;

  for(pos=task.begin(); pos!=task.end(); ++pos){
    if ((*pos).deviceQ == deviceQ){
      turnaroundTimeSum += (*pos).turnaroundTime;
      count++;
    }
    else
      continue;
  }
  cout << "deviceQ: " << deviceQ << endl;
  cout << "task count: " << count << endl;
  cout << "total turnaround time: " << endl;
  return (double)turnaroundTimeSum/count;
    
}


void FCFS(std::vector<TaskNode> taskQ)
{
  list<TaskNode> taskPool;
  list<TaskNode>::iterator pos;


  taskPool.assign(taskQ.begin(),taskQ.end());
  cout << "assign list from vector" << endl;
  //print_info(taskPool);
  print_info<list<TaskNode> >(taskPool);
  cout << endl;

  // sort the task pool by arriving time
  cout << "sorting according to arrive time" << endl;
  taskPool.sort(arriveTimeCMP);
  //print_info(taskPool);
  print_info<list<TaskNode> >(taskPool);
  cout << endl;

  // Initialization
  init(taskPool);

/*
  // test overload operator "<<"
  cout << "look at here" << endl;
  for(pos=taskPool.begin(); pos!=taskPool.end(); ++pos){
    cout << *pos << endl;
    
  }

*/

/*
  // Test copy function
  TaskNode node1;
  pos = taskPool.begin();
  node1 = *pos;
  cout << "node1 arriveTime: " << node1.arriveTime << endl;
  cout << "node1 CPUexecutionTime: " << node1.CPUexecutionTime << endl;
  cout << "node1 GPUexecutionTime: " << node1.GPUexecutionTime << endl;
  cout << "node1 priority: " << node1.priority << endl;
  cout << "node1 speedup: " << node1.speedup << endl;
  cout << "node1 turnaroundTime: " << node1.turnaroundTime << endl; 
*/

  cout << "start scheduling..." << endl << endl;
  TaskNode task;
  for(pos=taskPool.begin(); pos!=taskPool.end(); ++pos){
    if (accumulateTimeGPU <= accumulateTimeCPU){
      // running on GPU device
      RunonGPU(*pos);
    }
    else{
      // CPU shceduling
      RunonCPU(*pos);
    }
  }

  cout << "after FCFS scheduling..." << endl;
  print_info(taskPool);
  cout << endl << endl;

  cout << "CPU average turnaround time: " << endl;
  cout << averageTurnaroundTime(taskPool, TaskNode::cpu);
  cout << endl;

  cout << "GPU average turnaround time: " << endl;
  cout << averageTurnaroundTime(taskPool, TaskNode::gpu);
  cout << endl;

/*
  // some other test... basically useless
  cout << "here use member function front()" << endl;
  while(!taskPool.empty()){
    cout << "front of the list " << taskPool.front() << endl;
    taskPool.pop_front();
  }

  cout << "output the list again" << endl;
  print_info(taskPool);
  cout << "the taskPool size is: " << taskPool.size() << endl;
  cout << "the taskPool is empty: " << taskPool.empty() << endl;
 
*/
}


void speedupBased(std::vector<TaskNode> taskQ)
{
  list<TaskNode> taskPool;
  list<TaskNode>::iterator pos;

  accumulateTimeCPU = 0;
  accumulateTimeGPU = 0;

  taskPool.assign(taskQ.begin(),taskQ.end());
  cout << "assign list from vector" << endl;
  print_info<list<TaskNode> >(taskPool);
  cout << endl;

  // sort the task pool by execution time
  cout << "sorting according to speedup" << endl;
  taskPool.sort(speedupCMP);
  //print_info(taskPool);
  print_info<list<TaskNode> >(taskPool);
  cout << endl;

  // Initialization
  init(taskPool);

    cout << "start speedup-based scheduling..." << endl << endl;

///// should change something here

  //TaskNode task;
/*
  for(pos=taskPool.begin(); pos!=taskPool.end(); ++pos){
    if (accumulateTimeGPU <= accumulateTimeCPU){
      // running on GPU device
      RunonGPU(*pos);
    }
    else{
      // CPU shceduling
      RunonCPU(*pos);
    }
  }
*/

  list<TaskNode> taskPoolNew;
  //list<TaskNode>::iterator pos;
  list<TaskNode>::iterator posB = taskPool.begin();
  list<TaskNode>::iterator posE = taskPool.end();
  --posE;
  while(!taskPool.empty()){
    //posB = taskPool.begin();
    //posE = taskPool.end();
    if(accumulateTimeGPU <= accumulateTimeCPU){
      cout << "before GPU" << endl;
      if(accumulateTimeGPU <= (*posB).arriveTime){
        RunonGPU(*posB);
        //taskPool.pop_front();
        taskPoolNew.push_back(*posB);
        posB = taskPool.erase(posB);
        posB = taskPool.begin();
        cout << "GPU" << endl;
	cout << "size of taskPool after GPU: " << taskPool.size() << endl;
	cout << "GPU accumulate time: " << accumulateTimeGPU << endl;
      }
      else{
 	cout << "GPU continue..." << endl;
        cout << "size of taskPool (GPU continue): " << taskPool.size() << endl;
        posB++;
        continue;
      }
    }
    else {
      cout << "before CPU" << endl;
      if (accumulateTimeCPU <= (*posE).arriveTime){
        RunonCPU(*posE);
        //RunonCPU(taskPool.back());
        //taskPool.pop_back();
        taskPoolNew.push_back(*posE);
        posE = taskPool.erase(posE);
        posE = taskPool.end();
        --posE;
        cout << "CPU" << endl;
    	cout << "size of taskPool after CPU: " << taskPool.size() << endl;
 	cout << "CPU accumulate time: " << accumulateTimeCPU << endl;
	cout << "posE = " << (*posE) << endl;
      }
      else {
        cout << "CPU continue..." << endl;
 	cout << "size of taskPool (CPU continue): " << taskPool.size() << endl;
        posE--;
        cout << "*posE: " << *posE << endl;
	cout << "*posE arriveTime: " << (*posE).arriveTime << endl;
        continue;
      }
    }
  }

  cout << "after Speedup based scheduling..." << endl;
  cout << "origianl task Pool:" << endl;
  print_info(taskPool);
  cout << "New task Pool: " << endl;
  print_info(taskPoolNew);
  cout << endl << endl;

  cout << "CPU average turnaround time: " << endl;
  cout << averageTurnaroundTime(taskPoolNew, TaskNode::cpu);
  cout << endl;

  cout << "GPU average turnaround time: " << endl;
  cout << averageTurnaroundTime(taskPoolNew, TaskNode::gpu);
  cout << endl;


}


void shortestJobFirst(std::vector<TaskNode> taskQ)
{
  list<TaskNode> taskPool;
  list<TaskNode>::iterator pos;

  accumulateTimeCPU = 0;
  accumulateTimeGPU = 0;     

  taskPool.assign(taskQ.begin(),taskQ.end());
  cout << "assign list from vector" << endl;
  print_info<list<TaskNode> >(taskPool);
  cout << endl;

  // sort the task pool by execution time
  cout << "sorting according to arrive time" << endl;
  taskPool.sort(arriveTimeCMP);
  //print_info(taskPool);
  print_info<list<TaskNode> >(taskPool);
  cout << endl;

  // Initialization
  init(taskPool);

}
