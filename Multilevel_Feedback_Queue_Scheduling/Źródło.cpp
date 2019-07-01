#include <iostream>
#include <vector>
#include <stdlib.h>    
#include <time.h> 
using namespace std;

#define x1 9 // RoundRobin time slice value for first level queue
#define x2 16 //                         ...for second level queue
			  // third level queue is executing by FCFS algorithm
struct process {
	process() : start_waiting_time(arrival_time) {}
	int pid;
	int arrival_time;
	int burst_time;
	int start_waiting_time;
	int end_waiting_time;
};
void queue_RR(vector <process> &q, vector <process> &q_next, int time,int &entire_time,int &sum) {
	
	if (!empty(q)) {
		if (q[0].burst_time <= time) {/// burst time < 10
			q[0].end_waiting_time = entire_time;
			sum = +(q[0].end_waiting_time - q[0].start_waiting_time);
			cout << "P" << q[0].pid << " bursting time:" << q[0].burst_time <<" terminated "<< endl ;
			entire_time += q[0].burst_time;
			q.erase(q.begin());
		}
		else {
			q[0].end_waiting_time = entire_time;
			sum = +(q[0].end_waiting_time - q[0].start_waiting_time);
			cout << "P" << q[0].pid << " bursting time:" << time << endl ;
			q[0].burst_time -=time;
			entire_time += time;
			q[0].start_waiting_time = entire_time;
			q_next.push_back(q[0]);
			
			q.erase(q.begin());
		}

	}
}
void queue_FCFS(vector <process> &q,  int &entire_time,int &sum) {
	if (!empty(q)) {
			sum = +(entire_time - q[0].end_waiting_time);
			entire_time += q[0].burst_time;
			cout <<"P"<< q[0].pid << " bursting time:" << q[0].burst_time << " terminated" << endl ;
			q.erase(q.begin());
	}
}
int main()
{
	int total;
	cout << "Enter number of processes:" << endl;
	cin >> total;
	cout << endl;
	struct process* p = new process[total];
	
	p[0].pid = 0;
	p[0].arrival_time = 0;
	p[0].burst_time = 20;
	srand(time_t(NULL));
	cout << "Process" << "   " << "Arrival time" << "   " << "Burst time" << endl;
	cout << "P" << p[0].pid << "             " << p[0].arrival_time << "             " << p[0].burst_time << endl;
	for (int i = 1; i < total; i++) {
		p[i].pid = i;
		p[i].arrival_time = p[i-1].arrival_time+rand() % 20;
		p[i].burst_time = rand() % 40 + 1;
		cout << "P" << p[i].pid << "             " << p[i].arrival_time << "            "<<p[i].burst_time << endl;
	}
	

	int sum= 0;
	vector <process> q1, q2, q3;
	//vector<int*> q1 = vector<int*>();
	int i=1, time=0;
	q1.push_back(p[0]);
	while ((!empty(q1)||!empty(q2)|| !empty(q3))) {
		if(!empty(q1)) cout << endl << "Queue1:" << endl;
		while (1) {
			queue_RR(q1, q2, x1, time,sum);
			if (i < total&&p[i].arrival_time < time) {
				//p[i].start_executing_time = time;
				q1.push_back(p[i]);
				i++;
				//if (i == total) break;
			}
			else if (empty(q1)) break;
		}
		
		if (!empty(q2)) cout <<endl<<"Queue2:" << endl;
		while (1) { 
			
			//cout << "q2 " << q2[0].pid << endl;
	
			queue_RR(q2, q3, x2, time,sum);
			if (i < total&&p[i].arrival_time < time) {
				//p[i].start_executing_time = time;
				q1.push_back(p[i]);
				i++;

				break;
			}
			else if (empty(q2)) {
				if (!empty(q3)) cout << endl << "Queue3:" << endl;
				while (1) {
					//	cout << "q3 " << q3[0].pid << endl;
					//if (i == total) break;
					queue_FCFS(q3, time,sum);
					if (i < total&&p[i].arrival_time < time) {
						//p[i].start_executing_time = time;
						q1.push_back(p[i]);
						i++;
						break;
					}
					else if (empty(q3)) break;
					
				}

			}
			if (empty(q3)) break;
			
		}
		
	}
	
	cout << endl<< "Avarage waiting time:" <<(float) sum / total << endl;
	system("pause");
	return 0;
}