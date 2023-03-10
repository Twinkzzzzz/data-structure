#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int n,a[1001],s;

int main()
{
	cin >> n;
	for(int i=0;i<n;++i) cin >> a[i];
	cin >> s;
	int t=0,w=n-1,m;
	while(t<=w)
	{
		m=(t+w)/2;
		//cout << m <<endl;
		if (a[m]==s) break;
		if (a[m]>s) w=m-1; else t=m+1;
	}
	if (a[m]==s) cout << m << endl; else cout << -1 << endl;
	return 0;
} 
