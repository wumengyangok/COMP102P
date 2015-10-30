#include<stdio.h>
struct node{
  int x;
  int y;
};
int abs(int a){
  if (a>=0)
    return a;
  else;
  return 0-a;
}
int main(){
  int n;
  scanf("%d",&n);
  node a[n+1];
  int i;
  for(i=1;i<=n;i++){
    scanf("%d %d",&a[i].x,&a[i].y);
  }
  int j;
  int map[30][30];
  for(i=1;i<=n;i++)
    for(j=1;j<=n;j++){
      map[i][j]=abs(a[i].x-a[j].x)+abs(a[i].y-a[j].y);
    }
  bool set[n+1];
  for(i=1;i<=n;i++){
    set[i]=true;
  }
  set[1]=false;
  int sum=0;
  int setnum=1;
  while(setnum<n){
    int min=100000;
    int minnode;
    for(i=1;i<=n;i++)
      if(!set[i])
	for(j=1;j<=n;j++)
	  if((set[j])&&(j!=i))
	    if(map[i][j]<min){
	      min=map[i][j];
	      minnode=j;
	  }
    sum+=min;
    set[minnode]=false;
    setnum++;
  }
  printf("%d\n",sum);
  return 0;
}

