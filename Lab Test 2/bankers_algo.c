#include<stdio.h>
#include<stdlib.h>

void check_safety();
int n,m,*available,*max,*allocation,*need,*work,*finish;

int main(){
	int i,j;
	FILE *fp;
	fp = fopen("input.txt","r");
	fscanf(fp,"%d %d",&n,&m);
	available = (int*)malloc(m*sizeof(int));
	max = (int*)malloc(n*m*sizeof(int));
	allocation = (int*)malloc(n*m*sizeof(int));
	need = (int*)malloc(n*m*sizeof(int));
	work = (int*)malloc(m*sizeof(int));
	finish = (int*)malloc(n*sizeof(int));
	
	for (i = 0; i <  n; i++)
      for (j = 0; j < m; j++){
		fscanf(fp,"%d",&*(allocation + i*m + j));
	}

	for (i = 0; i <  n; i++)
      for (j = 0; j < m; j++){
		fscanf(fp,"%d",&*(max + i*m + j));
	}
	
	for(i=0;i<m;i++){
		fscanf(fp,"%d",&available[i]);
	}
	for (i = 0; i <  n; i++)
      for (j = 0; j < m; j++){
		*(need + i*m + j) = *(max + i*m + j) - *(allocation + i*m + j);
	}
	
	 check_safety();
	
	return 0;
}

void check_safety(){
	int i,j,flag =0;
	for(i=0;i<m;i++)
		work[i] = available[i];
	
	for(i=0;i<n;i++)
		finish[i] = 0;

Loop:	for(i=0;i<n;i++){
Loop1:		if(finish[i]==0){
			for (j = 0; j < m; j++){
				if(*(need + i*m + j)<=work[j])
					flag=1;
				}
			if(flag==1){
				for(j=0;j<m;j++)
					work[i] += *(allocation + i*m + j);
				finish[i] = 1;
				printf("P%d\t",i);
				goto Loop;
				}
			}
		}
		
	for(i=0;i<n;i++)
		if(finish[i] == 0){
			goto Loop;
			}
	printf("System is in safe state\n");
	}
	
