#include<stdio.h>

int linear(int* a, int k, int n){
	for(int i =0;i<n;i++){
		if(a[i] == k)
			return i;
	}
	return -1;
}

void main(){
	int k,n;
	printf("enter the number of elements in array :");
	scanf("%d",&n);
	int a[n];
	printf("enter the elements of array\n");
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	printf("enter the key :");
	scanf("%d",&k);
	int r = linear(a,k,n);
	if(r>=0)
		printf("element found at %d",r);
	else
		printf("element not found");
}
