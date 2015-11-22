package com.wumengyangok;
import java.util.Scanner;
public class queueElement {
    public String status="0000000000000000";
    public int depth=0;
    public int[] path=new int[17];
}
public class Main {
    public static int m=0;
    public static int n=0;
    public static int ans=0;
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
        Scanner scanner=new Scanner(System.in);
        int n=scanner.nextInt();
        char[] target={'0','0','0','0','0','0','0','0','0','0','0','0','0',
                '0','0','0','0'};
        for (int i = 0; i < n ; i++) {
            int in=scanner.nextInt();
            target[in]='1';
        }
        String targets=new String(target,1,16);
        queueElement allPosibility[]=new queueElement[5000000];
        for (int i = 1; i < 5000000 ; i++) {
            allPosibility[i]=new queueElement();
        }
        int left=1;
        int right=1;
        allPosibility[1].depth=0;
        allPosibility[1].status=targets;
        targets="0000000000000000";
        while (left<=right){
            if(allPosibility[left].status.equals(targets)) {
                for (int i = 1; i <= allPosibility[left].depth ; i++) {
                    System.out.println(allPosibility[left].path[i]+" ");
                }
                break;
            }
            for (int i = 0; i < 16 ; i++) {
                if (allPosibility[left].status.charAt(i)=='1') {
                    right++;
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
    }
}
