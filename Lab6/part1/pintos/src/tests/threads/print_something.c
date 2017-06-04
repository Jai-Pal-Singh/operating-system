#include<stdio.h>
#include<kernel/console.h>
#include "print_something.h"
#include<random.h>
#include"threads/thread.h"

void sort_random_number(void * aux);
void test_sort(void);

void test_print_something(void){
printf("Hello World!!!\n");

}

void sort_random_number(void *aux){
	int n=10,i,j,k,b,temp,a[10];
	random_bytes(a,10*sizeof(int));
	
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
	printf("Sorted Random Numbers:\n");
	for(i=0;i<n;i++)
		printf("%d\n",a[i]);
}
	
void test_sort(void){
	thread_create("sort",10,sort_random_number, NULL);
	thread_yield();
}


