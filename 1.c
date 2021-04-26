#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 20
#include<time.h>

struct details{
	char accountno[30];
	int amt;
	char operation[20];
	int balance;
	
};
typedef struct details detail; 

struct STACK{
	detail arr[MAX];
	int top;
	
};

struct POINT{char username[30];struct POINT *left;struct POINT *right; char password[30];char accountno[30]; int balance;
};
typedef struct POINT *USERS;



void push(struct STACK *s,char *accountno,int amt,char *operation,int balance)
{
	if(s->top==MAX-1)
	{
		printf("PASS BOOK IS FULL PRESS 1 TO GENERATE NEW PASSBOOK\n");
		return;
	}
	s->top++;
	strcpy(s->arr[s->top].accountno,accountno);
	strcpy(s->arr[s->top].operation,operation);
	s->arr[s->top].amt=amt;
	s->arr[s->top].balance=balance;
	printf("THE TRANSACTION WAS SUCCESSFULL \n");
}
void kill(struct STACK *s)
{
	while(1)
	{
		if(s->top==-1)
		{
			s->top++;
			return;
		}
		s->top--;
	}
}

void printcar(struct STACK *s,char *name,int option)
{
	time_t t=time(NULL);
	struct tm *tm=localtime(&t);
	if(s->top==0)
	{
		printf("THE PASSBOOK IS EMPTY\n");
		return;
	}
	printf("YOUR PASSBOOK IS:\n");
	int i,j=0,q=0,total=0,bal;
	if(option==1)
	{
	FILE * a;
	a=fopen(name,"a");
	int ko=s->top;
	printf("\nNO:\tNAME:\tACCOUNT NO:\tAMOUNT(Rs.)\tOPERATION\tBALANCE(Rs.)\n");
	fprintf(a,"\n%s%s\n%s\t%s\t%s\t\t%s\t%s\n","UPDATED ON: ",asctime(tm),"NAME:","ACCOUNT NO","AMOUNT(Rs.)","OPERATION","BALANCE(Rs.)");
	for(i=1;i<=ko;i++)
	{
		q++;
		fprintf(a,"%d\t",q);
		fprintf(a,"%s\t\t",name);
		fprintf(a,"%s\t\t",s->arr[i].accountno);
		fprintf(a,"%d\t",s->arr[i].amt);
		fprintf(a,"%s\t",s->arr[i].operation);
		fprintf(a,"%d\n",s->arr[i].balance);
		printf("%d\t",q);
		printf("%s\t",name);
		printf("%s\t",s->arr[i].accountno);
		printf("%d\t",s->arr[i].amt);
		printf("%s\t",s->arr[i].operation);
		bal=s->arr[i].balance;
		printf("%d\n",bal);	
	}
	printf("NO OF TRANSACTIONS: %d\n",q);
	printf("CURRENT BALANCE %d ",bal);
	fprintf(a,"%s %d\n","NO OF TRANSACTIONS:",q);
	fprintf(a,"%s:%d\n","CURRENT BALANCE:",bal);
	}
/*	if(option==1)	
	{
		i=s->top;
	printf("%s\t%-35s\t%-s\t%s\n","NO","ITEM","QUANTITY","PRICE");
	for(i;i>0;i--)
	{
		j+=s->arr[i].qty;
		total+=(s->arr[i].price)*(s->arr[i].qty);
		printf("%d\t",q);
		printf("%-35s\t",s->arr[i].name);
		printf("%d\t",s->arr[i].qty);
		printf("%d\n",s->arr[i].price);
		q++;
	}
	printf("NO OF ITEMS: %d\n",j);
	printf("FINAL AMOUNT TO BE PAID: %d",total);	
	}*/
}


USERS makenode(char *username,char *password,char * accountno,int balance)
{
	USERS temp=(struct POINT*)malloc(sizeof(struct POINT));
	strcpy(temp->username,username);
	temp->balance=balance;
	strcpy(temp->accountno,accountno);
	strcpy(temp->password,password);
	temp->left=NULL;
	temp->right=NULL;
	return temp;
} 

USERS insert(USERS temp,char *username,char *password,char *accountno,int balance)
{
	int a;
	if(temp==NULL)
	return makenode(username,password,accountno,balance);
	if(temp)
	a=strcmp(temp->accountno,accountno);
	if(a>0)
	temp->left=insert(temp->left,username,password,accountno,balance);
	else if(a<0)
	temp->right=insert(temp->right,username,password,accountno,balance);
	return temp;
}
int check(USERS temp,char*accountno,char*password)
{		
		int a,b;
		if(temp)
		{
		a=strcmp(temp->accountno,accountno);
		b=strcmp(temp->password,password);
		if(a==0&&b==0)
		return 1;
		if(a<0)
		return check(temp->right,accountno,password);
		if(a>0)
		return check(temp->left,accountno,password);
		}
		return 0;
	
}
int search(USERS temp,char*accountno)
{		
		int a;
		if(temp)
		{
			a=strcmp(temp->accountno,accountno);
			if(a==0)
			{
				printf("NAME: %s\n",temp->username);
				printf("PASSWORD: %s\n",temp->password);
				printf("ACCOUNT NO: %s\n",temp->accountno);
				printf("BALANCE IS: %d",temp->balance);
				return 1;
			}
			if(a<0)
				return search(temp->right,accountno);
			if(a>0)
				return search(temp->left,accountno);
		}
	
}
void inorder(USERS l)
{
	if(l)
	{
		inorder(l->left);
		printf("\t%s\t%s\n",l->username,l->accountno);
		inorder(l->right);
	}
}

int update_check(USERS temp,char*accountno,int val,int mode)
{		if(mode==1)	
	{
		int a;
		if(temp)
		{
			a=strcmp(temp->accountno,accountno);
			if(a==0)
			{
				temp->balance=temp->balance+val;	
				return 1;
			}
			if(a<0)
				return update_check(temp->right,accountno,val,1);
			if(a>0)
				return update_check(temp->left,accountno,val,1);
		}
		
	}
	if(mode=2)
	{
		int a;
		if(temp)
		{
			a=strcmp(temp->accountno,accountno);
			if(a==0)
			{
				return temp->balance;
			}
			if(a<0)
				return update_check(temp->right,accountno,val,2);
			if(a>0)
				return update_check(temp->left,accountno,val,2);
		}
		
	}	
}


void loggedin(char*accountno,USERS U,struct STACK *s)
{
	int i,select,option,discount=0;
	
	
	USERS temp=U;
	int bal, amt;
	float val;
	
	k:
	printf("\n1)USER DETAILS 2)TRANSACTIONS 3)PASSBOOK GENERATION 4)LOG OUT : ");
	while(1)
	{
		scanf("%d",&option);
		if(option==1)
		{
			search(temp,accountno);
			goto k;
		}
		
		if(option==2)
		{
			int select;
		printf("SELECT THE OPERATION:: 1)CREDIT 2)DEBIT\n");
		while(1)
		{
			scanf("%d",&select);
			if(select>3)
			{
			printf("\nNOT AVAILABLE:");
			goto k;
			}
			if(select==-1)
			{
			printf("\n");
				goto k;
			}
			if(select==1)
			{
				printf("ENTER AMONUT TO BE CREDITED:");
				scanf("%d",&amt);
				update_check(U,accountno,amt,1);
				push(s,accountno,amt,"Credit",update_check(U,accountno,0,2));	
			}
			if(select==2)
			{
				printf("ENTER AMONUT TO BE DEBITED:");
				scanf("%d",&amt);
				update_check(U,accountno,-amt,1);
				push(s,accountno,amt,"Debit",update_check(U,accountno,0,2));	
			}
			goto k;
		}
		}
	
	
		if(option==4)
		{
			//printf("ENTER THE INTERST RATE YOU WANT T")
		}
	
		if(option==3)
		{
			int a;
			printf("PRESS 1 TO GENERATE PASSBOOK\n");
			scanf("%d",&a);
			if(a==1)
			{
				char temp[20];
				printf("ENTER YOUR NAME:");
				scanf("%s",temp);
				printcar(s,temp,1);	
			}
			goto k;
		}
	
	
		if(option==4)
		{
			printf("THANKS FOR USING OUR BANKING SERVICE");
			system("cls");
			printf("MENU:\n1)CREATE ACCOUNT 2)LOGIN ACCOUNT 3)EXIT \n");
			break;
		}		
		//}
		
	}
}

void menu(USERS U)
{
	struct STACK s; 
	s.top=0;

	int i,no,bal;
	char name[30],pass[30],pincode[10],mob[20],city[20],code[30],dis[10],sno[20];
	k:
	printf("1)CREATE ACCOUNT 2)LOGIN ACCOUNT 3)EXIT :");
	scanf("%d",&i);
	if(i==1)
	{
	
				printf("ENTER YOUR NAME: ");
				scanf("%s",name);
				printf("ENTER PASSWORD: ");
				scanf("%s",pass);
				no=(rand()%10000)+1000;
				printf("YOUR ACCOUNT NO IS : %d",no);
				itoa(no,sno, 10);
				U=insert(U,name,pass,sno,0);
				printf("\nUSER HAS BEEN REGISTERED\n");
				
				goto k;
	}
	if(i==2)
	{
				printf("ENTER ACCOUNT NO: ");
				scanf("%s",sno);
				printf("ENTER PASSWORD: ");
				scanf("%s",pass);
				if(check(U,sno,pass))
				{	
					printf("\nLOGGED IN SUCCESSFULLY..");
					printf("\n WELCOME Mr.%s",name);
					//system("color 1");
					system("cls");
					loggedin(sno,U,&s);
					goto k;
				}
				else
				{
				printf("\nCHECK YOUR DETAILS..\n\n");
				goto k;
				}		
	}
	if(i==3)
	{
		return;
	}
	
	if(i==-1)
	return;
}

int main()
{
	struct STACK s; 
	s.top=-1;
	USERS U=NULL;
	
	menu(U);
	
}
