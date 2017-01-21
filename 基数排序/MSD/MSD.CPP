#include<stdio.h>
#include<ListNode.h>
#define N 5
#define DL 3
#define R 10
void Print2(ListNode La[],int index);
void MSD(ListNode La[N]);
void Construct(ListNode La[N],ListNode* first[R],int left,int right,int acc[R]);
void MSDSort(ListNode La[N],ListNode* first[N],ListNode* last[N],int left,int right,int index);
int SearchNext(ListNode* first[N],int index);
int pro(char c);
void main()
{
	char a[N][DL+1]={"152","323","042","012","002"};
	ListNode La[N+1];	
	int i;
	for(i=0;i<N;i++)
	{
		La[i+1].data=&a[i][0];
		La[i].next=&La[i+1];
	}
	La[N].next=NULL;
	MSD(La);
	Print2(La,1);
}
void Print2(ListNode La[],int index)
{
	int i;
	for(i=index;i<=N;i++)
	{
		printf("%s ",(char*)La[i].data);
	}
	printf("\n");
}
void MSD(ListNode La[N])
{
	ListNode* first[R]={0};
	ListNode* last[R]={0};
	Print2(La,1);
	MSDSort(La,first,last,1,N,0);
}
void MSDSort(ListNode La[N],ListNode* first[N],ListNode* last[N],int left,int right,int index)
{
	printf("%d %d->%d:",index,left,right);
	Print2(La,1);
	if(left>=right)
	{
		return;
	}
	int i;
	for(i=left;i<=right;i++)
	{
		char* c=(char*)La[i].data;
		int k=pro(c[index]);
		if(first[k]==NULL)
		{
			first[k]=&La[i];
		}
		else
		{
			last[k]->next=&La[i];
		}
		last[k]=&La[i];
		last[k]->next=NULL;
	}
	int acc[R]={0};
	Construct(La,first,left,right,acc);

	int pre;
	pre=i=SearchNext(first,0);
	while(i<R)
	{
		i=SearchNext(first,i+1);
		if(i<R && index+1<DL)
		{
			ListNode* f[R]={0};
			ListNode* l[R]={0};
			MSDSort(La,f,l,acc[pre],right,index+1);
		}
		pre=i;
	}
}
int SearchNext(ListNode* first[N],int index)
{
	int i;
	for(i=index;i<R;i++)
	{
		if(first[i]!=NULL)
		{
			return i;
		}
	}
	return R;
}
void Construct(ListNode La[N],ListNode* first[R],int left,int right,int acc[R])
{
	int i=-1,j=left;
	ListNode La2[N+1];
	while(i<R)
	{
		i=SearchNext(first,i+1);
		if(i<R)
		{
			ListNode* p;
			acc[i]=j;
			for(p=first[i];p!=NULL;p=p->next)
			{
				La2[j].data=p->data;
				j++;
			}
		}
	}
	for(i=left;i<=right;i++)
	{
		La[i].data=La2[i].data;
	}
}
int pro(char c)
{
	return c-'0';
}