#include <cstdio>
#include <cstring>
#include <iostream> 
using namespace std;

const int maxn=30;
const int maxm=500;
int n;//��Ч��ĸ��
int G[maxn][maxn];
int vis[maxn];
int ans[maxn];
int cnt;
bool mark[maxn];//��ǵ�ǰ��ĸ�����ڱ�����
bool ok(int i,int cnt)//�����ans[0,cnt-1]������һ����Ӧ��i����ų��ֵ���ĸ,��ô����false
{
    for(int j=0;j<cnt;j++)
        if(G[i][ans[j]]) return false;
    return true;
}
void dfs(int cnt)
{
    if(cnt==n)
    {
        for(int i=0;i<n;i++)
            printf("%c",ans[i]+'a');
        printf("\n");
    }
    else for(int i=0;i<26;i++)if(mark[i]&&!vis[i]&&ok(i,cnt))
    {
        vis[i]=1;
        ans[cnt]=i;
        dfs(cnt+1);
        vis[i]=0;
    }
}
int main()
{
    char str[1000];
    while(gets(str))
    {
        n=0;
        memset(mark,0,sizeof(mark));
        memset(G,0,sizeof(G));
        memset(vis,0,sizeof(vis));
        for(int i=0;str[i];i++)if(str[i]!=' ')
            mark[str[i]-'a']=true, n++;
        gets(str);
        for(int i=0;str[i];i++)if(str[i]!=' ')
        {
            int a,b;
            a=str[i++]-'a';
            while(str[i]==' ')
                i++;
            b=str[i]-'a';
            G[a][b]=1;
        }
        dfs(0);//��ʾ��ǰ���ڹ����0��λ��
        puts("");
    }
    return 0;
}
