#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

int map[101][101],ind[101],ans[101],vis[101],pos[100001][101],mark[101],div[101],divans1[101],divans2[101];
double maxmark,maxterm,stan,avesum,minn2;
int n,e,sum1,sum2,minn1,divnum2=0,sum,num1,num2;

void search(int p,int k)
{
	ans[k]=p;
	if (k==n)
	{
		sum++;
		for(int i=1;i<=n;++i) pos[sum][i]=ans[i];
		return;
	}
	vis[p]=1;
	for(int i=1;i<=n;++i) if(map[p][i]) ind[i]--;
	for(int i=1;i<=n;++i) if(!vis[i] && !ind[i]) search(i,k+1);
	for(int i=1;i<=n;++i) if(map[p][i]) ind[i]++;
	vis[p]=0;
	return;
}

int main()
{
	cin >> n >> e >> maxmark >> maxterm;
	double tmpsum=0;
	for(int i=1;i<=n;++i)
	{
		cin >> mark[i];
		tmpsum+=mark[i];
	}
	stan=tmpsum/maxterm;
	int x,y;
	memset(map,0,sizeof(map));
	memset(ind,0,sizeof(ind));
	memset(ans,0,sizeof(ans));
	memset(vis,0,sizeof(vis));
	memset(div,0,sizeof(div));
	memset(divans1,0,sizeof(divans1));
	memset(divans2,0,sizeof(divans2));
	for(int i=1;i<=e;++i)
	{
		cin >> x >> y;
		map[x][y]=1;
		ind[y]++;
	}
	sum=0;
	for(int i=1;i<=n;++i) if(!ind[i]) search(i,1);
	int tmp=0,tdiv=0,flag=0,num;
	minn1=n;
	cout << "可能的拓扑序列=" << sum << endl;
	cout << "理想平均学分=" << stan << endl;
	minn2=10000;
	for(int k=1;k<=sum;++k)
	{
		tmp=0;
		tdiv=0;
		flag=0;
		for(int j=1;j<=n;++j)
		{
			tmp+=mark[pos[k][j]];
			if (tmp>maxmark)
			{
				tdiv++;
				div[tdiv]=j-1;
				tmp=mark[pos[k][j]];
				if (tdiv==maxterm)
				{
					flag=1;
					break;
				}
			}
		}
		if (!flag)
		{
			tdiv++;
			div[tdiv]=n;
			if (tdiv<minn1)
			{
				num1=k;
				minn1=tdiv;
				for(int j=1;j<=tdiv;++j) divans1[j]=div[j];
			}
		}
		//
		tmp=0;
		tdiv=0;
		flag=0;
		avesum=0;
		memset(div,0,sizeof(div));
		for(int j=1;j<=n;++j)
		{
			tmp+=mark[pos[k][j]];
			if (tmp>stan)
			{
				
				if(tmp-stan>stan-tmp+mark[pos[k][j]])
				{
					avesum+=stan-tmp+mark[pos[k][j]];
					tdiv++;
					div[tdiv]=j-1;
					tmp=mark[pos[k][j]];
				}
				else
				{
					
					avesum+=tmp-stan;
					tdiv++;
					div[tdiv]=j;
					tmp=0;
				}
				if (tdiv==maxterm)
				{
					flag=1;
					break;
				}
			}
		}
		if (!flag)
		{ 
			if (div[tdiv]!=n)
			{
				tdiv++;
				div[tdiv]=n;
				avesum+=(stan-tmp);
				if (avesum<minn2)
				{
					num2=k;
					minn2=avesum;
					divnum2=tdiv;
					for(int j=1;j<=tdiv;++j) divans2[j]=div[j];
				}
			}
		}
	}
	if (minn1==n)
	{
		cout << "no possible solution!\n";
		return 0;
	}
	cout << "\n课程最紧凑:\n";
	for(int i=1;i<=minn1;++i)
	{
		cout << "第" << i << "学期: ";
		for(int j=divans1[i-1]+1;j<=divans1[i];++j)
		{
			cout << pos[num1][j] << " ";
		} 
		cout << endl;
	}
	if(!divnum2)
	{
		cout << "no possible solution for the second requirement!\n";
		return 0;
	}
	cout << endl << "学分最平均:\n";
	for(int i=1;i<=divnum2;++i)
	{
		cout << "第" << i << "学期: ";
		for(int j=divans2[i-1]+1;j<=divans2[i];++j)
		{
			cout << pos[num2][j] << " ";
		} 
		cout << endl;
	}
	return 0;
} 
