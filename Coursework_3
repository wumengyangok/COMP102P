#include <stdio.h>
int main(void){
	int box[31337];
	for(int i=0;i<31337;i++)
		box[i]=0;
	int n,m;
	scanf("%d %d",&m,&n);
	for(int i=0;i<n-1;i++){
		box[m]++;
		m=m*31334%31337;
	}
	int ans=0;
	for(int i=0;i<=m;i++){
		ans+=box[i];
	}
	printf("%d\n",ans+1);
	return 0;
}
