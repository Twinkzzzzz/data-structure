#include <iostream>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <windows.h>
using namespace std;

int a[10]={41,60,25,13,36,22,69,53,92,81};
int ct,st;

void coutcur(int t,int w,int mid,int p,int q)
{
	system("cls");
	cout << "当前正在排序: " << "第" << t+1 << "个至第" << w+1 << "个  " << "基准: " << mid << endl;
	for(int k=0;k<=9;++k) if (k==t || k==w) cout << "▽ "; else cout << "   ";
	cout << endl;
	for(int k=0;k<=9;++k) cout << a[k] << " ";
	cout << endl;
	for(int k=0;k<=9;++k) if (k==p || k==q) cout << "↑ "; else cout << "   ";
	cout << "\ncompare times: " << ct << " swap times: " << st << endl;
	cout << "\n";
	sleep(1);
	return;
}

void qsort(int t,int w)
{
	if (t>=w) return;
	int mid=a[t];
	int i=t,j=w;
	while(i<j)
	{
		coutcur(t,w,mid,i,j);
		while(a[j]>mid && j>i)
		{
			ct++;
			j--;
			coutcur(t,w,mid,i,j);
		}
		if (i<j)
		{
			a[i]=a[j];
			st++;
			coutcur(t,w,mid,i,j);
			i++;
			coutcur(t,w,mid,i,j);
		}
		while(a[i]<mid && i<j)
		{
			ct++;
			i++;
			coutcur(t,w,mid,i,j);
		}
		if(i<j)
		{
			a[j]=a[i];
			st++;
			coutcur(t,w,mid,i,j);
			j--;
			coutcur(t,w,mid,i,j);
		}
	}
	a[i]=mid;
	coutcur(t,w,mid,i,j);
	qsort(t,i-1);
	qsort(i+1,w);
}

int main()
{
	ct=st=0;
	cout << endl << endl;
	for(int i=0;i<=9;++i) cout << a[i] << " ";
	sleep(10);
	qsort(0,9);
	for(int i=0;i<=9;++i) cout << a[i] << " ";
	cout << endl;
	return 0;
}
