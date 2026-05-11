#include<stdio.h>

inline int binary(int* a, int n, int k){
	int l=0,h=n;
	while(l<=h){
		int mid = l+((h-l)/2);
		if(a[mid] == k)
			return mid;
		else if(a[mid] > k)
			h = mid-1;
		else
			l = mid+1;
	}
	return -1;
}

void main(){
	int n,k;
	printf("enter the number of elements :");
	scanf("%d",&n);
	int a[n];
	printf("enter the elements into the array\n");
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	printf("enter the key to search :");
	scanf("%d",&k);
	int r = binary(a,n,k);
	if(r = -1)
		printf("element not found");
	else
		printf("element found at %d",r);
}
	
	
