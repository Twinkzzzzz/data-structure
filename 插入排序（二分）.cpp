#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int a[1001]={23,51,64,63,25,46,27,23,34,643,1,3,0,5,3,15,43,1};
int n=15;

int main()
{
	int i,t,w,m,tmp;
	for(i=2;i<=n;++i)
	{
		t=1;
		w=i-1;
		while(t<=w)
		{
			m=(t+w)/2;
			if (a[m]<a[i]) t=m+1; else w=m-1;
		}
		tmp=a[i];
		for(int j=i-1;j>=t;--j) a[j+1]=a[j];
		a[t]=tmp;
	}
	for(int i=1;i<=n;++i) cout << a[i] << " ";
	return 0;
} 
