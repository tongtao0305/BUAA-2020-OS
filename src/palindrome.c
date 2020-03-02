#include<stdio.h>
int main()
{
	int n;
	scanf("%d",&n);

	char num[10001];
	int copy = n;
	int cnt = 0;
	int i;
	int flag = 1;

	while (copy > 0){
		num[cnt++] = copy % 10;
		copy = copy / 10;	
	}

	for (i=0;i<cnt/2;i++){
		if (num[i]!=num[cnt-i-1]){
			flag=0;
			break;
		}
	}

	if(flag==1){
		printf("Y");
	}else{
		printf("N");
	}
	return 0;
}
