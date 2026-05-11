#include<stdio.h>
#include<stdlib.h>

int euclid(int a, int b){
	while(b != 0){	
		int r = a%b;
		a = b;
		b = r;
	}
	return a;
}

int MODeuclid(int a, int b){
	while(a != b){
		if(a>b)
			a = a-b;
		else
			b = b-a;
	}
	return a;
}

int CONint(int a, int b){
	if(b>a){
		int temp = a;
		a = b;
		b = temp;
	}
	while(b != 0){
		if(a % b == 0)
			return b;
		else 
			b-=1;
	}
	return a;
}
	
int main(){
	int a,b,s;

	while(1){
		printf("enter two numbers");
		scanf("%d %d",&a,&b);
		printf("\n1.euclid\n2.mod euclid\n3.con int\n");
		scanf("%d",&s);
		switch(s){
			case 1: printf("%d",euclid(a,b));
			break;
			case 2: printf("%d",MODeuclid(a,b));
			break;
			case 3: printf("%d",CONint(a,b));
			break;
			default: exit(0);
		}
	}
}
		
	
