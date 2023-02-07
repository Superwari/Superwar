#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>

#define U 1
#define D 2
#define L 3
#define R 4                        //�D�����A U�G�W D:�U L:�� R:�k
typedef struct snake               //�D�����@�Ӹ`�I
{
	int x;                        //�`�I��x�y��
	int y;                        //�`�I��y�y��
	struct snake *next;           //�D�����U�@�Ӹ`�I
}snake;
int score=0,add=10;              //�`�o���M�C�Y�@���������o��
int highscore=0;                 //�̰���
int status,sleeptime=200;        //�D�e�i���A�A�C�����檺�ɶ����j
snake *head,*food;               //�D�Y���СA��������
snake *q;                        //�M���D�ɥΪ�����
int endgamestatus=0;             //�C�������ɪ����A
HANDLE hOut;                      //�����i����{���X
void gotoxy(int x,int y);
int color(int c);
void printsnake();
void wlcome();
void createmap();
void scoreandtips();
void initsnake();
void createfood();
int biteself();
void cantcrosswall();
void speedup();
void speeddown();
void snakemove();
void keyboardcontrol();
void lostdraw();
void endgame();
void choose();
void file_out();
void file_in();
void explation();

main()
{
    system("mode con cols=100 lines=30");
    printsnake();
    wlcome();
    file_out();
    keyboardcontrol();
    endgame();
}

 void gotoxy(int x,int y)//�]�w�C�Ц�m
{COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c); //�w��C�Ъ���m
}

int color(int c)//�]�w�C��
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
    return 0;
}
void printsnake()//�C�L�r���D
{
 	gotoxy(2,5);
	color(3);
	printf("�m�W�G�i�p��");

	gotoxy(2,6);
	color(3);
	printf("�Ǹ��G1910101099");

	gotoxy(35,1);
 	color(6);
 	printf("/^\\/^\\");

 	gotoxy(34,2);
 	printf("|_| o|");

 	gotoxy(33,2);
 	color(2);
 	printf("_");

 	gotoxy(25,3);
 	color(12);
 	printf("\\/");

 	gotoxy(31,3);
 	color(2);
 	printf("/");

 	gotoxy(37,3);
 	color(6);
 	printf("\\_/");

 	gotoxy(41,3);
 	color(10);
 	printf(" \\");

 	gotoxy(26,4);
 	color(12);
 	printf("\\____");

 	gotoxy(32,4);
 	printf("_________");

 	gotoxy(31,4);
 	color(2);
 	printf("|");

 	gotoxy(43,4);
 	color(10);
 	printf("\\");

 	gotoxy(32,5);
 	color(2);
 	printf("\\_______");

 	gotoxy(44,5);
 	color(10);
 	printf("\\");

 	gotoxy(39,6);
 	printf("|    |              \\");

 	gotoxy(38,7);
 	printf("/    /                \\");

 	gotoxy(37,8);
 	printf("/    /               \\ \\");

 	gotoxy(35,9);
 	printf("/    /                \\ \\");

 	gotoxy(34,10);
 	printf(" /   /                  \\  \\");

 	gotoxy(33,11);
 	printf("/    /        _----_        \\  \\");

 	gotoxy(32,12);
 	printf("/    /         _-~   ~-_        |  |");

 	gotoxy(31,13);
 	printf("(     (     _-~    _--_    ~-_     _/ |");

 	gotoxy(32,14);
 	printf("\\    ~-____-~    _-~    ~-_    ~-_-~ /");

 	gotoxy(33,15);
 	printf("~-_         _-~        ~-_       _-~");

 	gotoxy(35,16);
 	printf("~--____-~                ~-___-~");
}

 void wlcome()//�w�虜��
 {int n;
 int i,j=1;
 gotoxy(43,18);
 color(11);
 printf("�g�Y�D�j�@��");
 color(14);
 for(i=20;i<=26;i++)
    {
    	for(j=27;j<=74;j++)
    	{
    		gotoxy(j,i);
    		if(i==20||i==26)
    		{
    			printf("-");
			}
			else if(j==27||j==74)
			{
				printf("|");
			}
		}
	}
	color(12);
	gotoxy(35,22);
	printf("1.�}�l�C��");
	gotoxy(55,22);
	printf("2.�C������");
	gotoxy(35,24);
	printf("3.�h�X�C��");
	gotoxy(29,27);
	color(3);
	printf("�п��1 2 3\n");
	color(14);
	scanf("%d",&n);
	switch(n)
	{
	 case 1:
	 	system("cls");//�M��
	 createmap();
	 initsnake();
	 createfood();
	 keyboardcontrol();
	 break;
	 case 2:
	 	explation();
        break;
    break;
    case 3:
        exit(0);
    break;
    }
}
void createmap()//�إߦa��
{
	int i,j;
	for(i=0;i<58;i+=2)
	{
		gotoxy(i,0);
		color(5);
	    printf("��");
	    gotoxy(i,26);
		printf("��");
	}
	for(i=0;i<26;i++)
	{
		gotoxy(0,i);
	    printf("��");
	    gotoxy(56,i);
		printf("��");
	}
	for(i=2;i<56;i+=2)
	{
		for(j=1;j<26;j++)
		{
			gotoxy(i,j);
		    color(3);
		    printf("��\n\n");
		}

	}
}
 void scoreandtips()//�C�������k�����o���M�p����
 {
 	file_out();
 	gotoxy(64,4);
 	color(11);
 	printf("*�̰�����*: %d",highscore);
 	gotoxy(64,8);
 	color(14);
 	printf("�o��: %d ",score);
 	color(13);
 	gotoxy(73,11);
 	printf("�p����");
	gotoxy(60,13);
 	color(6);
 	printf("+---------------------+");
 	gotoxy(60,25);
 	printf("+---------------------+");
 	color(3);
 	gotoxy(64,14);
 	printf("�C�ӭ����o���G%d��",add);
 	gotoxy(64,16);
 	printf("�������A����r��ۤv");
 	gotoxy(64,18);
 	printf("�Ρ����������O����D������");
 	gotoxy(64,20);
 	printf("F1���[�t�AF2����t");
 	gotoxy(64,22);
 	printf("space: �Ȱ��C��");
 	gotoxy(64,24);
 	printf("ESC:�h�X�C��");
}
void file_out()//�}���ɮװO���̰���
{
	FILE *fp;
	fp=fopen("save.txt","a+");
	fscanf(fp,"%d",&highscore);
	fclose(fp);
}

void initsnake()
{
 	snake *tail;
 	int i;
 	tail=(snake*)malloc(sizeof(snake));
 	tail->x=24;
 	tail->y=5;
 	tail->next=NULL;
 	for(i=1;i<=4;i++)
 	{
 		head=(snake*)malloc(sizeof(snake));
 		head->next=tail;
 		head->x=24+2*i;
 		head->y=5;
 		tail=head;
	 }
	 while(tail!=NULL)
	 {gotoxy(tail->x,tail->y);
	  color(14);
	  printf("��");                   //�D���ѡ��զ�
	  tail=tail->next;
	 }
}
void createfood()//�H���X�{����
{
   snake *food_1;
   srand((unsigned)time(NULL));
   food_1=(snake*)malloc(sizeof(snake));
   while((food_1->x%2!=0))
   {
   	 food_1->x=rand()%52+2;
	}
   food_1->y=rand()%24+1;
   q=head;
   while(q->next==NULL)
   {
   	  if(q->x==food_1->x&&q->y==food_1->y)
   	  {
   	  	free(food_1);
   	  	createfood();
	  }
	  q=q->next;
   }
   gotoxy(food_1->x,food_1->y);
   food=food_1;
   color(12);
   printf("@");
}

int biteself()
{
	snake *self;                //�w�qself���D���W���D�Y�H�~���`�I
	self=head->next;
	while(self!=NULL)
	{
		if(self->x==head->x&&self->y==head->y)
		{
			return 1;
		}
		self=self->next;
	}
	return 0;
}

void cantcrosswall()
{
	if(head->x==0||head->x==56||head->y==0||head->y==26)
	{
		endgamestatus=1;
		endgame();
	}
}

void speedup()//�[�t
{
	if(sleeptime>=50)
	{
		sleeptime=sleeptime-10;
		add=add+2;
	 }
}

void speeddown()//��t
{
	if(sleeptime<350)
	{
		sleeptime=sleeptime+30;
		add=add-2;
		if(sleeptime==350)
		{
			add=1;
		}
	 }
}

 void snakemove()//�����V
{
	snake *nexthead;
	cantcrosswall();
	nexthead=(snake*)malloc(sizeof(snake));
	if(status==U)//�W
	{
		nexthead->x=head->x;         //�V�W�e�i�ɡAx���ܡAy-1
		nexthead->y=head->y-1;
		nexthead->next=head;
		head=nexthead;
		q=head;
		//�p�G�U�@�Ӧ�m�W�������A�U�@�Ӧ�m���y�ЩM�����y�ЬۦP
		if(nexthead->x==food->x&&nexthead->y==food->y)
		{
			while(q!=NULL)
			{
				gotoxy(q->x,q->y);
				color(14);
				printf("��");
				q=q->next;
			}
			score=score+add;
			speedup();
			createfood();
		}
	else
	{
		while(q->next->next!=NULL)//�p�G�S���J������
		      {
		      	gotoxy(q->x,q->y);
				color(14);
				printf("��");
				q=q->next;
			  }
  //�g�L�W�����j�� �Aq���V�D���A�D�����U�@�B�N�O�D���L�h����m
		      gotoxy(q->next->x,q->next->y);
			  color(3);
			  printf("��");//��_���L����m
			  free(q->next);
			  q->next=NULL;
		 }

	 }
  if(status==D)
  {
        nexthead->x=head->x;         //�V�U�e�i�ɡAx���ܡAy+1
		nexthead->y=head->y+1;
		nexthead->next=head;
		head=nexthead;
		q=head;
		//�p�G�U�@�Ӧ�m�W�������A�U�@�Ӧ�m���y�ЩM�����y�ЬۦP
		if(nexthead->x==food->x&&nexthead->y==food->y)
		{
			while(q!=NULL)
			{
				gotoxy(q->x,q->y);
				color(14);
				printf("��");
				q=q->next;
			}
			score=score+add;
			speedup();
			createfood();
		}
	else
	{
		while(q->next->next!=NULL)//�p�G�S���J������
		      {
		      	gotoxy(q->x,q->y);
				color(14);
				printf("��");
				q=q->next;
			  }
  //�g�L�W�����j�� �Aq���V�D���A�D�����U�@�B�N�O�D���L�h����m
		      gotoxy(q->next->x,q->next->y);
			  color(3);
			  printf("��");//��_���L����m
			  free(q->next);
			  q->next=NULL;
		 }
	}
 if(status==L)//��
   {
   	    nexthead->x=head->x-2;         //�V���e�i�ɡAx���ܡAy+1
		nexthead->y=head->y;
		nexthead->next=head;
		head=nexthead;
		q=head;
		//�p�G�U�@�Ӧ�m�W�������A�U�@�Ӧ�m���y�ЩM�����y�ЬۦP
		if(nexthead->x==food->x&&nexthead->y==food->y)
		{
			while(q!=NULL)
			{
				gotoxy(q->x,q->y);     //�����ܦ��D���W���@����
				color(14);
				printf("��");
				q=q->next;
			}
			score=score+add;
			speedup();
			createfood();
		}
	else
	{
		while(q->next->next!=NULL)//�p�G�S���J������
		      {
		      	gotoxy(q->x,q->y);
				color(14);
				printf("��");
				q=q->next;
			  }
  //�g�L�W�����j�� �Aq���V�D���A�D�����U�@�B�N�O�D���L�h����m
		      gotoxy(q->next->x,q->next->y);
			  color(3);
			  printf("��");//��_���L����m
			  free(q->next);
			  q->next=NULL;
		 }
   }
  if(status==R)
  {
  	    nexthead->x=head->x+2;         //�V�W�e�i�ɡAx���ܡAy-1
		nexthead->y=head->y;
		nexthead->next=head;
		head=nexthead;
		q=head;
		//�p�G�U�@�Ӧ�m�W�������A�U�@�Ӧ�m���y�ЩM�����y�ЬۦP
		if(nexthead->x==food->x&&nexthead->y==food->y)
		{
			while(q!=NULL)
			{
				gotoxy(q->x,q->y);
				color(14);
				printf("��");
				q=q->next;
			}
			score=score+add;
			speedup();
			createfood();
		}
	else
	{
		while(q->next->next!=NULL)//�p�G�S���J������
		      {
		      	gotoxy(q->x,q->y);
				color(14);
				printf("��");
				q=q->next;
			  }
  //�g�L�W�����j�� �Aq���V�D���A�D�����U�@�B�N�O�D���L�h����m
		      gotoxy(q->next->x,q->next->y);
			  color(3);
			  printf("��");//��_���L����m
			  free(q->next);
			  q->next=NULL;
		 }
}
  if(biteself()==1)
  {
  	endgamestatus=2;
  	endgame();
  }
}
void keyboardcontrol()
{
	status=R;
	while(1)
	{
		scoreandtips();
 //GetAsyncKeyState��ƥΨӧP�_��ƩI�s���w�����䪺���A
    if(GetAsyncKeyState(VK_UP)&&status!=D)
	  {
	  	status=U;
	   }
	   else if(GetAsyncKeyState(VK_DOWN)&&status!=U)
	  {
	  	status=D;
	   }
	   else if(GetAsyncKeyState(VK_LEFT)&&status!=R)
	  {
	  	status=L;
	   }
	   else if(GetAsyncKeyState(VK_RIGHT)&&status!=L)
	  {
	  	status=R;
	   }
	   if(GetAsyncKeyState(VK_SPACE))
	   {
	       while(1)
	        {
	//�I�ssleep��ơA�O�{�ǰ���A����F��䤤�]�w���޼Ʈɶ�
			   Sleep(300);
			   if(GetAsyncKeyState(VK_SPACE))
			   {
			   	  break;
				}
			}
	   }
	   else if(GetAsyncKeyState(VK_ESCAPE))
	   {
	   	    endgamestatus=3;
	   	    break;
	   }
	   else if(GetAsyncKeyState(VK_F1))
	   {
	   	    speedup();
	   }
	   else if(GetAsyncKeyState(VK_F2))
	   {
	   	    if(sleeptime<350)
	   	     {
	   	     	sleeptime=sleeptime+30;
	   	     	add=add-2;
	   	     	if(sleeptime==350)
	   	     	{
	   	     		add=1;
				}
	   	    }
	   }
	   Sleep(sleeptime);
	   snakemove();
	}
}

void lostdraw()
{
	system("cls");
	int i,j;
	gotoxy(17,5);
	color(11);
	printf("+------------------------");

	gotoxy(35,5);
	color(14);
	printf("o00o");

    gotoxy(39,5);
	color(11);
	printf("----------");

	gotoxy(48,5);
	color(14);
	printf("---");

	gotoxy(51,5);
	color(11);
	printf("----------");

	gotoxy(61,5);
	color(14);
	printf("o00o");

	gotoxy(65,5);
	color(11);
	printf("-----------------+");

	for(i=6;i<=19;i++)
	{
		gotoxy(17,i);
	    printf("|");
	    gotoxy(82,i);
	    printf("|");
		}
		gotoxy(17,20);
		printf("+----------------------------------");

		gotoxy(52,20);
		color(11);
		printf("-----------------------------+");
 }

  void endgame()
  {
  	system("cls");
  	if(endgamestatus==1)
  	{
  		lostdraw();
  		gotoxy(35,9);
  		color(12);
  		printf("�藍�_�A�z������F�C�C�������I");
	  }
	  else if(endgamestatus==2)
	  {
	  	lostdraw();
	  	gotoxy(35,9);
	  	color(12);
	  	printf("�藍�_�A�z�r��ۤv�F�C�C�������I");
	   }
	  else if(endgamestatus==3)
	  {
	  	lostdraw();
	  	gotoxy(40,9);
	  	color(12);
	  	printf("�z�����F�C���C");
	   }
	  	gotoxy(43,12);
	  	color(13);
	  	printf("�z���o���O %d",score);
	  	if(score>=highscore)
		  {
		  	color(10);
		  	gotoxy(33,16);
		  	printf("�зs�����աI�A�u�ΡI�I�I");
			file_in();
		   }
	choose();
  }
  void file_in()//�N�̰����x�s���ɮפ�
  {
  	FILE *fp;
  	fp=fopen("save.txt","w+");//�HŪ�g���覡�إ��ɮ�
  	fprintf(fp,"%d",score);
  	fclose(fp);
  }
  void choose()
  {
  	int n;
  	gotoxy(25,23);
  	color(12);
  	printf("�����@��-------1");
	gotoxy(52,23);
	printf("�����F�A�h�X-------2");
	gotoxy(46,25);
  	color(11);
  	printf("��ܡG");
  	scanf("%d",&n);
  	switch(n)
  	{
  		case 1:
  			system("cls");
  			score=0;
  			sleeptime=200;
  			add=10;
  			printsnake();
  			wlcome();
  			break;
  		case 2:
  			exit(0);
  			break;
  		default:
  			gotoxy(35,27);
  			color(12);
  			printf("�z��J���~�A�Э��s��J");
  			system("pause >nul");//�����N��
			endgame();
			choose();
			break;
	  }
   }
  void explation()
  {
  	int i,j=1;
  	system("cls");
  	color(13);
  	gotoxy(44,3);
  	printf("�C������");
	 color(2);
	 for(i=6;i<=22;i++)
	 {
	 	for(j=20;j<=75;j++)
	 	{
	 		gotoxy(j,i);
	 		if(i==6||i==22)printf("=");
	 		else if(j==20||j==75)printf("||");
		 }
	  }
	  color(3);
	  gotoxy(30,8);
	  printf("1�B�������A����r��ۤv");
	  color(3);
	  gotoxy(30,8);
	  printf("1�B�������A����r��ۤv");
	  color(10);
	  gotoxy(30,11);
	  printf("2�B�Ρ����������O����D������");
	  color(14);
	  gotoxy(30,14);
	  printf("3�BF1���[�t�AF2����t");
	  color(11);
	  gotoxy(30,17);
	  printf("4�B���Ů���Ȱ��C���A�A���Ů����~��");
	  color(4);
	  gotoxy(30,20);
	  printf("5�BESC�G�h�X�C���Aspace�G�Ȱ��C��");
	  getch();//�����N���^�D����
	  system("cls");
	  printsnake();
	  wlcome();
}
