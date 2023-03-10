#include <cstdio>
#include <cstring>
#include <iostream> 
using namespace std;

const int maxn=30;
const int maxm=500;
int n;//有效字母数
int G[maxn][maxn];
int vis[maxn];
int ans[maxn];
int cnt;
bool mark[maxn];//标记当前字母出现在变量中
bool ok(int i,int cnt)//如果在ans[0,cnt-1]出现了一个本应在i后面才出现的字母,那么返回false
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
        dfs(0);//表示当前正在构造第0个位置
        puts("");
    }
    return 0;
}
