/*
status [the nth number][the sum right now] = status [the (n-1)th number][the sum right now - the number]
status[max_len][target_sum]={0}
status[1][0..9]={1};
for(int i=2;i<=max_len;i++){
	for(int j=0;j<=max_len;i++){
	   for(int k=0;k<=9;k++){
	      status[i,j]+=status[i-1][j-k];
	   }
	}
}
int ans=sum(status[0..max_len][target_sum])
*/
package com.wumengyangok;

import java.util.Scanner;

/*This file is for the practise in Algorithm*/
public class Main {
    //QuickSort
    public static int m=0;
    public static int n=0;
    public static int ans=0;
    //Theory Coursework4
    //dfs
    public static void dfs(int add, int deep, int sum){
        if (deep>n) return;
        else{
            deep++;
            if (add+sum==m){
                ans++;
                return;
            }else if (add+sum>m){
                return;
            }
            else {
                sum+=add;
                for (int i = 0; i < 10; i++) {
                    dfs(i,deep,sum);
                }
            }
        }
    }
    public static int min(int a,int b){
        return (a<=b) ? a : b;
    }
    public static void main(String[] args) {
        Scanner scanner=new Scanner(System.in);
        n=scanner.nextInt();
        m=scanner.nextInt();
        m=min(m,n*9-m);
        //dfs(0,0,0);
        //s [the nth number][the sum right now] = status [the (n-1)th number][the sum right now - the number]
        int status[][]= new int[n+1][m+1];
        for (int i = 1; i <=n ; i++) {
            for (int j = 0; j <m ; j++) {
                status[i][j]=0;
            }
        }
        for (int i = 0; (i <= 9)&&(i <= m) ; i++) {
            status[1][i]=1;
        }
        for(int i=2;i<=n;i++){
            for(int j=0;j<=m;j++){
                for(int k=0;k<=9;k++){
                    if(j-k >= 0)
                        status[i][j]+=status[i-1][j-k];
                }
            }
        }
        int ans=status[n][m];
        System.out.println(ans);
    }
}
