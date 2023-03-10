#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <iomanip>
using namespace std;

typedef struct node
{
	string name;
	string num;
	double score[4];
}stu;

template <class T> 
T getmax(T a,T b)
{
	if (a>b) return a; else return b;
}

template <class T> 
T getmin(T a,T b)
{
	if (a<b) return a; else return b;
}

class table
{
	private:
		stu inf[1001];
		int sum;
		stu maxn,minn,tot;
		int mt[5],eg[5],cp[5],tott[5];
		
	public:
		table()
		{
			sum=0;
			maxn.name=maxn.num="0";
			minn.name=minn.num="0";
			tot.name=tot.num="0";
			memset(mt,0,sizeof(mt));
			memset(eg,0,sizeof(eg));
			memset(cp,0,sizeof(cp));
			memset(tott,0,sizeof(tott));
		}
		void insert(stu p)
		{
			sum++;
			inf[sum]=p;
			maxn.score[0]=getmax(maxn.score[0],p.score[0]);
			maxn.score[1]=getmax(maxn.score[1],p.score[1]);
			maxn.score[2]=getmax(maxn.score[2],p.score[2]);
			maxn.score[3]=getmax(maxn.score[3],p.score[3]);
			minn.score[0]=getmin(minn.score[0],p.score[0]);
			minn.score[1]=getmin(minn.score[1],p.score[1]);
			minn.score[2]=getmin(minn.score[2],p.score[2]);
			minn.score[3]=getmin(minn.score[3],p.score[3]);
			tot.score[0]+=p.score[0];
			tot.score[1]+=p.score[1];
			tot.score[2]+=p.score[2];
			tot.score[3]+=p.score[3];
			if (p.score[1]<60) eg[0]++;
			else if (p.score[1]<70) eg[1]++;
			else if (p.score[1]<80) eg[2]++;
			else if (p.score[1]<90) eg[3]++;
			else eg[4]++;
			if (p.score[2]<60) mt[0]++;
			else if (p.score[2]<70) mt[1]++;
			else if (p.score[2]<80) mt[2]++;
			else if (p.score[2]<90) mt[3]++;
			else mt[4]++;
			if (p.score[3]<60) cp[0]++;
			else if (p.score[3]<70) cp[1]++;
			else if (p.score[3]<80) cp[2]++;
			else if (p.score[3]<90) cp[3]++;
			else cp[4]++;
			if (p.score[0]<180) tott[0]++;
			else if (p.score[0]<210) tott[1]++;
			else if (p.score[0]<240) tott[2]++;
			else if (p.score[0]<270) tott[3]++;
			else tott[4]++;
		}
		void sort(int m,int t,int w)
		{
			if (t>=w) return;
			int i=t,j=w;
			stu mid=inf[i];
			while(i<j)
			{
				while(i<j && inf[j].score[m]<mid.score[m]) j--;
				if (i<j)
				{
					inf[i]=inf[j];
					i++;
				}
				while(i<j && inf[i].score[m]>mid.score[m]) i++;
				if (i<j)
				{
					inf[j]=inf[i];
					j++;
				}
			}
			inf[i]=mid;
			sort(m,t,i-1);
			sort(m,i+1,w);
		}
		void search(string q)
		{
			int flag=0;
			for(int i=1;i<=sum;++i)
			{
				if (inf[i].name==q || inf[i].num==q)
				{
					if (!flag)
					{
						flag=1;
						cout << setw(10) << "学号" << setw(10) << "姓名" << setw(10) << "英语" << setw(10) << "数学" << setw(10) << "计算机" << setw(10) << "总分" << endl;					
					}
					cout << setw(10) << inf[i].num << setw(10) << inf[i].name << setw(10) << inf[i].score[1] << setw(10) << inf[i].score[2] << setw(10) << inf[i].score[3] << setw(10) << inf[i].score[0] << endl;
				} 
			}
			if (!flag) cout << "No matched information!\n";
		}
		void showinf()
		{
			cout << "        共有" << sum << "位学生\n";
			if (sum)
			{
				cout << "  " << setw(20) << "最高分" << setw(10) << "最低分" << setw(10) << "平均分\n";
				cout << setw(10) << "英语" << setw(10) << maxn.score[1] << setw(10) << minn.score[1] << setw(10) << tot.score[1]/(sum) << endl;
				cout << setw(10) << "数学" << setw(10) << maxn.score[2] << setw(10) << minn.score[2] << setw(10) << tot.score[2]/(sum) << endl;
				cout << setw(10) << "计算机" << setw(10) << maxn.score[3] << setw(10) << minn.score[3] << setw(10) << tot.score[3]/(sum) << endl;
				cout << setw(10) << "总分" << setw(10) << maxn.score[0] << setw(10) << minn.score[0] << setw(10) << tot.score[0]/(sum) << endl << endl;
				cout << setw(10) << "人数" << "  " << setw(10) << "<60" << setw(10) << "60-69" << setw(10) << "70-79" << setw(10) << "80-89" << setw(10) << ">=90\n";
				cout << setw(10) << "英语" << setw(10) << eg[0] << setw(10) << eg[1] << setw(10) << eg[2] << setw(10) << eg[3] << setw(10) << eg[4] << endl;
				cout << setw(10) << "数学" << setw(10) << mt[0] << setw(10) << mt[1] << setw(10) << mt[2] << setw(10) << mt[3] << setw(10) << mt[4] << endl;
				cout << setw(10) << "计算机" << setw(10) << cp[0] << setw(10) << cp[1] << setw(10) << cp[2] << setw(10) << cp[3] << setw(10) << cp[4] << endl;
				cout << setw(10) << "平均分" << setw(10) << tott[0] << setw(10) << tott[1] << setw(10) << tott[2] << setw(10) << tott[3] << setw(10) << tott[4] << endl;
			}
		}
		int showsum() 
		{
			return sum;
		}
		friend ostream& operator<<(ostream& os,const table& tb)
		{
			if (!tb.sum) os << "暂无学生信息!\n";
			else
			{
				os << " " << setw(10) << "学号" << setw(10) << "姓名" << setw(10) << "英语" << setw(10) << "数学" << setw(10) << "计算机" << setw(10) << "总分" << endl; 
				for(int i=1;i<=tb.sum;++i)
				{
					os << setw(10) << tb.inf[i].num << setw(10) << tb.inf[i].name << setw(10) << tb.inf[i].score[1] << setw(10) << tb.inf[i].score[2] << setw(10) << tb.inf[i].score[3] << setw(10) << tb.inf[i].score[0] << endl;
				}
			}
			return os;
		}
};

table tb;
stu tmps;
string ctmp;

int main()
{
	int c;
	cout << "欢迎使用学生成绩管理系统！\n1.插入一个新的学生信息\n2.按学生的英语成绩进行排序\n3.按学生的数学成绩进行排序\n4.按学生的计算机成绩进行排序\n5.按学生的总分进行排序\n6.学生成绩总览\n7.输出成绩单\n8.查询学生信息\n9.刷新屏幕\n0.退出\n";
	cin >> c;
	while(c)
	{
		switch(c)
		{
			case(1):
				cout << "输入学生姓名:";
				cin >> tmps.name;
				cout << "输入学号:";
				cin >> tmps.num;
				cout << "输入英语成绩:";
				cin >> tmps.score[1];
				cout << "输入数学成绩:";
				cin >> tmps.score[2];
				cout << "输入计算机成绩:";
				cin >> tmps.score[3];
				tmps.score[0]=tmps.score[1]+tmps.score[2]+tmps.score[3];
				tb.insert(tmps);
				break;
			case(2):
				tb.sort(1,1,tb.showsum());
				break;
			case(3):
				tb.sort(2,1,tb.showsum());
				break;
			case(4):
				tb.sort(3,1,tb.showsum());
				break;
			case(5):
				tb.sort(0,1,tb.showsum());
				break;
			case(6):
				tb.showinf();
				break;
			case(7):
				cout << tb << endl;
				break;
			case(8):
				cin >> ctmp;
				tb.search(ctmp);
				break;
			case(9):
				system("cls");
				cout << "欢迎使用学生成绩管理系统！\n1.插入一个新的学生信息\n2.按学生的英语成绩进行排序\n3.按学生的数学成绩进行排序\n4.按学生的计算机成绩进行排序\n5.按学生的总分进行排序\n6.学生成绩总览\n7.输出成绩单\n8.查询学生信息\n9.刷新屏幕\n0.退出\n";
				break;
		}
		cin >> c;
	}
	return 0;
} 
