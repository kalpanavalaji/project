#include<stdio.h>
int* add(int,int);
int main()
{
int a,b,*c;
scanf("%d",&a);
scanf("%d",&b);
//c=add(b-a,a+b);
c=add(a,b);
printf("%d a\n",a);
printf("%d b\n",b);
printf(" c %d\n",*c);
}
int* add(int e ,int f)
{
int *s;
//*e=*e+1;
//*f=*f+1;
//*f++;
s=e+f;
//s=(e-f)+(e+f);
printf(" s %p",s);
//printf(" e %d\n",*e);
//printf(" f %d\n",*f);
return s;
}

