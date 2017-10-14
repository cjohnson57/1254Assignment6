/*
	Author: W. Douglas Lafield
	Task.h
*/
#ifndef _TASK_GUARD
#define _TASK_GUARD 1

//#include <iostream>

using namespace std;

class Task
{
	private:
		int id;
		int requestTime;
		int startTime;
		int duration;
	public:
		/* constructers */
		Task(int i, int r, int d);
		Task(int i, int r, int d, int s);
		
		/* generic constructer */
		Task();
		
		/* destructer */
		~Task();

		int		getDuration() const;
		/* returns how long the task is to take */
		
		int 	getId() const;
		/* returns the task's id */
		
		int		getRequestTime() const;
		/* returns the time that the task is requested */
		
		int		getStartTime() const;
		/* returns the time that the task started */
		
		void	setStartTime(int t);
		/* set the time that the task started */
		
		int		calculateWaitingTime();
		/* calculates waiting time (after start time is set) */

		
		
		
		//string toString() const;
		/* show the studen't name with the last name first, followed by
		 * the first name, each separated by a comma */
};

#endif
