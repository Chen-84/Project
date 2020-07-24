#include"public.h"
#include"globalFile.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
////����Ա�๦�ܺ���ʵ�ֽӿ�


//////////////////////////////////////////////
////����Ա�����˵�
void Administrator::operMenu(char* _name)
{
	WindowInit("�ձ���");
	char name[50] = "";
	
	sprintf(name, "��ӭ����Ա��%s  ��¼ ", _name);
	settextcolor(RED);
	settextstyle(20, 0, "����");//�������弰��С
	outtextxy(270, 40, name);

	setcolor(RED);//�����ı���ɫ 
	settextstyle(20, 0, "����");
	RECT rect = { 270, 100, 780, 470 };
	drawtext(_T("�����Խ������²�����\n\n��ѡ��\n\n��1��:   ����˺�\n\n��2��:   �鿴�˺�\n\n��3��:   �鿴����\n\n��4��:   ���ԤԼ\n\n��5��:   ע����¼\n\n��0��:   �˳�"), &rect, DT_WORDBREAK);
	setcolor(RED);//�����ı���ɫ 
	settextstyle(15, 0, "����");
	RECT rect1 = { 270, 390, 780, 470 };
	drawtext(_T("\n\n�밴�س�������ѡ�񡭡�"), &rect1, DT_WORDBREAK);
}

//////////////////////////////////////////////
//����˺�
int Administrator:: addperson()
{
	start:WindowInit("�ձ���");
	setcolor(RED);//�����ı���ɫ 
	settextstyle(20, 0, "����");
	RECT rect = { 270, 100, 780, 470 };
	drawtext(_T("��1��:   ���ѧ��\n\n��2��:   �����ʦ\n\n��0��:   ����"), &rect, DT_WORDBREAK);
	settextstyle(15, 0, "����");
	RECT rect1 = { 270, 180, 780, 470 };
	drawtext(_T("\n\n�밴���������ѡ�񡭡�"), &rect1, DT_WORDBREAK);
	while (!kbhit())
	{
	}

	char select[2];
	InputBox(select, 2, "������ѡ�");
	int s = (int)select[0];
	while (!(48 == s || 49 == s || 50 == s))
	{
		InputBox(select, 2, "�����������������룺");
		s = (int)select[0];
	}

	string fileName;
	char id[20];
	ofstream ofs;

	switch (s)
	{
	case 49:
	{
			  ////���ѧ��
		       WindowInit("�ձ���");
			   fileName = STUDENT_FILE;
			   InputBox(id, 20, "������ѧ��ѧ�ţ�");
			   break;
	}

	case 50:
	{
			   ////��ӽ�ʦ
			   WindowInit("�ձ���");
			   fileName = TEACHER_FILE;
			   InputBox(id, 20, "�������ʦְ���ţ�");
			   break;

	}

	case 48:
		return 0;
		break;
	}

	ofs.open(fileName,ios::out|ios::app);
	char name[20];
	char pwd[20];
	InputBox(name, 20, "�������û�����");
	InputBox(pwd, 20, "���������룺");

	ofs << id << " " << name << " " << pwd << " " << endl;

	ofs.close();
	
	WindowInit("�ձ���");
	setcolor(RED);//�����ı���ɫ 
	settextstyle(20, 0, "����");
	RECT rect2 = { 270, 100, 780, 470 };
	drawtext(_T("��ӳɹ���"), &rect2, DT_WORDBREAK);
	settextstyle(15, 0, "����");
	RECT rect3 = { 270, 100, 780, 470 };
	drawtext(_T("\n\n�밴��P�������ء���"), &rect3, DT_WORDBREAK);
	
	while (1)
	{
		int c = getch();
		if (c == 80)
			break;
	}
	char c;
	c=getchar();
	goto start;

}


//////////////////////////////////////////////
//����ѧ������
string Administrator:: initvector_s()
{
	Vstu.clear();
	Vtea.clear();
	string s_Vstu;
	ifstream ifs;
	ifs.open(STUDENT_FILE,ios::in);
	if (!ifs.is_open())
	{
		return "";
	}
	Student s;
	
	while (ifs >> s.m_id && ifs >> s.m_name && ifs >> s.m_pwd)
	{
		Vstu.push_back(s);
	}
	ifs.close();

	for (int i = 0; i < Vstu.size(); ++i)
	{
		s_Vstu += Vstu[i].m_id;
		s_Vstu += ' ';
		s_Vstu += Vstu[i].m_name;
		s_Vstu += ' ';
		s_Vstu += Vstu[i].m_pwd;
		s_Vstu += "\n\n";
	}

	ifs.close();

	return s_Vstu;
}

//////////////////////////////////////////////
//�����ʦ����
string Administrator::initvector_t()
{
	Vstu.clear();
	Vtea.clear();
	string s_Vtea;
	ifstream ifs;
	
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		return "";
	}
	Teacher t;

	while (ifs >> t.m_empid && ifs >> t.m_name && ifs >> t.m_pwd)
	{
		Vtea.push_back(t);
	}
	ifs.close();

	for (int i = 0; i < Vtea.size(); ++i)
	{
		s_Vtea += Vtea[i].m_empid;
		s_Vtea += ' ';
		s_Vtea += Vtea[i].m_name;
		s_Vtea += ' ';
		s_Vtea += Vtea[i].m_pwd;
		s_Vtea += "\n\n";
	}

	return s_Vtea;
}

//////////////////////////////////////////////
//�鿴�˺�
int Administrator::showperson()
{
start:WindowInit("�ձ���");
	
	setcolor(RED);//�����ı���ɫ 
	settextstyle(20, 0, "����");
	RECT rect = { 270, 100, 780, 470 };
	drawtext(_T("��1��:   �鿴ѧ���˺�\n\n��2��:   �鿴��ʦ�˺�\n\n��0��:   ����"), &rect, DT_WORDBREAK);
	settextstyle(15, 0, "����");
	RECT rect1 = { 270, 180, 780, 470 };
	drawtext(_T("\n\n�밴�λس�����ѡ�񡭡�"), &rect1, DT_WORDBREAK);
	while (1)
	{
		int c = getch();
		if (c == 13)
			break;
	}

	char select[2];
	InputBox(select, 2, "������ѡ�");
	int s = (int)select[0];
	while (!(48 == s || 49 == s || 50 == s))
	{
		InputBox(select, 2, "�����������������룺");
		s = (int)select[0];
	}

	string fileName;
	ofstream ofs;
	switch (s)
	{
	case 49:
	{
			   ////�鿴ѧ���˺�
			   WindowInit("�ձ���");
			   string s = initvector_s();
			   char* c_Vstu = (char*)s.c_str();
			   setcolor(RED);//�����ı���ɫ 
			   settextstyle(20, 0, "����");
			   RECT rect = { 30, 30, 780, 470 };
			   drawtext(_T("ѧ���˺���Ϣ���£�"), &rect, DT_WORDBREAK);

			   RECT rect1 = { 30, 80, 780, 470 };
			   drawtext(_T(c_Vstu), &rect1, DT_WORDBREAK);
			  
			   settextstyle(15, 0, "����");
			   RECT rect2 = { 270, 400, 780, 470 };
			   drawtext(_T("\n\n�밴��P�������ء���"), &rect2, DT_WORDBREAK);
			   while (1)
			   {
				   int c = getch();
				   if (c == 80)
					   goto start;
			   }
				   break;
	}

	case 50:
	{
			   ////�鿴��ʦ�˺�
			   WindowInit("�ձ���");
			   string s = initvector_t();
			   char* c_Vtea = (char*)s.c_str();
			   setcolor(RED);//�����ı���ɫ 
			   settextstyle(20, 0, "����");
			   RECT rect = { 30, 30, 780, 470 };
			   drawtext(_T("��ʦ�˺���Ϣ���£�"), &rect, DT_WORDBREAK);

			   RECT rect1 = { 30, 80, 780, 470 };
			   drawtext(_T(c_Vtea), &rect1, DT_WORDBREAK);

			   settextstyle(15, 0, "����");
			   RECT rect2 = { 270, 400, 780, 470 };
			   drawtext(_T("\n\n�밴��P�������ء���"), &rect2, DT_WORDBREAK);
			   while (1)
			   {
				   int c = getch();
				   if (c == 80)
					   goto start;
			   }
			   break;

	}

	case 48:
		return 0;
		break;
	}
}

//////////////////////////////////////////////
//�鿴������Ϣ
int Administrator::showcomputer()
{
	
	string s_room = getroom();
	//////��ʾ
	WindowInit("�ձ���");

	char* c_room = (char*)s_room.c_str();

	setcolor(RED);//�����ı���ɫ 
	settextstyle(20, 0, "����");
	RECT rect = { 30, 30, 780, 470 };
	drawtext(_T("������Ϣ���£�\n\n�����    �������ˣ�   ���ã��ˣ�\n\n"), &rect, DT_WORDBREAK);

	RECT rect1 = { 30, 120, 780, 470 };
	drawtext(_T(c_room), &rect1, DT_WORDBREAK);

	settextstyle(15, 0, "����");
	RECT rect2 = { 270, 400, 780, 470 };
	drawtext(_T("\n\n�밴��P�������ء���"), &rect2, DT_WORDBREAK);
	while (1)
	{
		int c = getch();
		if (c == 80)
			return 0;
	}
	return 1;
}

//////////////////////////////////////////////
//���ԤԼ��¼
int Administrator::cleanfile()
{
	ofstream ofs(ORDER_FILE,ios::trunc);
	ofs.close();

	WindowInit("�ձ���");
	setcolor(RED);//�����ı���ɫ
	settextstyle(35, 0, "����");//�������弰��С
	outtextxy(270, 130, "ԤԼ��ճɹ���");

	settextstyle(15, 0, "����");
	RECT rect2 = { 270, 180, 780, 470 };
	drawtext(_T("\n\n�밴��P�������ء���"), &rect2, DT_WORDBREAK);
	while (1)
	{
		int c = getch();
		if (c == 80)
			return 0;
	}


	return 1;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
////����Ա�˵�
int Administrator:: Administrator_menu(Administrator &ads)
{
	start:char _name[20];
	std::strcpy(_name,ads.m_name.c_str());
	ads.operMenu(_name);
	
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
			   int m = addperson();
			   if (m == 0)
				   goto start;
			   return 1;
			   break;
	}

	case 50:
	{
			   int m = showperson();
			   if (m == 0)
				   goto start;
			   return 2;
			   break;

	}

	case 51:
	{
			   int m = showcomputer();
			   if (m == 0)
				   goto start;
			 
			   return 3;
			   break;

	}
	case 52:
	{
			   int m = cleanfile();
			   if (m == 0)
				   goto start;
			   return 4;
			   break;

	}
	case 53:
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


}