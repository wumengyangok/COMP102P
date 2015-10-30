#include<stdio.h>
int gcd(int m,int n){
  while(n>0){
    m=m % n;
    int t=m;
    m=n;
    n=t;
  }
  return m;
}
int main(){
  int number;
  scanf("%d",&number);
  int m,n;
  scanf("%d",&m);
  int sum=m;
  int i;
  for(i=1;i<number;i++){
    scanf("%d",&n);
    sum+=n;
    m=gcd(m,n);
  }
  int ans=sum/m;
  printf("%d %d\n",m,ans);
}
