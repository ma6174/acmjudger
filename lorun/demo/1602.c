#include<stdio.h>  
void main()  
{  
int a,b,c,m;  
int d=1;  
  while(scanf("%d %d",&a,&b)!=EOF)  
   {  
     
   for(c=1;c<=1000;c++)  
      {  
          if(a%c==0&&b%c==0)  
                {  
                 d=d*c;  
                 a=a/c;  
                 b=b/c;  
                }  
      }  
      m=d*a*b;  
     printf("%d",m);  
    }  
}
