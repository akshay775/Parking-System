#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct node
{
	int id,money,h,m;
    struct node *next,*prev;
};

typedef struct node NODE;
NODE *start=NULL;
int i;

int emptySlot()
{
	if(start==NULL)
	return 1;
	else
	return 0;
}

void parkVehicle(int slot,int amount,int eth,int etm)
{
	NODE *nw,*last;
	nw=(NODE*) malloc(sizeof(NODE));
	nw->id=slot;
	nw->money=amount;
	nw->h=eth*60;
	nw->m=etm;
	nw->next=nw->prev=NULL;
	if(emptySlot())
	{
		start=nw;
	}
	else
	{
		last=start;
		while(last->next!=NULL)
		{
			last=last->next;
		}
		last->next=nw;
		nw->prev=last;
	}
}

NODE * removeVehicle(NODE *cur,int slot)
{
	int f=0;
	NODE *prv,*t;
	cur=start;
	while(cur!=NULL)
	{
		if(cur->id==slot)
		{
			f=1;
			break;
		}
		else
		{
		prv=cur;
		cur=cur->next;	
		}
	}
	if(f==1)
	{
		if(cur==start)
		{
			start=start->next;
			if(cur->next!=NULL)	
			start->prev=NULL;
		}
		else if(cur->next==NULL)
		{
			prv->next=NULL;
		}
		else
		{
			t=cur->next;
			prv->next=t;
			t->prev=prv;
		}
		return cur;
	}
	else
	printf("NO Slot found\n");
}



void parkingArea()
{
	NODE *r;
	if(!emptySlot())
	{
		r=start;
		    printf("\t ----------------\n");
		while(r!=NULL)
		{
			printf("\t| Slot %d is Full |\n",r->id);
			printf("\t ----------------\n");
			r=r->next;
		}
	}
	else
	printf("\n\t**Every slot is Empty**\n");
}

void DisplayPrice()
{
	printf("\n Price Displayed Below Is for 1hr\n");
	printf("\t-------------------------------\n");
	printf("\t|Sr.No|   Vehicle     | Price |\n");
	printf("\t-------------------------------\n");
	printf("\t| 1.  | 2-Wheeler     |  200  |\n");
	printf("\t-------------------------------\n");
	printf("\t| 2.  | 4-Wheeler     |  250  |\n");
	printf("\t-------------------------------\n");
	printf("\t| 3.  | 5-Seater      |  300  |\n");
	printf("\t-------------------------------\n");
	printf("\t| 4.  | 7-Seater      |  350  |\n");
	printf("\t-------------------------------\n");
	printf("\t| 5.  | 12-Seater     |  400  |\n");
	printf("\t-------------------------------\n");	
	printf("\nAdditional Charges for extra time is same for all,<100 per half-hour>\n");
}

int price(int ch)
{
	switch(ch)
	{
		case 1:return 200;
		break;
		case 2:return 250;
		break;
		case 3:return 300;
		break;
		case 4:return 350;
		break;
		case 5:return 400;
		break;
	}
}

void credit(int price)
{
	int i,ph[10],pin;
	printf("\t\nYOUR TOTAL AMOUNT IS %d\n",price);
	printf("\nPHONE NUMBER PLZZ!!\n");
	for(i=0;i<9;i++)
	{
		scanf("%d",&ph[i]);
	}
	printf("\n\n******AFTER SWIPE*******\n");
	printf("\nENTER PIN\n");
	fflush(stdin);
	scanf("%d",&pin);
	printf("\nSUCCESSFULL !!!!\n");
}

void cash(int price)
{
	int amount,balance,money;
	printf("\tYOUR TOTAL AMOUNT IS %d\n",price);
	 bal:printf("\n\tENTER YOUR MONEY\n");
	     printf("\n\t<Rs 20,Rs 50,Rs 100,Rs 200,Rs 500>\n");
	     fflush(stdin);
	     scanf("%d",&amount);
	     if(amount<price)
	  {
	 balance=price-amount;
	 printf("\n\tYOU HAVE ENTERED LESS AMOUNT \n\t BALANCE IS %d\n",balance);
	 price=balance;
	 goto bal;
	}
	else if(amount>price)
	{
		money=amount-price;
		printf("\n\tYOU HAVE ENTERED EXCESS AMOUNT \n\t YOUR RETURN MONEY %d\n",money);
	}
}

void vehicleParking()
{
	int ch,slot,amount,eth,etm;
	DisplayPrice();
	type:printf("\nEnter Your Vehicle Type\n");
	fflush(stdin);
	scanf("%d",&ch);
	if(ch>5)
	{
		printf("\nInvalid Option\n");
		goto type;
	}
	amount=price(ch);
	time:printf("\nENTER TIME <in hours and min>\n");
	fflush(stdin);
	scanf("%d%d",&eth,&etm);
	if(eth>24 || etm>60)
	{
		printf("\nInvalid time\n");
		goto time;
	}
	if(eth>12)
	eth=eth-12;
	parkingArea();
	printf("\nYour Parking Slot\n");
	fflush(stdin);
	scanf("%d",&slot);
	parkVehicle(slot,amount,eth,etm);
}

void filehandling(int ps,int eh,int em,int amount,int exh,int exm)
{
	FILE *fp;
	fp=fopen("Parking.txt","a");
	if(fp!=NULL)
	{
		if(i==0)
		{
		fprintf(fp,"+---------------------------------------------------------------------+\n");
    	fprintf(fp,"|S.N|    Parking Slot    |   Entry Time    |   Exit Time    | Amount  |\n");
    	fprintf(fp,"+---------------------------------------------------------------------+\n");
    	}
    	fprintf(fp,"|%d  |    %13d   |%7d:%.2d       |%9d:%.2d    |%7d  |\n", i + 1,ps,(eh/60),em,(exh/60),exm,amount);
    	fprintf(fp,"+---------------------------------------------------------------------+\n");
	}
	i++;	
}


void exiting()
{
	NODE *cur;
	int exh,exm,slot,ftm,famount,c;
	slot:printf("\nEnter the Parking Number / Slot\n");
	fflush(stdin);
	scanf("%d",&slot);
	cur=removeVehicle(cur,slot);
	exit:printf("\nEnter the exit time\n");
	fflush(stdin);
	scanf("%d%d",&exh,&exm);
	if(exh>24 || exm>60)
	{
		printf("\nInvalid time\n");
		goto exit;
	}
	if(exh>12)
	{
	exh=exh-12;
    }
	exh=exh*60;
	ftm=(exh+exm)-(cur->h+cur->m);
	if(ftm>=90)
	{
		if(ftm>=90 && ftm<120)
		famount=cur->money+100;
		else if(ftm>=120 && ftm<150)
		famount=cur->money+200;
		else if(ftm>=150 && ftm<180)
		famount=cur->money+300;
		else if(ftm>=180 && ftm<=300)
		famount=cur->money+400;
		else
		famount=1200;
	}
	else
	famount=cur->money;
	filehandling(cur->id,cur->h,cur->m,famount,exh,exm);
	printf("HOW WOULD YOU LIKE TO PAY THROUGH\n");
    printf("1.CREDIT\n");
    printf("2.CASH\n");
    fflush(stdin);
    scanf("%d",&c);
    if(c==1)
    {
       credit(famount);
    }
    else
    {
       cash(famount);
    }
 
}

int count()
{
	NODE *r;
	int c=0;
		r=start;
		while(r!=NULL)
		{
			r=r->next;
			c++;
		}
	return c;
}

int main()
{
	int f=0;
	char ch;
	while(1)
	{
	abc:printf("\nIS YOUR CAR PARKED <Y for Yes> <N for No> <D for display> <E for exit>\n");
	fflush(stdin);
	scanf("%c",&ch);
	switch(ch)
	{
	case 'N':
		if(count()>10)
	 {
		f=1;
	 } 
	 else
	 {
	 	f=0;
	 }
	 if(f==1)
	 {
	 	printf("\nEvery SLOT is FUll\n");
		 goto abc;
	 }
	vehicleParking();
	printf("\n**THANK YOU HAVE A NICE  DAY**\n");	
	break;
	case 'Y': exiting();
	printf("\n**THANK YOU HAVE A NICE  DAY**\n");	
	break;
	case 'D':parkingArea();
	break;
	default :return 0;
	}
	}
}
