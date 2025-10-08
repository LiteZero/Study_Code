import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        //输入一个整数n，求n行的杨辉三角形。
        Scanner sc = new Scanner(System.in);
        int n=sc.nextInt();
        int [][]a=new int[n][n];
        int i,j;
        for(i=0;i<n;i++){a[i][0]=1;a[i][i]=1;}
        for(i=1;i<n;i++){for(j=0;j<n;j++){
            if(a[i][j]==1 && j!=0){continue;}
            if(a[i][j]==0){a[i][j]=a[i-1][j]+a[i-1][j-1];}
        }}
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                if(a[i][j]!=0)System.out.print(a[i][j]+" ");
            }
            if(i!=n-1){System.out.println("");}
        }
    }
}