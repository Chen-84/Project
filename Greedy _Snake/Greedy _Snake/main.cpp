#include"Greedy _Snake.h"

static int speed = 0;
int ch;//����
int flag=0;//ʳ��״̬���Ƿ񱻳�,0�������ˣ�
int fg = 1;



int main()
{

Loop:Load_music();
	Start_interface();//��ʼ����
	int s;
	while (1)//ֻ�е�������Ч�����Ž�����һ�����������ڵ�ǰ����
	{
		s = getch();
		if (s == 106 || s == 107)
			s -= 32;
		if (s == 74 || s == 75 || s == 27)
			break;
	}

	switch (s)
	{
	case 74:
	{

		   CK:GameInIt();
			   int sh = Hight_Score_out();
			   while (1)
			   {
			
				   while (!kbhit())//���û�а��¼��̣������ѭ��
				   {
					   if (0 == flag)//��ʾʳ�ﱻ���ˣ�������ʳ������
					   {
						   CreateFood();
					   }
					   DrawFood();
					   flag = eatFood();
					   SnakeMove();//�ƶ�

					   fg = SnakeStatus(); //�ж��Ƿ������Ϸ
					   if (0 == fg)
					   while (1)
					   {
						   Game_over(sh);//��������ҳ��
						   int sh = Hight_Score_out();
						   int Hight_Score = myHight_Score();
						   if (Hight_Score > sh)//�ж��Ƿ���Ҫ�����ļ��е���߷�
						   {
							   Hight_Score_in();
						   }
						   while (1)
						   {
							   int c = getch();
							   if (c == 80 || c == 112)//�����p����P,�����¿�ʼ
								   goto CK;
							   if (c == 27)
								   goto Loop;
						   }
					   }
					   speed = myspeed();
    				   /*for (int i = 0; i <= speed * 40; i++)
					   {
						   Sleep(1);
					   }*/

					   ShowStatus_bar();
					  // cleardevice(); //ˢ����Ļ

				   }
				   //�˳�ѭ����ʾ�а��¼��̣��жϰ��µ���ʲô��
				   ch = getch();
				   if (ch == 27)//�����Esc,���˳���Ϸ
					   goto Loop;
				   else if (ch == 80 || ch == 112)//�����p����P,�����¿�ʼ
					   goto CK;

				   else if (ch == 32)//����ǿո�,�������ѭ������ʾ��ͣ
				   while (1)
				   {
					   int c = getch();
					   if (c == 32)//����ٴΰ��¿ո�,���˳�ѭ������ʾ������Ϸ
						   break;
				   }
				   else if (ch == 87 || ch == 119 || ch == 83 || ch == 115)
				   {
					   Changespeed(ch);
				   }
				   else 
				   {
					   Changch(ch);//���·�������ı䷽��
				   }

			   }
	}
		break;

	case 75:
		Description_interface();//˵������
		int ch;
		while (1)
		{
			ch = getch();
			if (ch == 27)
				goto Loop;
		}

		getchar();
		break;
	case 27:
		exit(0);
		break;
	}

	return 0;
}









//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
////ͼ�ν������÷�

//int main()
//{
//	
//	//��ʼ��һ��640*480�Ĵ��ڣ����Ͻ�������ԭ�㣬����Ϊx�ᣬ����Ϊy��
//	initgraph(640, 480);//  init(��ʼ��)   graph(ͼ��) 
//	//rectangle(320,240,500,400);//�������м俪ʼ����һ��500*400�ľ���
//	//circle(320,240,200);//���м仭һ���뾶Ϊ200��Բ��
//	////ͨ�����ݲ���(�ı�����ĸı䷽ʽ)����ͼ�γ���һЩ����Ч��
//	int x = 0, y = 50,speed=0;
//	while (1)
//	{
//		
//		circle(320, y, 50);
//	    //circle(x, y, 50);
//		Sleep(100);
//		y += speed++;
//		if (y<50 || y>430)
//		{
//			speed = -speed;
//		}
//		cleardevice();//system("cls");
//	}
//	getchar();
//	return 0;
//}

