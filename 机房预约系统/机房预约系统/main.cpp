#include"public.h"
#include"globalFile.h"

int main()
 {


start:Main_menu();////���˵�
	
	char select[2];
	while (1)
	{
		int c = getch();
		if (c ==13)
			break;
	}
    InputBox(select, 2, "������ѡ�");
	int s = (int)select[0];
	while (!(48 == s || 49 == s || 50 == s || 51 == s))
	{
		InputBox(select, 2, "�����������������룺");
		s = (int)select[0];
	}
	switch(s)
	{
	case 49:
	{
			   int s = LoginIn(STUDENT_FILE, 1);
			   if (s == 1)
				   goto start;
			   break;
	}
		
	case 50:
	{
			   bool s = LoginIn(TEACHER_FILE, 2);
			   if (s == 1)
				   goto start;
			   break;

	}

	case 51:
	{
			   bool s = LoginIn(ADMIN_FILE, 3);
			   if (s == 1)
				   goto start;
			   break;

	}
		
	case 48:
		exit(0);
		break;
	}
	return 0;
}













//
//int main()
//{
//	IMAGE img;//������� ���ͼƬ
//	loadimage(&img, "1.jpg", 1000, 800);//����ͼƬ
//	initgraph(800, 480);//��ʼ��һ��800*480�Ĵ���
//	putimage(0, 0, &img);//��ͼƬ��Ϊ����
//	setbkmode(TRANSPARENT);//�����ı��������Ϊ͸��
//
//	setcolor(BLACK);//�����ı���ɫ
//	settextstyle(45, 0, "����");//�������弰��С
//	outtextxy(350,120,"xiaomu");
//
//	char ch[20];
//	InputBox(ch, 20, "������ѡ�");
//	
//
//	
//	getchar();
//	return 0;
//}