import java.util.*;        
import java.math.BigInteger;        
import java.math.BigDecimal;        
        
;        
        
public class Main {        
        
    public static void main(String[] args) {        
        Scanner in =new Scanner(System.in);        
        BigInteger [] a = new BigInteger[10001];        
        a[2]=BigInteger.valueOf(3);        
        a[3]=BigInteger.valueOf(4);        
        for(int i=4;i<=10000;++i){        
            a[i]=a[i-1].add(a[i-2]);        
        }        
        while(in.hasNext()){        
            int n=in.nextInt();        
            System.out.println(a[n]);        
        }        
    }        
            
}     
