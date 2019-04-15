#include<stdio.h>
#define max 101 //  Size Limit

int n; // Number Of Processess 

/* PCB for the process :-
 pid  :-  Name Of The Process
 arr_time  :-  Arrival Time
 bur_time  :-  Burst Time
 pri   :-  Priority
 fin_time  :-  Completion Time
 start_time  :-  Starting Time
 wait_time  :-  Waiting Time
 turn_around :-  Total TurnAround Time
 
 Variables Which Are Usefull For The pri_queue And Queue
 pri_queue_front :- Priority Queue Front
 pri_queue_rear :- Priority Queue Rear
 queue_front :- Queue Front
 queue_rear :- Queue Rear */

struct info {
    int number;
    char pid[5];
    int arr_time;
    int bur_time;
    int pri;
    int rt;
    int fin_time;
    int start_time;
    int wait_time;
    int turn_around;
};



int pri_queue_front = -1, pri_queue_rear = -1;
int queue_front = -1, queue_rear = -1;

// Declaration of Array of Structures

struct info* pri_queue[max];
struct info* r_queue[max];

/* 
 sorting According to the arrival time and if  arrival time of any two processes are equal then 
 sorting According to their Process Id*/

void sorting(struct info process[]) {
    int i, j;
    struct info temp;

    for (i = 0; i < n; i++) {

        for (j = i; j >= 1; j--) {
            
            if (process[j].arr_time < process[j - 1].arr_time) {

                temp = process[j - 1];
                process[j - 1] = process[j];
                process[j] = temp;
            }
            else if (process[j].arr_time == process[j - 1].arr_time) {

                if (process[j].number < process[j].number) {

                    temp = process[j - 1];
                    process[j - 1] = process[j];
                    process[j] = temp;
                }
            }
        }
    }
}
int pri_queue_Empty() {

    return (pri_queue_front == -1 && pri_queue_rear == -1); // If pri_queue_front and pri_queue_rear both are equal to -1 then Priority Queue is Empty else not empty
}
struct info* pri_queue_top() {

    return pri_queue[pri_queue_front];
}
void loc(struct info *x) {

    int i, j;

    for (i = 0; i <= pri_queue_rear; i++) {

        if (x->pri < pri_queue[i]->pri) {

            for (j = pri_queue_rear + 1; j > i; j--) {

                pri_queue[j] = pri_queue[j - 1];
            }

            pri_queue[i] = x;
            return;
        }
    }
    pri_queue[i] = x;
}
void pri_queue_Push(struct info* x) {

    if (pri_queue_front == -1 && pri_queue_rear == -1) { // If Priority Queue is empty then Increment the both the values to 1

        pri_queue_front++; 
        pri_queue_rear++;
        pri_queue[pri_queue_rear] = x; 
        return;
    }
    else {

        loc(x); 
    }

    pri_queue_rear++;
}
void pri_queue_Pop() {

    int i;

    if (pri_queue_front == -1 && pri_queue_rear == -1) {

        return;
    }
    for (i = 0; i < pri_queue_rear; i++) {

        pri_queue[i] = pri_queue[i + 1];
    }

    pri_queue_rear--;

    if (pri_queue_rear == -1)
        pri_queue_front = -1;
}
int ready_queue_Empty() {

    return (queue_front == -1 && queue_rear == -1);
}
struct info* ready_queue_front() {
    return r_queue[queue_front];
}
void ready_queue_push(struct info* x) {

    if (queue_front == -1 && queue_rear == -1) {

        queue_front++;
        queue_rear++;
        r_queue[queue_rear] = x;
        return;
    }
    else {

        queue_rear++;
    }

    r_queue[queue_rear] = x;
}



void ready_queue_pop() {

    if (queue_front == -1 && queue_rear == -1) {

        return;
    }

    for (int i = 0; i <= queue_rear; i++) {

        r_queue[i] = r_queue[i + 1];
    }

    queue_rear--;
    if (queue_rear == -1)
        queue_front = -1;
}

//  calculating the average waiting time and average turnaround time

void cal(struct info process[], int g[], int n1) {

    int i, j;
    float avgwait_time = 0, avgturn_around = 0;

    for (i = 0; i < n; i++) {

        for (j = n1; j >= 0; j--) {

            if (g[j] == i + 1) {

                process[i].fin_time = j + 1;
                break;
            }
        }
    }

    for (i = 0; i < n; i++) {

        for (j = 0; j < n1; j++) {

            if (g[j] == i + 1) {

                process[i].start_time = j;
                break;
            }   
        }
    }

    for (i = 0; i < n; i++) {
        
        process[i].turn_around = process[i].fin_time - process[i].arr_time;
    }
    for(i=0;i<n;i++)
    {
    	process[i].wait_time = process[i].turn_around - process[i].bur_time;
	}
	  for(i=0;i<n;i++)
    {
    	avgwait_time += process[i].wait_time;
        avgturn_around += process[i].turn_around;
	}
	

    printf("Id \t ArrivalTime \t BurstTime \t WaitingTime \t TurnAroundTime \n");

    for (i = 0; i < n; i++) {

        printf("%d \t    %d \t\t    %d \t\t    %d \t\t    %d \n", process[i].number, process[i].arr_time, process[i].bur_time, process[i].wait_time, process[i].turn_around);
    }

    avgwait_time /= n;
    avgturn_around /= n;

    printf("\n\n");
    printf("Average Waiting Time And Average Turn Around Time \n\n");

    printf("%f %f", avgwait_time, avgturn_around);

    printf("\n");

}

// Implementation of Multi Level Queue

void multi_level_queue(struct info process[]) {

    int total_time = 0; 
    total_time += process[0].arr_time + process[0].bur_time;

    for (int i = 1; i < n; i++) {

        if (total_time < process[i].arr_time)
            total_time = process[i].arr_time;
        
        total_time += process[i].bur_time;
    }

    int ghant_chart[total_time]; 
    int cpu_status = 0; 

    for (int i = 0; i < total_time; i++)
        ghant_chart[i] = -1;
    
    struct info* current;
    int pri_queue_status = 0;
    int ready_queue_status = 0; 
    int quantam = 2; 
    
    for (int i = 0; i < total_time; i++) {

        for (int j = 0; j < n; j++) {

            if (i == process[j].arr_time) {
                pri_queue_Push(&process[j]);
            }
        }

        if (cpu_status == 0) { 

            if (!pri_queue_Empty()) { 

                current = pri_queue_top();
                pri_queue_Pop();
                pri_queue_status = 1;
                cpu_status = 1;
            }
            else if (!ready_queue_Empty()) {

                current = ready_queue_front();
                ready_queue_pop();
                ready_queue_status = 1;
                quantam = 2;
                cpu_status = 1;
            }
        }
        else if (cpu_status == 1) {

            if (pri_queue_status == 1 && !pri_queue_Empty()) {

                if (pri_queue_top()->pri < current->pri) {

                    ready_queue_push(current);
                    current = pri_queue_top();
                    pri_queue_Pop();
                }
            }
            else if (ready_queue_status == 1 && !pri_queue_Empty()) {

                ready_queue_push(current);
                current = pri_queue_top();
                pri_queue_Pop();
                ready_queue_status = 0;
                pri_queue_status = 1;
            }
        }

        if (cpu_status == 1) {

            if (pri_queue_status == 1) {

                current->rt--;
                ghant_chart[i] = current->number;

                if (current->rt == 0) {

                    cpu_status = 0;
                    pri_queue_status = 0;
                }
            }
            else if (ready_queue_status == 1) {

                current->rt--;
                quantam--;
                ghant_chart[i] = current->number;

                if (current->rt == 0) {

                    cpu_status = 0;
                    ready_queue_status = 0;
                }
                else if (quantam == 0) {

                    cpu_status = 0;
                    ready_queue_status = 1;
                    ready_queue_push(current);
                }
            }
        }
    }

    // Printing ghant Chart

    printf("\n\n");

    for (int i = 0; i < total_time; i++) {
        printf("%d ", ghant_chart[i]);
    }

    printf("\n\n");

    cal(process, ghant_chart, total_time);

}


int main() {

    printf("Enter Number of process \n");
    scanf("%d", &n);

    struct info process[n];
    for (int i = 0; i < n; i++) {
    	printf("Enter Process Id, Arrival Time, Burst Time, Priority for %d process \n",i+1);
        scanf("%d%d%d%d", &process[i].number, &process[i].arr_time, &process[i].bur_time, &process[i].pri);
        process[i].rt = process[i].bur_time;
    }

    sorting(process);   

    multi_level_queue(process);

    return 0;
}
