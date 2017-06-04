#include<stdio.h>
#include<stdbool.h>
#include<sys/types.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
bool flag[2];
int turn;
	
int main(){
	int other,pid;
	flag[0] = FALSE;
	flag[1] = FALSE;
	
	 if((pid=vfork())<0)
        {
                perror("vfork error\n");
                return 0;

        }
	while(TRUE){
		other = 1 - pid;
		if(pid==0){
			flag[pid] = TRUE;
			turn = other;
			while((flag[other])&&(turn == other)){
				}
			//critical section
			printf("pid 0 in critical section\n");
			flag[pid] = FALSE;
			//remainder section
			
			}
		else{
			flag[pid] = TRUE;
			turn = other;
			while((flag[other])&&(turn = other)){}
			//critical section
			printf("pid 1 in critical section\n");
			flag[pid] = FALSE;
			//remainder section
			
			}
			pid = other;
			sleep(1);
		}
	return 0;
	}
