#include <iostream>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <windows.h>
using namespace std;

int a[10]={41,60,25,13,36,22,69,53,11,50};
int ct,st;

void coutcur(int p,int q,int r)
{
	system("cls");
	cout << "round " << r << ": ";
	for(int k=0;k<=9;++k) cout << a[k] << " ";
	cout << endl;
	cout << "         ";
	for(int k=0;k<=9;++k) if (k==p || k==q) cout << "¡ü "; else cout << "   ";
	cout << "\n         compare times: " << ct << " swap times: " << st << endl;
	cout << "\n";
	sleep(1);
	return;
}

int main()
{
	ct=st=0;
	cout << "         ";
	for(int i=0;i<9;++i) cout << a[i] << " ";
	cout << "\n";
	sleep(10);
	coutcur(0,1,1);
	for(int i=0;i<9;++i)
	{
		for(int j=i+1;j<=9;++j)
		{
			ct++;
			coutcur(i,j,i+1);
			if (a[i]>a[j])
			{
				st++;
				swap(a[i],a[j]);
				coutcur(i,j,i+1);
			}
		}
	}
	for(int i=0;i<=9;++i) cout << a[i] << " ";
	return 0;
} 
