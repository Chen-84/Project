#include"public.h"
#include"globalFile.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
////��ʦ�๦�ܺ���ʵ�ֽӿ�

extern order odr;


//////////////////////////////////////////////
////��ʦ�����˵�
void Teacher::operMenu(char* _name)
{
	WindowInit("�ձ���");
	char name[50] = "";

	sprintf(name, "��ӭ��ʦ��%s  ��¼ ", _name);
	settextcolor(RED);
	settextstyle(20, 0, "����");//�������弰��С
	outtextxy(270, 40, name);

	setcolor(RED);//�����ı���ɫ 
	settextstyle(20, 0, "����");
	RECT rect = { 270, 100, 780, 470 };
	drawtext(_T("�����Խ������²�����\n\n��ѡ��\n\n��1��:   �鿴����ԤԼ\n\n��2��:   ���ԤԼ\n\n��0��:   �˳�"), &rect, DT_WORDBREAK);
	setcolor(RED);//�����ı���ɫ 
	settextstyle(15, 0, "����");
	RECT rect1 = { 270, 290, 780, 470 };
	drawtext(_T("\n\n�밴�س�������ѡ�񡭡�"), &rect1, DT_WORDBREAK);
}



//////////////////////////////////////////////
//�޸Ļ�����Ϣ
void Teacher:: Modifycomputer(int n)
{
	queue<room> q;
	ifstream ifs;
	fstream ofs;
	room om;

	ifs.open(COMPUTER_FILE, ios::in);
	if (!ifs.is_open())
	{
		return;
	}

	int i = 1;
	while (ifs >> om.room_name && ifs >> om.count && ifs >> om.Used_count)
	{
		if (i != n)
		{
			q.push(om);
		}
		else
		{
			const char *r = om.Used_count.c_str();
			int a = atoi(r);
			char b[5];
			string s;
			a++;
			itoa(a, b, 10);
			int i = 0;
			while (b[i] != '\0')
			{
				s.push_back(b[i]);
				++i;
			}

			om.Used_count = s;
			q.push(om);
		}

		i++;
	}

	ifs.close();

	ofs.open(COMPUTER_FILE, ios::out | ios::trunc);
	if (!ofs.is_open())
	{
		return;
	}

	ofs.close();


	while(!q.empty())
	{
		room tmp = q.front();
		q.pop();

		/////д��ԤԼ�ļ���
		ofstream ofs(COMPUTER_FILE, ios::app);
		ofs << tmp.room_name << " " << tmp.count << " " << tmp.Used_count << endl;
		
		ofs.close();
	}

}



//////////////////////////////////////////////
//����
int Teacher:: Marking()
{

	char select[2];
	InputBox(select, 2, "������Ҫ���ĵı�ţ�");

	int s = (int)select[0]-48;



	while (s>odr.count)
	{
		InputBox(select, 2, "�����������������룺");
		s = (int)select[0]-48;
	}


	ifstream ifs;
	order or;
	order tmpr;
	fstream ofs;
	queue<order> q;
	ifs.open(ORDER_FILE, ios::in);
	if (!ifs.is_open())
	{
		return 0;
	}


	int i = 1;
	while (ifs >> or._id && ifs >> or._name && ifs >> or._week
		&& ifs >> or._time && ifs >> or._roomid && ifs >> or._state)
	{

		if (i != s)
		    q.push(or);

		else
		{
			char se[2];
			InputBox(se, 2, "��ȷ��ͨ����ѧ���������𣿣���Y or N��");

			int s = (int)se[0];

			while (!(78 == s || 110 == s || 89 == s || 121 == s))
			{
				InputBox(se, 2, "�����������������룺��Y or N��");
				int s = (int)se[0];
			}

			if (78 == s || 110 == s)
			{
				or._state = '0';
				tmpr = or;

				WindowInit("�ձ���");
				setcolor(RED);//�����ı���ɫ
				settextstyle(35, 0, "����");//�������弰��С
				outtextxy(170, 130, "�Ѿܾ�����ԤԼ��");
				settextstyle(15, 0, "����");//�������弰��С
				outtextxy(170, 170, "����P��������");
			}
			else
			{
				or._state = '2';
				tmpr = or;

				const char *c = or._roomid.c_str();
				int a = atoi(c);
				
				Modifycomputer(a);

				WindowInit("�ձ���");
				setcolor(RED);//�����ı���ɫ
				settextstyle(35, 0, "����");//�������弰��С
				outtextxy(170, 130, "��ͬ�����ԤԼ��");
				settextstyle(15, 0, "����");//�������弰��С
				outtextxy(170, 170, "����P��������");
			}
		}
		i++;
	}

	ifs.close();

	ofs.open(ORDER_FILE, ios::out | ios::trunc);
	if (!ofs.is_open())
	{
		return 0;
	}

	ofs.close();
	while (!q.empty())
	{
		order tmp = q.front();
		q.pop();

		tmp.Writeorder();
	}
	tmpr.Writeorder();


	
		while (1)
		{
			int c = getch();
			if (c == 80)
				return 0;
		}

	return 0;
}
	


//////////////////////////////////////////////
//���ԤԼ
int Teacher:: validorder()
{
	start:string s_order = order::Readorder(2, "");
	//////��ʾ
	WindowInit("�ձ���");

	char* c_order = (char*)s_order.c_str();

	setcolor(RED);//�����ı���ɫ 
	settextstyle(30, 0, "����");
	RECT rect = { 270, 30, 780, 470 };
	drawtext(_T("ԤԼ��Ϣ"), &rect, DT_WORDBREAK);

	settextstyle(20, 0, "����");
	RECT rect1 = { 30, 70, 780, 470 };
	drawtext(_T("ԤԼ��Ϣ���£�\n\n���  ѧ��   ����      ����      ʱ��    �����   ԤԼ״̬\n\n"), &rect1, DT_WORDBREAK);

	RECT rect2 = { 30, 160, 780, 470 };
	drawtext(_T(c_order), &rect2, DT_WORDBREAK);

	settextstyle(15, 0, "����");
	RECT rect3 = { 30, 390, 780, 470 };
	drawtext(_T("\n\n����P�����鿴������Ϣ\n\n���س����������ġ���"), &rect3, DT_WORDBREAK);

	while (1)
	{
		int m;
		int c = getch();
		if (c == 80)
		{
			Administrator::showcomputer();
			goto start;
		}
		else if (c == 13)
			m=Marking();
		if (m == 0)
			break;
	}
	return 0;
}




/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
////��ʦ�˵�
int Teacher::Teacher_menu(Teacher &t)
{
start:char _name[20];
	WindowInit("�ձ���");
	std::strcpy(_name, t.m_name.c_str());
	t.operMenu(_name);

	char select[2];
	while (1)
	{
		int c = getch();
		if (c == 13)
			break;
	}
	InputBox(select, 2, "������ѡ�");
	int s = (int)select[0];
	while (!(48 == s || 49 == s || 50 == s || 51 == s || 52 == s || 53 == s))
	{
		InputBox(select, 2, "�����������������룺");
		s = (int)select[0];
	}
	switch (s)
	{
	case 49:
	{
			   int m = Student::showallorder();
			   if (m == 0)
				   goto start;
			   return 1;
			   break;
	}

	case 50:
	{
			   int m =  validorder();
			   if (m == 0)
				   goto start;
			   return 2;
			   break;

	}
	
	case 48:
		return 0;
		break;
	}

	return 1;
}

