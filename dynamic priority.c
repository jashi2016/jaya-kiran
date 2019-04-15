#include<stdio.h>

// PCB 

struct process_info{
	int process_id,at,bt,completion_time,priority;
};



void exchange(struct process_info* m1,struct process_info* m2) { 
    struct process_info t = *m1; 
    *m1 = *m2; 
    *m2 = t; 
} 

int dividing (struct process_info queue[], int lower_element, int higher_element) 
{ 
    int mid = queue[higher_element].priority;
    int i = (lower_element- 1),j; 
		  
    for (j = lower_element; j <= higher_element- 1; j++) { 
    	
        if (queue[j].priority > mid || (queue[i].priority == queue[j].priority && queue[i].completion_time > queue[j].completion_time)) { 
            i++; 
            exchange(&queue[i], &queue[j]); 
        } 
    } 
    exchange(&queue[i + 1], &queue[higher_element]); 
    return (i + 1); 
} 
  
void Q_S(struct process_info queue[], int lower_element, int higher_element) 
{ 
    if (lower_element< higher_element) { 
        int pi = dividing(queue, lower_element, higher_element); 
        Q_S(queue, lower_element, pi - 1); 
        Q_S(queue, pi + 1, higher_element); 
    } 
} 

void dynamic_priority(struct process_info process[],int n)
{
	struct process_info r_queue[n];
	int i,j,rq=0,burst = 0,sum=0,x=n;
	
	while(x !=0 ){
	
		for(i=0;i<n;i++){
			if(burst == process[i].at){  
				r_queue[rq] = process[i];
				rq++;
			}
		}
		
		Q_S(r_queue,0,rq-1);	//Sorting queue according to their priority
	
	//  execution order
	//	printf("%d %d %d %d \n",r_queue[0].process_id,r_queue[0].at,r_queue[0].bt,r_queue[0].priority); 
	
	/* 	 status of the ready queue
		for(i=0;i<rq;i++)
		printf("%d %d %d %d \n",r_queue[i].process_id,r_queue[i].at,r_queue[i].bt,r_queue[i].priority);*/
	
		/*Cpu is allocated and Process execution start*/	
		r_queue[0].bt--;
		r_queue[0].completion_time = burst;
		r_queue[0].priority += 1;
		
		/*Every other waiting in r_queue will be incremented with 2 in the priority*/
		for(j=1;j<rq;j++)
			r_queue[j].priority += 2;
	
		/*If First process of r_queue is completed it will out of the memory*/
		if(r_queue[0].bt == 0){
			sum += (r_queue[0].completion_time-r_queue[0].at-process[r_queue[0].process_id-1].bt)+1; // 1 bcz burst is incremented after
			--x;
			for(j=0;j<rq-1;j++)	
				r_queue[j] = r_queue[j+1];
			rq--;
		}
		
		
		burst++;
	}
	printf("Average Waiting time : %f sec: ",(float)sum/n);			
}

int main()
{
	int i,n;	
	
	printf("Enter no. of process to create : ");		
	scanf("%d",&n);
	struct process_info process[n];


	for(i=0;i<n;i++){
		printf("Enter process_id | arrival_Time | Burst_Time for %d Process: ",i+1);
		scanf("%d%d%d",&process[i].process_id,&process[i].at,&process[i].bt);
		process[i].completion_time = process[i].priority = 0;	
	}	
	
	dynamic_priority(process,n);
	return 0;
}
