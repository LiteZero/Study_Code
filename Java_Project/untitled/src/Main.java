import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int[] a=new int[11];
        int i,j,t;
        for(i=0;i<10;i++){a[i]=sc.nextInt();}
        int n=sc.nextInt();
        for(i=0;i<10;i++){for(j=0;j<10;j++){if(a[i]<a[j]){t=a[i];a[i]=a[j];a[j]=t;}}}
        for(i=9;i>n-1;i--){a[i+1]=a[i];}
        a[n+1]=n;
        for(i=0;i<11;i++){System.out.print(a[i]+" ");}
    }
}