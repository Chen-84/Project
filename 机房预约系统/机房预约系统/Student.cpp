#include"public.h"
#include"globalFile.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
////ѧ���๦�ܺ���ʵ�ֽӿ�

order odr;

////�вι���
Student::Student(string id, string name, string pwd)
{
	m_id = id;
	m_name = name;
	m_pwd = pwd;

	//��ȡ������Ϣ
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	room r;
	while (ifs >> r.room_name&&ifs >> r.count&&ifs >> r.Used_count)
	{
		Vr.push_back(r);
	}

	ifs.close();

}

//////////////////////////////////////////////
//��ʾ������Ϣ
void Student::showcomputer()
{
	string s_room = getroom();
	//////��ʾ
	WindowInit("�ձ���");

	char* c_room = (char*)s_room.c_str();

	setcolor(RED);//�����ı���ɫ 
	settextstyle(30, 0, "����");
	RECT rect = { 270, 30, 780, 470 };
	drawtext(_T("����ѡ�����"), &rect, DT_WORDBREAK);

	settextstyle(20, 0, "����");
	RECT rect1 = { 30, 70, 780, 470 };
	drawtext(_T("������Ϣ���£�\n\n�����    �������ˣ�   ���ã��ˣ�\n\n"), &rect1, DT_WORDBREAK);

	RECT rect2 = { 30, 160, 780, 470 };
	drawtext(_T(c_room), &rect2, DT_WORDBREAK);

	settextstyle(15, 0, "����");
	RECT rect3 = { 30, 240, 780, 470 };
	drawtext(_T("\n\n�밴�س���������ѡ�񡭡�"), &rect3, DT_WORDBREAK);
	
}

//////////////////////////////////////////////
//д��ԤԼ״̬
void order::Writeorder()
{
	/////д��ԤԼ�ļ���
	ofstream ofs(ORDER_FILE, ios::app);
	ofs << _id << " " << _name << " ";
	ofs << _week << " " << _time << " ";
	ofs << _roomid << " " << _state << endl;//1���������

	ofs.close();
}



//////////////////////////////////////////////
//����ԤԼ״̬    flas==1,ֻ���Լ�����Ϣ  flas==2,��ȫ����Ϣ
string order::Readorder(int flas, string s_id)
{
	string outodr;
	ifstream ifs;
	vector<order> Vo;

	ifs.open(ORDER_FILE, ios::in);
	if (!ifs.is_open())
	{
		return 0;
	}
	if (flas == 1)
	{
		while (ifs >> odr._id && ifs >> odr._name && ifs >> odr._week
			&& ifs >> odr._time && ifs >> odr._roomid && ifs >> odr._state)
		{
			if (odr._id == s_id)
			{
				if (odr._state[0] == '0')
					odr._state = "ԤԼʧ��";
				else if (odr._state[0] == '1')
					odr._state = "ԤԼ��";
				else
					odr._state = "ԤԼ�ɹ�";
				
				Vo.push_back(odr);
				
			}
				
		}

		ifs.close();
	}
	else if (flas==2)
	{
		while (ifs >> odr._id && ifs >> odr._name && ifs >> odr._week
			&& ifs >> odr._time && ifs >> odr._roomid && ifs >> odr._state)
		{
			if (odr._state[0] == '0')
				odr._state = "ԤԼʧ��";
			else if (odr._state[0] == '1')
				odr._state = "ԤԼ��";
			else
				odr._state = "ԤԼ�ɹ�";
				Vo.push_back(odr);
				odr.count++;
		}
		ifs.close();
	}


	for (int i = 0; i < Vo.size(); ++i)
	{

		char m[2];
		itoa(i+1, m, 10);
		outodr += m;
		outodr += "      ";
		outodr += Vo[i]._id;
		outodr += "      ";
		outodr += Vo[i]._name;
		outodr += "      ";
		outodr += Vo[i]._week;
		outodr += "      ";
		outodr += Vo[i]._time;
		outodr += "      ";
		outodr += Vo[i]._roomid;
		outodr += "      ";
		outodr += Vo[i]._state;
		outodr += "\n\n";

	}

	return outodr;

}



//////////////////////////////////////////////
////ѧ�������˵�
void Student::operMenu(char* _name)
{
	WindowInit("�ձ���");
	char name[50] = "";

	sprintf(name, "��ӭѧ����%s  ��¼ ", _name);
	settextcolor(RED);
	settextstyle(20, 0, "����");//�������弰��С
	outtextxy(270, 40, name);

	setcolor(RED);//�����ı���ɫ 
	settextstyle(20, 0, "����");
	RECT rect = { 270, 100, 780, 470 };
	drawtext(_T("�����Խ������²�����\n\n��ѡ��\n\n��1��:   ����ԤԼ\n\n��2��:   �鿴�ҵ�ԤԼ\n\n��3��:   �鿴����ԤԼ\n\n��4��:   ע����¼\n\n��0��:   �˳�"), &rect, DT_WORDBREAK);
	setcolor(RED);//�����ı���ɫ 
	settextstyle(15, 0, "����");
	RECT rect1 = { 270, 390, 780, 470 };
	drawtext(_T("\n\n�밴�س�������ѡ�񡭡�"), &rect1, DT_WORDBREAK);

}



//////////////////////////////////////////////
//////����ԤԼ	
int Student:: applyorder()
{

	WindowInit("�ձ���");
	char week[20];
	char time[20];
	char room[2];

	InputBox(week, 20, "���������ڣ���һ ~ ���壩��");

	while (strcmp(week, "��һ") && strcmp(week, "�ܶ�") && strcmp(week, "����") && strcmp(week, "����") && strcmp(week, "����") )
	{
		InputBox(week, 20, "�����������������루��һ ~ ���壩��");
	}

	InputBox(time, 20, "������ʱ�� ����������磩��");

	while (strcmp(time, "����") && strcmp(time, "����"))
	{
		InputBox(time, 20, "������������������ ����������磩��");
	}

	showcomputer();

	while (1)
	{
		int c = getch();
		if (c == 13)
			break;
	}

	InputBox(room, 2, "�����뷿��ţ�1~3����");

	while (strcmp(room, "1") && strcmp(room, "2") && strcmp(room, "3"))
	{
		InputBox(room, 2, "������������������ ��1~3����");
	}

	WindowInit("�ձ���");
	setcolor(RED);//�����ı���ɫ
	settextstyle(35, 0, "����");//�������弰��С
	outtextxy(170, 130, "ԤԼ�ɹ����ȴ�����У�");
	settextstyle(15, 0, "����");
	outtextxy(270, 190, "�밴��P���˳�");

	/////д��ԤԼ�ļ���
	ofstream ofs(ORDER_FILE, ios::app);

	order or(m_id, m_name, week, time, room, "1");

	or.Writeorder();

	while (1)
	{
		int c = getch();
		if (c == 80)
			break;
	}

	return 0;
}

//////////////////////////////////////////////
//�鿴�ҵ�ԤԼ
int Student::showmyorder()
{
	string s_order = order::Readorder(1,m_id);
	//////��ʾ
	WindowInit("�ձ���");

	char* c_order = (char*)s_order.c_str();

	setcolor(RED);//�����ı���ɫ 
	settextstyle(30, 0, "����");
	RECT rect = { 270, 30, 780, 470 };
	drawtext(_T("�ҵ�ԤԼ��Ϣ"), &rect, DT_WORDBREAK);

	settextstyle(20, 0, "����");
	RECT rect1 = { 30, 70, 780, 470 };
	drawtext(_T("ԤԼ��Ϣ���£�\n\n���  ѧ��   ����      ����      ʱ��    �����   ԤԼ״̬\n\n"), &rect1, DT_WORDBREAK);

	RECT rect2 = { 30, 160, 780, 470 };
	drawtext(_T(c_order), &rect2, DT_WORDBREAK);

	settextstyle(15, 0, "����");
	RECT rect3 = { 30, 390, 780, 470 };
	drawtext(_T("\n\n�밴��P�������ء���"), &rect3, DT_WORDBREAK);

	while (1)
	{
		int c = getch();
		if (c == 80)
			return 0;
	}

}




//////////////////////////////////////////////
//�鿴����ԤԼ
int Student::showallorder()
{
	string s_order = order::Readorder(2,"");
	//////��ʾ
	WindowInit("�ձ���");

	char* c_order = (char*)s_order.c_str();

	setcolor(RED);//�����ı���ɫ 
	settextstyle(30, 0, "����");
	RECT rect = { 270, 30, 780, 470 };
	drawtext(_T("����ԤԼ��Ϣ"), &rect, DT_WORDBREAK);

	settextstyle(20, 0, "����");
	RECT rect1 = { 30, 70, 780, 470 };
	drawtext(_T("ԤԼ��Ϣ���£�\n\n���  ѧ��   ����      ����      ʱ��    �����   ԤԼ״̬\n\n"), &rect1, DT_WORDBREAK);

	RECT rect2 = { 30, 160, 780, 470 };
	drawtext(_T(c_order), &rect2, DT_WORDBREAK);

	settextstyle(15, 0, "����");
	RECT rect3 = { 30, 390, 780, 470 };
	drawtext(_T("\n\n�밴��P�������ء���"), &rect3, DT_WORDBREAK);

	while (1)
	{
		int c = getch();
		if (c == 80)
			return 0;
	}

}

//////////////////////////////////////////////
//ȡ��ԤԼ
int Student::cancelorder()
{
	return 0;
}





/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
////ѧ���˵�
int Student::Student_menu(Student &st)
{
start:char _name[20];
	WindowInit("�ձ���");
	std::strcpy(_name, st.m_name.c_str());
	st.operMenu(_name);

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
			   int m = applyorder();
			   if (m == 0)
				   goto start;
			   return 1;
			   break;
	}

	case 50:
	{
			   int m = showmyorder();
			   if (m == 0)
				   goto start;
			   return 2;
			   break;

	}

	case 51:
	{
			   int m = showallorder();
			   if (m == 0)
				   goto start;

			   return 3;
			   break;

	}
	case 52:
	{
			   WindowInit("�ձ���");
			   setcolor(RED);//�����ı���ɫ 
			   settextstyle(20, 0, "����");
			   RECT rect = { 270, 120, 780, 470 };
			   drawtext(_T("ע���ɹ���"), &rect, DT_WORDBREAK);
			   settextstyle(15, 0, "����");
			   RECT rect1 = { 270, 150, 780, 470 };
			   drawtext(_T("\n\n�밴����������˳�����"), &rect1, DT_WORDBREAK);
			   while (!kbhit())
			   {
			   }
			   return 0;
			   break;
	}
	

	case 48:
		return 0;
		break;
	}

	return 1;
}

