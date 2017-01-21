#include<stdio.h>
#include<ListNode.h>
#define N 5
#define DL 3
#define R 10
void Print(ListNode La[N],int index);
void LSD(ListNode La[N]);
void Distribute(ListNode La[N],ListNode* first[R],ListNode* last[R],int index);
void Collect(ListNode La[N],ListNode* first[R],ListNode* last[R],int index);
int pro(char c);
int SearchNext(ListNode* first[],int index);
void main()
{
	char a[N][DL+1]={"152","123","042","012","002"};
	ListNode La[N+1];	
	int i;
	for(i=0;i<N;i++)
	{
		La[i+1].data=&a[i][0];
		La[i].next=&La[i+1];
	}
	La[N].next=NULL;
	LSD(La);
}
void Print(ListNode La[],int index)
{
	ListNode *p;
	for(p=La[index].next;p!=NULL;p=p->next)
	{
		printf("%s ",(char*)p->data);
	}
	printf("\n");
}
void LSD(ListNode La[N])
{
	int i;
	for(i=DL-1;i>=0;i--)
	{
		ListNode* first[R]={0};
		ListNode* last[R]={0};
		Distribute(La,first,last,i);
		Collect(La,first,last,i);
		Print(La,0);
	}
}
void Distribute(ListNode La[N],ListNode* first[R],ListNode* last[R],int index)
{
	ListNode* p;
	for(p=La[0].next;p!=NULL;p=p->next)
	{
		char* t=(char*)p->data;
		int k=pro(t[index]);
		if(first[k]==NULL)
		{
			first[k]=p;
		}
		else
		{
			last[k]->next=p;
		}
		last[k]=p;
	}
}
void Collect(ListNode La[N],ListNode* first[R],ListNode* last[R],int index)
{
	int pre,i;
	pre=i=SearchNext(first,0);
	ListNode* p=first[pre];
	La[0].next=first[pre];
	while(i<R)
	{
		i=SearchNext(first,i+1);
		if(i<R)
		{
			last[pre]->next=first[i];
			pre=i;			
		}
	}
	last[pre]->next=NULL;
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
int pro(char c)
{
	return c-'0';
}