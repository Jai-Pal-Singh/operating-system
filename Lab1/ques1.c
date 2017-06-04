#include<stdio.h>

int main(){
	int i;
	printf("%p\n",&i);
	for(i=0;i<1000000000;i++){};
	return 0;
}
