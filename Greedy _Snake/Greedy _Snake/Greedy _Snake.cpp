#include"Greedy _Snake.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
////1�����ݶ���
//////////////////////////////////////////////


////����
typedef struct Coor
{
	int x;
	int y;
}Coor;

////�ߵķ���
typedef enum ch
{
	up = 72,//�ϼ���ֵ
	down = 80,//�¼���ֵ
	left = 75,//�����ֵ
	right = 77//�Ҽ���ֵ
}CH;

//////////////////////////////////////////////
////��
typedef struct Snake
{
	//ÿһ���ߵ�����
	struct Coor scr[Sanke_Size]; //ÿһ���ߵ�����
	int n;      //�ߵĳ���
	CH ch;
	int speed = 3;//��ȡ�ٶ�
}Snake;

//////////////////////////////////////////////
////ʳ��
typedef struct food
{
	//��λ
	Coor fco;//ʳ������
	int flag;//ʳ��״̬���Ƿ񱻳ԣ�
	
}food;
food fo;

Snake Sn;
//////////////////////////////////////////////
////�÷�
int Score=0; //�ܵ÷�
int add = 10;//��ʾÿ�γԵ�ʳ���10��
int Hight_Score =0;//��ʾ��ʷ��߷�
int r=0;//��ɫ����


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//2��ģ����� ����> ���ܻ��֣�������

////����ʵ�ֽӿ�
/////////////////////////////////////////////////////////////////////////////////////////////////
////��������
void Load_music()
{
	////����һ������
	////PlaySound(L"",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);  //wav���ָ�ʽ
	////��MP3����
	mciSendString("open mymusic.mp3 alias mymusic", 0, 0, 0);//ARNO�Ƕ����˼��.mp3��ı���
	////ѭ������
	mciSendString("play mymusic repeat", 0, 0, 0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//���ƿ�ʼ����
void Start_interface()
{
	IMAGE img;//������� ���ͼƬ
	loadimage(&img, "��ʼ����.jpg", 800, 480);//����ͼƬ
	initgraph(800, 480);//��ʼ��һ��800*480�Ĵ���
	putimage(0, 0, &img);//��ͼƬ��Ϊ����

	////����һƬ����������Ϸ��
	HRGN  rgn = CreateRectRgn(320, 300, 500, 420);
	setcliprgn(rgn);//������320, 300, 500, 420�ľ��������ó�������Ϊ��Ϣ��
	DeleteObject(rgn);//��Ҫռ��ϵͳ�ڴ�
	setcolor(RED);//�����ı���ɫ
	settextstyle(45, 0, "����");//�������弰��С
	setbkmode(TRANSPARENT);//�����ı��������Ϊ͸��
	outtextxy(330, 320, "̰����");
	setcolor(RED);//�����ı���ɫ
	settextstyle(20, 0, "����");//�������弰��С
	outtextxy(400, 390, "����xiaomu");


	////����һƬ��������˵�ѡ��
	HRGN  rgn1 = CreateRectRgn(585, 65, 800, 480);
	setcliprgn(rgn1);//������585, 65,800,480�ľ��������ó�������Ϊ��Ϣ��
	DeleteObject(rgn1);//��Ҫռ��ϵͳ�ڴ�
	setcolor(LIGHTRED);//�����ı���ɫ
	settextstyle(18, 0, "����");//�������弰��С
	outtextxy(640, 80, "��ӭ����");
	settextstyle(22, 0, "����");//�������弰��С
	outtextxy(610, 110, "̰���ߴ���ս");
	
	//һ�ֺܶ����ֵ����
	setcolor(BLACK);//�����ı���ɫ 
	settextstyle(15, 0, "����");
	RECT rect = { 600, 180, 780, 470 };
	drawtext(_T("��ѡ��\n\n\n��J��:   ��ʼ��Ϸ\n\n��K��:   ��Ϸ˵��\n\n��Esc��: �˳���Ϸ"), &rect, DT_WORDBREAK);

	settextstyle(13, 0, "����");
	RECT rect1 = { 610, 330, 750, 470 };
	drawtext(_T("��ܰ��ʾ��\n\n��Ҫ��������ʱ��ֻ�轫��ϲ������������Ϊ��mymusic.mp3���󣬺������ļ��ŵ�ͬһ�ļ��м��ɡ�"), &rect1, DT_WORDBREAK);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//����˵������
void Description_interface()
{
	IMAGE img;//������� ���ͼƬ
	loadimage(&img, "˵������.jpg", 800, 480);//����ͼƬ
	initgraph(800, 480);//��ʼ��һ��800*480�Ĵ���
	putimage(0, 0, &img);//��ͼƬ��Ϊ����

	setbkmode(TRANSPARENT);//�����ı��������Ϊ͸��

	////����һƬ��������˵�ѡ��
	HRGN  rgn1 = CreateRectRgn(0, 0, 800, 480);
	setcliprgn(rgn1);//������585, 65,800,480�ľ��������ó�������Ϊ��Ϣ��
	DeleteObject(rgn1);//��Ҫռ��ϵͳ�ڴ�
	setcolor(RED);//�����ı���ɫ
	settextstyle(24, 0, "����");//�������弰��С
	outtextxy(340, 80, "��Ϸ˵��");

	setcolor(LIGHTRED);//�����ı���ɫ
	settextstyle(18, 0, "����");//�������弰��С
	outtextxy(230, 110, "��Ϸ����");

	//һ�ֺܶ����ֵ����
	setcolor(BLACK);//�����ı���ɫ 
	settextstyle(15, 0, "����");
	RECT rect = { 270, 140, 800, 480 };
	drawtext(_T("[1]�����ܴ�ǽ\n\n[2]������ײ���Լ�"), &rect, DT_WORDBREAK);

	setcolor(LIGHTRED);//�����ı���ɫ
	settextstyle(18, 0, "����");//�������弰��С
	outtextxy(230, 200, "���ܼ�����������");

	//һ�ֺܶ����ֵ����
	setcolor(BLACK);//�����ı���ɫ 
	settextstyle(15, 0, "����");
	RECT rect1 = { 270, 230, 800, 480 };
	drawtext(_T("[1]���� �������������� �����ƶ�����\n\n[2]����W��Ϊ���١���S��Ϊ����\n\n[3]�����ո���ͣ��Ϸ���ٰ��ո������Ϸ\n\n[4]����P�����¿�ʼ\n\n[5]����Esc���˳���Ϸ\n\n[6]����Ϸ�ɼ�¼�÷ֺ���ʷ��߷�"), &rect1, DT_WORDBREAK);

	setcolor(LIGHTRED);//�����ı���ɫ
	settextstyle(18, 0, "����");//�������弰��С
	outtextxy(230, 410, "���أ�");
	setcolor(LIGHTRED);//�����ı���ɫ
	outtextxy(280, 410, "��Esc��");
	setcolor(RED);
	settextstyle(40, 0, "����");
	RECT rect3 = { 650, 150, 780, 470 };
	drawtext(_T("̰\n\n��\n\n��"), &rect3, DT_WORDBREAK);

}

/////////////////////////////////////////////////////////////////////////////////////////////////
//���ƽ�������
void Game_over(int sh)
{
	IMAGE img;//������� ���ͼƬ
	loadimage(&img, "��������.jpg", 800, 480);//����ͼƬ
	initgraph(800, 480);//��ʼ��һ��800*480�Ĵ���
	putimage(0, 0, &img);//��ͼƬ��Ϊ����

	HRGN  rgn = CreateRectRgn(185, 65, 790, 445);
	setcliprgn(rgn);//������185, 65, 585, 445�ľ��������ó�������Ϊ��Ϣ��
	DeleteObject(rgn);//��Ҫռ��ϵͳ�ڴ�
	setcolor(RED);//�����ı���ɫ
	settextstyle(45, 0, "����");//�������弰��С
	setbkmode(TRANSPARENT);//�����ı��������Ϊ͸��
	outtextxy(270, 100, "Game Over.");

	
	char SP[20] = "";
	sprintf(SP, "���ĵ÷��ǣ�:%d ", Score);
	settextcolor(RED);
	settextstyle(18, 0, "����");//�������弰��С
	outtextxy(320, 180, SP);
	

	if (sh > Score)
	{
		char SP1[50] = "";
		sprintf(SP1, "���ź���������ʷ��߷ֻ��:%d ", sh - Score);
		settextcolor(RED);
		settextstyle(18, 0, "����");//�������弰��С
		outtextxy(240, 230, SP1);
		Score = 0;
	}
	else
	{
		settextstyle(18, 0, "����");
		RECT rect1 = { 270, 230, 600, 350 };
		drawtext(_T("��ϲ����ˢ������ʷ��߷֣�"), &rect1, DT_WORDBREAK);
	}


	setcolor(RED);//�����ı���ɫ 
	RECT rect2 = { 250, 330, 780, 470 };
	drawtext(_T("������ѡ�����¿�ʼ���˳���Ϸ��\n\n      ��P����  ���¿�ʼ  \n\n      ��Esc�����˳���Ϸ  "), &rect2, DT_WORDBREAK);
	settextstyle(40, 0, "����");
	RECT rect3 = { 650, 150, 780, 470 };
	drawtext(_T("̰\n\n��\n\n��"), &rect3, DT_WORDBREAK);
}


/////////////////////////////////////////////////////////////////////////////////////////////////
//��Ϸ��ʼ��
void GameInIt()
{

	
	IMAGE img;//������� ���ͼƬ
	loadimage(&img, "��Ϸ����.jpg", 800, 480);//����ͼƬ
	initgraph(800, 480);//��ʼ��һ��800*480�Ĵ���
	putimage(0, 0, &img);//��ͼƬ��Ϊ����

	////����һƬ������Ϊ��Ϣ��
	HRGN  rgn = CreateRectRgn(585, 65, 800, 480);
	setcliprgn(rgn);//������585, 65,800,480�ľ��������ó�������Ϊ��Ϣ��
	DeleteObject(rgn);//��Ҫռ��ϵͳ�ڴ�
	setcolor(RED);//�����ı���ɫ
	settextstyle(30, 0, "����");//�������弰��С
	setbkmode(TRANSPARENT);//�����ı��������Ϊ͸��
	outtextxy(630, 80, "̰����");
	setcolor(RED);//�����ı���ɫ
	settextstyle(15, 0, "����");//�������弰��С
	outtextxy(650, 125, "����xiaomu");



	//һ�ֺܶ����ֵ����
	setcolor(BLACK);//�����ı���ɫ 
	settextstyle(15, 0, "����");
	RECT rect = { 600, 280, 780, 470 };
	drawtext(_T("��Ϸ˵����\n\n�����: ���Ʒ���\n\n�ո�  ��ͣ/����\n\n��P��:  ���¿�ʼ\n\n��ESC��:������Ϸ\n\n��W�����١�S������"), &rect, DT_WORDBREAK);

	

	////���߳�ʼ��
	//cleardevice();//����
	Sn.scr[0].x = 185;
	Sn.scr[0].y = 65;
	Sn.ch = right;//����Ϊ��
	Sn.n = 2;//����Ϊ2+1
	Sn.speed = 3;//�ٶ�Ϊ5-3
	fo.flag = 0;//������
	Score = 0;//����Ϊ0
	Hight_Score = Hight_Score_out();//��ʷ��߷�Ϊ�ļ��洢����߷�

	setfillcolor(LIGHTCYAN);
	fillrectangle(185, 65, 195, 75);
	

}

/////////////////////////////////////////////////////////////////////////////////////////////////
//�ò�ͬ��ɫ����һ����
void DrawSnake_1(int i)
{
	switch (r)
	{
	case 0:
		rectangle(Sn.scr[i].x, Sn.scr[i].y, Sn.scr[i].x + 10, Sn.scr[i].y + 10);
		r = 1;
		break;
	case 1:
		setfillcolor(LIGHTCYAN);
		fillrectangle(Sn.scr[i].x, Sn.scr[i].y, Sn.scr[i].x + 10, Sn.scr[i].y + 10);
		r = 2;
		break;
	case 2:
		setfillcolor(LIGHTBLUE);
		fillrectangle(Sn.scr[i].x, Sn.scr[i].y, Sn.scr[i].x + 10, Sn.scr[i].y + 10);
		r = 3;
		break;
	case 3:
		setfillcolor(LIGHTGREEN);
		fillrectangle(Sn.scr[i].x, Sn.scr[i].y, Sn.scr[i].x + 10, Sn.scr[i].y + 10);
		r = 4;
		break;
	case 4:
		setfillcolor(LIGHTMAGENTA);
		fillrectangle(Sn.scr[i].x, Sn.scr[i].y, Sn.scr[i].x + 10, Sn.scr[i].y + 10);
		r = 0;
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//����n����
void DrawSnake()
{	
	for (int i = Sn.n; i >= 0;i--)
	{
		DrawSnake_1(i);
	}	
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//�ߵ��ƶ�
void SnakeMove()
{
	
	for (int i = Sn.n; i > 0; i--)
	{
		Sn.scr[i].x = Sn.scr[i-1].x;
		Sn.scr[i].y = Sn.scr[i - 1].y;
	}
	
	switch (Sn.ch)
	{
	case up:
		Sn.scr[0].y -= 10;
		break;
	case down:
		Sn.scr[0].y += 10;
		break;
	case left:
		Sn.scr[0].x -= 10;
		break;
	case right:
		Sn.scr[0].x += 10;
		break;
	}
	DrawSnake();
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//�ı䷽��
void Changch(char input)
{
	
	input = getch();
	switch (input)
	{
	case up:
		if (Sn.ch != down)
		Sn.ch = up;
		break;
	case down:
		if (Sn.ch != up)
		Sn.ch = down;
		break;
	case left:
		if (Sn.ch != right)
		Sn.ch = left;
		break;
	case right:
		if (Sn.ch != left)
		Sn.ch = right;
		break;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////
//����ʳ������ʳ��
void CreateFood()
{
	srand(unsigned int (time(NULL)));

	fo.fco.x = 185+ (rand() % ((585 - 185) /10)) * 10;
	fo.fco.y = 65 + (rand() % ((445 - 65) / 10)) * 10;
	fo.flag = 1;//û����
}


/////////////////////////////////////////////////////////////////////////////////////////////////
//����ʳ��
void DrawFood()
{
	setlinecolor(RED);
	roundrect(fo.fco.x, fo.fco.y, fo.fco.x + 10,fo.fco.y + 10, 10,10);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//�ж�ʳ���Ƿ񱻳�ʳ��
int eatFood()
{
	if (Sn.scr[0].x == fo.fco.x && Sn.scr[0].y == fo.fco.y)
	{
		Score += add;
		Sn.n++;
		
		if (Score > Hight_Score)
		{
			Hight_Score += add;
		}

		fo.flag = 0;
		return fo.flag;
	}

	else
		return 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//�ߵ�״̬�����ж��Ƿ������Ϸ
int  SnakeStatus()
{
	if (Sn.scr[0].x<185 || Sn.scr[0].x>575|| Sn.scr[0].y<65 || Sn.scr[0].y>440)//ײǽ����
	{
		return 0;
	}
		
	else
	{
		for (int i = 1; i <= Sn.n; ++i)
		{
			if (Sn.scr[0].x == Sn.scr[i].x && Sn.scr[0].y == Sn.scr[i].y)
			{
				return 0;
			}
				
		}

		return 1;

	}
	
}

//��ȡ�ٶ�
int  myspeed()
{
	return Sn.speed;
}

//�ı��ٶ�
void Changespeed(char c)
{
	if (c == 87 || c == 119)
	{
		if (Sn.speed>0)
			Sn.speed--;
	}
		
	else if (Sn.speed<4)
	{
		 Sn.speed++;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//��ʾ״̬��
void ShowStatus_bar()
{
	Sleep(100);

	////����һƬ������Ϊ��Ϣ��
	HRGN  rgn = CreateRectRgn(609, 140, 760, 270);
	setcliprgn(rgn);//������609, 120, 800, 250�ľ��������ó�������Ϊ�÷���
	//setbkcolor(WHITE);
	setfillcolor(WHITE);
	solidrectangle(609, 120, 800, 270);	
	DeleteObject(rgn);//��Ҫռ��ϵͳ�ڴ�
	setbkmode(TRANSPARENT);//�����ı��������Ϊ͸��
	

	char SP[20] = "";
	sprintf(SP, "�ٶȣ�:%d ", 5-Sn.speed);
	settextcolor(RED);
	settextstyle(15, 0, "����");//�������弰��С
	outtextxy(610, 165, SP);
	
	char n[20] = "";
	sprintf(n, "���ȣ�:%d ", Sn.n+1);
	settextcolor(RED);
	settextstyle(15, 0, "����");//�������弰��С
	outtextxy(610, 190, n);

	char S[20] = "";
	sprintf(S, "�÷֣�:%d ", Score);
	settextcolor(RED);
	settextstyle(15, 0, "����");//�������弰��С
	outtextxy(610, 215, S);
	
	char H_S[20] = "";
	sprintf(H_S, "��ʷ��߷֣�%d ", Hight_Score);
	settextcolor(RED);
	settextstyle(15, 0, "����");//�������弰��С
	outtextxy(610, 240, H_S);


	////����������Ϊ��Ϸ��
	HRGN  rgn1 = CreateRectRgn(185, 65, 585, 445);
	setcliprgn(rgn1);//������185, 65, 585, 445�ľ��������ó�������Ϊ��Ϸ��
	DeleteObject(rgn1);//��Ҫռ��ϵͳ�ڴ�
	solidrectangle(185, 65, 585, 445);
	setbkcolor(WHITE);


	

}

//��ȡ��ǰ��߷�
int myHight_Score()
{
	return Hight_Score;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//����߷�д���ļ�
void Hight_Score_in()
{
	FILE *fp = fopen("Hight_Score.txt", "w");
	if (NULL != fp)
	{
		fprintf(fp, "%d", Hight_Score);
	}
	
	fclose(fp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//���ļ���ķ�������
int Hight_Score_out()
{
	int s = 0;
	FILE *fp = fopen("Hight_Score.txt","r");
	if (NULL != fp)
	{
		fscanf(fp,"%d",&s);
	}
	fclose(fp);
	return s;
}