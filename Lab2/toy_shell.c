#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>

int main(int argc, int *argv[]){
	int path,i,flag=0,pipe_flag=0;
	size_t bufsize = 100;
	char *str1,*str2,*token[100],*sub_token[100][100],cwdir[100],*a;
	pid_t  pid;
	str1 = (char*)malloc(100*sizeof(char));
	while(1){
		if (getcwd(cwdir, sizeof(cwdir)) != NULL)
       		printf("\njaipal@jaipal-pc:~%s$", cwdir);
   		else
			printf("\njaipal@jaipal-pc:~$ ");
		fflush(stdin);
		getline(&str1,&bufsize,stdin);
		
		if(feof(stdin))
			exit(0);
		if((strlen(str1)-1)>=1)
			str1[strlen(str1)-1] = '\0';
		if(!strcmp(str1,"exit")) 
			exit(0);
		fflush(stdin);	
		
		token[0] = strtok(str1, " ");
		for (i = 1; ; i++) {
			token[i] = strtok(NULL, " ");
			if (token[i] == NULL)
				break;
			else if(!strcmp(token[i],"&")){
				token[i] = NULL;
				flag++;
			}
			else if(!strcmp(token[i],"|"))
				pipe_flag++;
		}
			
		if(pipe_flag>0){    //code for input with pipe
			
			sub_token[0][0] = strtok(str1, "|");
			for (i = 1; ; i++) {
				sub_token[0][i] = strtok(NULL, "|");
				if (sub_token[0][i] == NULL)
					break;
				
			}
			printf("In pipeline after for\n");
			for(i=0;;i++){
				printf("%s\n",sub_token[0][i]);
				if (sub_token[0][i] == NULL)
					break;
			}
		
		}
		
		else{   //////code for input without pipe
			
			if(!strcmp(token[0],"cd")){
				if(!chdir(token[1])){}
				else if(token[1]==NULL){chdir("/home");}
				else
					printf("cd: %s: No such file or directory",token[1]);
			  }
			  
				
			if ((pid = fork()) == -1) {
				   perror("fork error");
				exit(0);
			}
			else if (pid == 0) {
				if(flag>0){
					execvp(token[0],token);
					flag=0;
				}
				else{
					execvp(token[0],token);
					waitpid(pid,NULL,0);
				}
			}
			else{
				if(flag>0)
					printf("%d running",pid);
				else
					waitpid(pid,NULL,0);			
				flag=0;
			}
		}		   
	}
	return 0;
}
