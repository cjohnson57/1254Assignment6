#include <iostream>
#include "Queue.h"
#include "Task.h"
#include <fstream>
#include <string>

using namespace std;

struct Core
{
	bool inUse;
	int idleTime;
	int remainingTaskTime;
	Task currentTask;
	Core()
	{
		inUse = false;
		idleTime = 0;
		remainingTaskTime = 0;
	}
};

int main(int argc, char** argv)
{
	//argc = 2; //For testing
	if (argc < 2)
	{
		cout << "You must enter a filename by command line." << endl;
		cout << "The command should be as follows:" << endl;
		cout << argv[0] << " [file containing roster]." << endl;
		return 0;
	}

	/* read file */
	ifstream f;
	f.open(argv[1]); //should be argv[1], for testing "C:\\Users\\Caleb\\Desktop\\1254 Projects\\prog6\\sampleTaskList.txt"
	if (!f)
	{
		cout << "File " << argv[1] << " does not exist." << endl;
		return 0;
	}

	int CoresCount, TasksCount;
	f >> CoresCount >> TasksCount;
	Queue<Task> q;

	Core * cores = new Core[CoresCount];
	int * taskIds = new int[TasksCount];
	int * taskRequestTimes = new int[TasksCount];

	for (int i = 0; i < TasksCount; i++)
	{
		int ID, StartTime, Duration;
		f >> ID >> StartTime >> Duration;
		Task tempTask(ID, StartTime, Duration);
		q.Enqueue(tempTask);
		taskIds[i] = ID;
		taskRequestTimes[i] = StartTime;
	}

	bool coresInUse = true;
	int clock = 0;
	int totalWaitingTime = 0;
	string log = "";

	while (coresInUse || q.getLength() > 0)
	{
		for (int i = 0; i < TasksCount; i++)
		{
			if (taskRequestTimes[i] == clock)
			{
				log += "Task " + to_string(taskIds[i]) + " was requested at time " + to_string(clock) + "\n";
			}
		}
		coresInUse = false;
		for (int i = 0; i < CoresCount; i++)
		{
			Task tempTask(-1, -1, -1); //Since an if statement relies on tempTask it must be created even if there are none left in q. So I set the id to -1 so the program knows it's not a real task.
			if (q.getLength() > 0)
			{
				tempTask = q.Front();
			}

			if (cores[i].inUse == false && tempTask.getRequestTime() <= clock && tempTask.getId() != -1) //Begin new task
			{
				q.Dequeue();
				coresInUse = true;
				cores[i].currentTask = tempTask;
				cores[i].inUse = true;
				cores[i].remainingTaskTime = tempTask.getDuration();
				tempTask.setStartTime(clock);
				totalWaitingTime += tempTask.calculateWaitingTime();
				log += "Task " + to_string(tempTask.getId()) + " began on core " + to_string(i) + " at time " + to_string(clock) + " after a wait of " + to_string(tempTask.calculateWaitingTime()) + "\n";
				cores[i].remainingTaskTime--;
			}
			else if (cores[i].inUse == false) //Core is not in use, but there is no task waiting 
			{
				cores[i].idleTime++;
			}
			else if (cores[i].inUse == true && cores[i].remainingTaskTime > 0) //Core is in use, task time is decremented
			{
				cores[i].remainingTaskTime--;
				coresInUse = true;
			}
			else if (cores[i].inUse == true && cores[i].remainingTaskTime == 0) //Finish task
			{
				log += "Task " + to_string(cores[i].currentTask.getId()) + " finished on core " + to_string(i) + " at time " + to_string(clock) + "\n";
				cores[i].inUse = false;
			}
		}
		clock++;
	}
	int totalIdleTime = 0;
	for (int i = 0; i < CoresCount; i++)
	{
		totalIdleTime += cores[i].idleTime;
	}

	log += "Total task waiting time = " + to_string(totalWaitingTime) + "\n";
	log += "Average task waiting time = " + to_string(static_cast<double>(totalWaitingTime) / TasksCount) + "\n";
	log += "Total core idle time = " + to_string(totalIdleTime) + "\n";
	log += "Average core idle time = " + to_string(static_cast<double>(totalIdleTime) / CoresCount) + "\n";

	ofstream g;
	g.open("log.txt");
	g << log;
	g.close();

	delete[] cores;
	delete[] taskIds;
	delete[] taskRequestTimes;
}