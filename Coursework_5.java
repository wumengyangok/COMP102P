package com.wumengyangok;
import java.util.Scanner;

/*This file is for the practise in Algorithm*/

public class Main {
    public static int m=0;
    public static int n=0;
    public static int ans=0;
    public static void qsort(int a[], int l, int r) {
        if (l == r)
            return;
        int i = l, j = r;
        int p = i;
        while (i < j) {
            if (a[i] < a[j]) {
                int temp = a[i];
                a[i] = a[p];
                a[p] = temp;
                i++;
                p++;
            } else {
                i++;
            }
        }
        int temp = a[j];
        a[j] = a[p];
        a[p] = temp;
        if (p > l)
            qsort(a, l, p - 1);
        if (p < r)
            qsort(a, p + 1, r);
    }
    public static int min(int a,int b){
        return (a<=b) ? a : b;
    }
    public static char reverse(char ch){
        if(ch == '1') return '0';
        else return '1';
    }
    public static String getStringWithLengthAndFilledWithCharacter(int length, char charToFill) {
        char[] array = new char[length];
        int pos = 0;
        while (pos < length) {
            array[pos] = charToFill;
            pos++;
        }
        return new String(array);
    }
    public static String solve(String status, int n){
        char[] _new=new char[17];
        //_new=status.toCharArray();
        //_new[0]='0';
        //System.out.println(status);
        for (int i = 0; i <= 15 ; i++) {
            _new[i]=status.charAt(i);
        }
        _new[n]=reverse(_new[n]);
        if(n%4-1 >= 0)
            _new[n-1]=reverse(_new[n-1]);
        if(n%4+1 <= 3)
            _new[n+1]=reverse(_new[n+1]);
        if(n-4 >= 0)
            _new[n-4]=reverse(_new[n-4]);
        if(n+4 <= 15)
            _new[n+4]=reverse(_new[n+4]);
        String news=new String(_new,0,16);
        return news;
    }
    public static void main(String arg[]){
        //System.out.println("Hello world!");
        //int a=Integer.parseInt(s);
        //String j=getStringWithLengthAndFilledWithCharacter(16,'0');
        //j=Integer.toBinaryString(a);
        //a=Integer.parseInt(j,2);
        //System.out.println(a+" "+j.charAt(15));

        Scanner scanner=new Scanner(System.in);
        int n=scanner.nextInt();
        char[] target={'0','0','0','0','0','0','0','0','0','0','0','0','0',
                '0','0','0','0'};
        for (int i = 0; i < n ; i++) {
            int in=scanner.nextInt();
            target[in]='1';
        }
        String targets=new String(target,1,16);
        //System.out.println(targets);
        queueElement allPosibility[]=new queueElement[5000000];
        for (int i = 1; i < 5000000 ; i++) {
            allPosibility[i]=new queueElement();
        }
        int left=1;
        int right=1;
        allPosibility[1].depth=0;
        allPosibility[1].status=targets;
        targets="0000000000000000";
        for (int i = 1; i <= 16 ; i++) {
            allPosibility[1].flag[i]=true;
        }
        while (left<=right){
            //System.out.println(allPosibility[left].status);
            if(allPosibility[left].status.equals(targets)) {
                //System.out.println(targets);
                //System.out.println(allPosibility[left].depth);
                for (int i = 1; i <= allPosibility[left].depth ; i++) {
                    System.out.println(allPosibility[left].path[i]+" ");
                }
                break;
            }
            for (int i = 0; i < 16 ; i++) {
                if ((allPosibility[left].flag[i + 1])&&(allPosibility[left].status.charAt(i)=='1')) {
                    right++;
                    for (int j = 1; j <= 16; j++) {
                        allPosibility[right].flag[j] = allPosibility[left].flag[j];
                    }
                    allPosibility[right].flag[i + 1] = false;
                    //System.out.println(allPosibility[right].status.length());
                    for (int j = 1; j <= allPosibility[left].depth ; j++) {
                        allPosibility[right].path[j]=allPosibility[left].path[j];
                    }
                    allPosibility[right].depth=allPosibility[left].depth+1;
                    allPosibility[right].path[allPosibility[right].depth]=i+1;
                    allPosibility[right].status = solve(allPosibility[left].status, i);
                }
            }
            left++;
        }
        //System.out.println(allPosibility[1].status);
    }


}
