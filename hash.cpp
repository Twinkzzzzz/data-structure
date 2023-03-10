#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

typedef struct node
{
	int num;
	int len;
	node* next;	
}hashnode;

class hash1
{
	private:
		int num[1001],len[1001],kn;
	public:
		hash1(const int kn1=10)
		{
			memset(num,0,sizeof(num));
			memset(len,0,sizeof(len));
			kn=kn1;
		}
		void insert(const int a)
		{
			int k,s=0;
			k=a%13;
			s=1;
			while(num[k]!=0 && s<kn)
			{
				k=(k+1)%kn;
				s++;
			}
			num[k]=a;
			len[k]=s;
		}
		hash1(const int* a,const int n,const int kn1=10)
		{
			memset(num,0,sizeof(num));
			memset(len,0,sizeof(len));
			kn=kn1;
			int k,s=0;
			for(int i=0;i<n;++i) insert(a[i]);
		}
		friend ostream& operator<<(ostream& os,const hash1& hs)
		{
			int sum=0;
			for(int i=0;i<hs.kn;++i)
			{
				os << hs.num[i] << " " << hs.len[i] << endl;
				sum+=hs.len[i];
			}
			double ans=(double)(sum)/(10.0);
			os << "avelen="  << ans << endl;
			return os;
		}
};

class hash2
{
	private:
		int num[1001],len[1001],kn;
	public:
		hash2(const int kn1=10)
		{
			memset(num,0,sizeof(num));
			memset(len,0,sizeof(len));
			kn=kn1;
		}
		void insert(const int a)
		{
			int k,s=0;
			k=a%13;
			s=1;
			while(num[k]!=0 && s<kn)
			{
				k=(k+s*s-(s-1)*(s-1))%kn;
				s++;
			}
			num[k]=a;
			len[k]=s;
		}
		hash2(const int* a,const int n,const int kn1=10)
		{
			memset(num,0,sizeof(num));
			memset(len,0,sizeof(len));
			kn=kn1;
			int k,s=0;
			for(int i=0;i<n;++i) insert(a[i]);
		}
		friend ostream& operator<<(ostream& os,const hash2& hs)
		{
			int sum=0;
			for(int i=0;i<hs.kn;++i)
			{
				os << hs.num[i] << " " << hs.len[i] << endl;
				sum+=hs.len[i];
			}
			double ans=(double)(sum)/(10.0);
			os << "avelen="  << ans << endl;
			return os;
		}
};

class hash3
{
	private:
		hashnode* head[1001];
		int kn;
	public:
		hash3(int kn1=10)
		{
			kn=kn1;
			for(int i=0;i<kn;++i)
			{
				head[i]=new hashnode;
				head[i]->num=head[i]->len=0;
				head[i]->next=NULL;
			}
		}
		void insert(const int a)
		{
			int k=a%kn;
			int s=1;
			hashnode* p=head[k],*q;
			while(p->next!=NULL)
			{
				p=p->next;
				s++;
			}
			q=new hashnode;
			q->len=s;
			q->num=a;
			q->next=NULL;
			p->next=q; 
		}
		hash3(const int* a,const int n,const int kn1=10)
		{
			kn=kn1;
			for(int i=0;i<kn;++i)
			{
				head[i]=new hashnode;
				head[i]->num=head[i]->len=0;
				head[i]->next=NULL;
			}
			for(int i=0;i<n;++i) insert(a[i]);
		}
		friend ostream& operator<<(ostream& os,const hash3& hs)
		{
			double ans=0;
			for(int i=0;i<hs.kn;++i)
			{
				hashnode* p=hs.head[i];
				if (p->next==NULL) os << "NULL\n";
				else
				{
					os << p->next->num;
					ans+=p->next->len;
					p=p->next;
					while(p->next!=NULL)
					{
						os << " --> " << p->next->num;
						ans+=p->next->len; 
						p=p->next;
					}
					os << endl;
				}
			}
			os << "avelen=" << ans/(10.0) << endl;
			return os;
		}
};

int a[10]={5,88,12,56,71,28,33,43,93,17};

int main()
{
	hash1 hs1(a,10,13);
	hash2 hs2(a,10,13);
	hash3 hs3(a,10,13);
	cout << hs1 << endl << hs2 << endl << hs3;
	return 0;
}
