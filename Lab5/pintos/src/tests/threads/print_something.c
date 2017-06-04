#include<stdio.h>
#include<kernel/console.h>
#include "print_something.h"

void test_print_something(void){
printf("Hello World!!!\n");

}

void sort_random_number(void){
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
	thread_exit();	
}
	
void test_sort(void){
	thread_create("sort",20,sort_random_number);
}


