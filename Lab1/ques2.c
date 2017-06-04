#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	int i,j,k,l,*b,sum=0;
	unsigned long int read=0,write=0,mem_sum=0,user=0,sys=0,idle=0,cont_no,tot_cont=0,proc_no,tot_proc=0; 
	float *a,mem_avg=0;
	FILE *fp;
	char *c;
	a = (float*)malloc(10*sizeof(float));
	b = (int*)malloc(14*sizeof(int));
	c = (char*)malloc(10*sizeof(char));

	if(argc==1){
		printf("\n");
		system("cat /proc/cpuinfo | grep 'model name' | uniq");
		system("echo -n 'Kernel version: ' ; cat /proc/version_signature");
		system("cat /proc/meminfo | grep MemTotal | uniq");
		fp = fopen("/proc/uptime","r");
		fscanf(fp,"%f",&a[0]);
		printf("Uptime : %.2f minutes\n",a[0]/60);
		printf("\n");
		fclose(fp);
 	}
 	else{
 		j=atoi(argv[1]);
 		k=atoi(argv[2]);
 		k=k/j;
 		while(1){
 			mem_sum=0;
 			mem_avg=0;
 			read=0;
 			write=0;
 			tot_cont=0;
 			tot_proc=0;
 			
 			for(l=0;l<k;l++){
 				fp = fopen("/proc/stat","r");
		 		fscanf(fp,"%s",c);
		 		for(i=0;i<10;i++){
					fscanf(fp,"%d",&b[i]);
					sum+=b[i];
				}
				user += b[0];
				sys += b[2];
				idle += b[3];
				fclose(fp);
		
				fp = fopen("/proc/meminfo","r");
				for(i=0;i<2;i++)
					fscanf(fp,"%s %d %s",c,&b[i],c);
				mem_sum +=b[0];
				mem_avg +=(float)(b[1]*100/b[0]);
				fclose(fp);
		

				fp = fopen("/proc/diskstats","r");
				while(!feof(fp)){
					for(i=0;i<14;i++){
						if(i==2)
							fscanf(fp,"%s",c);
						else
							fscanf(fp,"%d",&b[i]);
					}
					read += b[3];
					write += b[7];
				}
				fclose(fp);
				
				fp = popen("cat /proc/stat | grep ctxt | uniq","r");
				fscanf(fp,"%s %ld",c,&cont_no);
				tot_cont +=cont_no;
				fclose(fp);
		
				fp = popen("cat /proc/stat | grep processes | uniq","r");
				fscanf(fp,"%s %ld",c,&proc_no);
				tot_proc +=proc_no;
				fclose(fp);
		
				sleep(j);	
 			}
 			printf("\n");
 			printf("%%Cpu(s): %.2f user mode %.2f system mode %.2f idle mode\n",(float)(user*100/(sum)),(float)(sys*100/(sum)),(float)(idle*100/(sum)));
 			printf("Free memory : %ld \t %.2f %%\n",mem_sum,mem_avg);
 			printf("Read : %ld  Write : %ld\n",read/k,write/k);
 			printf("rate of context switches : %ld\n",tot_cont/k);
 			printf("rate of process creation : %ld\n",tot_proc/k);
 			printf("\n");
 		}
 		free(a);
 		free(b);
 		free(c);
 		
 	}
    return 0;
}
