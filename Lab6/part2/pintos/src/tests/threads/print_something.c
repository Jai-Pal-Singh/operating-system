#include<stdio.h>
#include<kernel/console.h>
#include "print_something.h"
#include"threads/thread.h"
#include<random.h>

int a[10], n=10;

void print_thread_name(void * aux);
void print_thread_id(void * aux);
void print_thread_priority(void * aux);
void test_sort(void);

void test_print_something(void){
printf("Hello World!!!\n");

}


void print_thread_name(void * aux){
	long long int i,j;
	random_bytes(a,10*sizeof(int));
	for(i=0;i<10;i++){
		printf("Thread 1: Thread name : %s\n", thread_name());
		for(j=0;j<10000000LL;j++){}
	}
	thread_print_stats();
}
	
void print_thread_id(void * aux){
	long long int i,j,b,temp,k;
	for(i=0;i<n;i++){
		k=a[i];
		b=i;
		for(j=i+1;j<n;j++){
			if(k>a[j]){
				k = a[j];
				b=j;
			}
		}		
		temp = k;
		a[b] = a[i];
		a[i] = temp;
	}
	for(i=0;i<10;i++){
		printf("Thread 2: Thread id : %d\n", thread_tid());
		for(j=0;j<10000000LL;j++){}
	}
	thread_print_stats();
}
	
void print_thread_priority(void * aux){
	long long int i,j;
	printf("Thread 3: Thread priority : %d\n", thread_get_priority());
	for(i=0;i<10;i++){
		for(j=0;j<100000000LL;j++){}
	}
	printf("Sorted Random Numbers:\n");
	for(i=0;i<n;i++)
		printf("%d\n",a[i]);
	thread_print_stats();
}
	
void test_sort(void){
	thread_print_stats();
	thread_create("random_num_generation",20,print_thread_name, NULL);
	thread_create("sort_random_num",19,print_thread_id, NULL);
	thread_create("print_random_num",18,print_thread_priority, NULL);
	thread_yield();
	}


