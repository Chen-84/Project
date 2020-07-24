#include"public.h"
#include"globalFile.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
////����ʵ�ֽӿ�

///////////////////////////////////////////////////////////
////��ʼ������
void WindowInit(string _s)
{
	IMAGE img;//������� ���ͼƬ
	int s=0;
	char* str = new char[_s.length() + 1];
	std::strcpy(str, _s.c_str());
	if (!(strcmp(str, "������")))
	{s = 1;}
	if (!(strcmp(str, "�ձ���")))
	{s = 2;}
	switch (s)
	{
	case 1:
		loadimage(&img, "������.jpg", 800, 480);//����ͼƬ
		break;
	case 2:
		loadimage(&img, "�ձ���.jpg", 800, 480);//����ͼƬ
		break;

	default:
		break;
	}
	initgraph(800, 480);//��ʼ��һ��800*480�Ĵ���
	putimage(0, 0, &img);//��ͼƬ��Ϊ����
	setbkmode(TRANSPARENT);//�����ı��������Ϊ͸��
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
////����

///////////////////////////////////
////���˵�
void Main_menu()
{
	string s = "������";
	WindowInit(s);
	setcolor(RED);//�����ı���ɫ
	settextstyle(35, 0, "����");//�������弰��С
	outtextxy(170, 130, "��ӭ����xiaomu����ԤԼϵͳ");

	setcolor(RED);//�����ı���ɫ 
	settextstyle(20, 0, "����");
	RECT rect = { 290, 190, 780, 470 };
	drawtext(_T("��ѡ��\n\n��1��:   ѧ    ��\n\n��2��:   ��    ʦ\n\n��3��:   �� �� Ա\n\n��0��:   �˳���Ϸ"), &rect, DT_WORDBREAK);
	setcolor(RED);//�����ı���ɫ 
	settextstyle(15, 0, "����");
	RECT rect1 = { 300, 370, 780, 470 };
	drawtext(_T("\n\n�밴�س�������ѡ�񡭡�"), &rect1, DT_WORDBREAK);
	
}

///////////////////////////////////
////��֤ʧ�ܽ���
void Login_failed_menu()
{
	WindowInit("�ձ���");
	setcolor(RED);//�����ı���ɫ
	settextstyle(35, 0, "����");//�������弰��С
	outtextxy(170, 130, "��¼ʧ�ܣ��û������ڣ�");
	
	
}


////���ַ���ת��Ϊint��
int c_s(char*  id)
{
	int i = 0;
	int s = 0;
	while (id[i] != '\0')
	{
		s = s * 10 + id[i] - '0';
		++i;
	}
	return s;
}


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
////��¼

////ѧ������ʦ��¼��֤
int LoginIn_Verification(ifstream* ifs, char* id, char *name, char *pwd)
{
	char fid[20];
	char fname[20] ;
	char fpwd[20];
	while (*ifs >> fid && *ifs >> fname && *ifs >> fpwd)
	{	
		while (!strcmp(id, fid) && !strcmp(name, fname))//��ź��û������
		{
			while (strcmp(pwd, fpwd))//���벻��ȣ����������ʱ����ѭ����
			{
				InputBox(pwd, 20, "��������������������루��Q�˳�����");
				char a[2] = { 'Q', '\0' };
				if (!strcmp(pwd, a))
					return 1;
				else if (!strcmp(pwd, fpwd))
				{
					break;
				}
			}
			return 0;
		}	
	}

	Login_failed_menu();//��¼ʧ�ܽ���
	while (!kbhit())//�ް������£�����ѭ��
	{
	}
	return 1;

}

////����Ա��¼��֤
int LoginIn_Administrator(ifstream* ifs, char *name, char *pwd)
{
	char fname[20];
	char fpwd[20];
	while ( *ifs >> fname && *ifs >> fpwd)
	{
		while (!strcmp(name, fname))//�û������
		{
			while (strcmp(pwd, fpwd))//���벻��ȣ����������ʱ����ѭ����
			{
				InputBox(pwd, 20, "��������������������루��Q�˳�����");
				char a[2] = { 'Q', '\0' };
				if (!strcmp(pwd, a))
					return 1;
				else if (!strcmp(pwd, fpwd))
				{
					break;
				}

			}
			return 0;
		}
	}
	if (strcmp(name, fname))//�û�������
	{
		Login_failed_menu();//��¼ʧ�ܽ���
		while (!kbhit())//�ް������£�����ѭ��
		{
		}
		return 1;
	}
}


//��¼����������ΪҪ�������ļ�����ݡ�type: 1 ѧ��    2 ��ʦ   3����Ա 
int LoginIn(string fileName, int type)
{
	WindowInit("�ձ���");
	Identity *person = nullptr;
	ifstream ifs;
	ifs.open(fileName,ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		ifs.close();
		return false;
	}

	char id[20];
	char name[20];
	char pwd[20];

	/*string name;
	string pwd;*/

	if (1 == type)
	{
		InputBox(id, 20, "������ѧ��ѧ�ţ�");
	}
	else if (2 == type)
	{
		InputBox(id, 20, "�������ʦְ���ţ�");
	}


	InputBox(name, 20, "�������û�����");
    InputBox(pwd, 20, "���������룺");
	int s;
	if (1 == type)
	{
		////ѧ����֤
		s = LoginIn_Verification(&ifs, id, name, pwd);
		if (!s)
		{
			////ѧ������ʵ��
			Student* st;
			st = new Student(id,name, pwd);
			int m = (*st).Student_menu(*st);
		    if (m == 0)
				s = 1;
		}
		
	}
	else if (2 == type)
	{
		////��ʦ��֤
		s = LoginIn_Verification(&ifs, id, name, pwd); 
		if (!s)
		{
			////��ʦ����ʵ��
			Teacher* t;
			t = new Teacher(id, name, pwd);
			int m = (*t).Teacher_menu(*t);
			if (m == 0)
				s = 1;
		}
		
		
	}
	else if (3 == type)
	{
		////����Ա��֤
		

		s = LoginIn_Administrator(&ifs, name, pwd);
		if (!s)
		{
			////����Ա����ʵ��
			Administrator* ads;
			ads = new Administrator(name, pwd);
			int m = (*ads).Administrator_menu(*ads);
			if (m == 5)
				delete ads;
			else if (m == 0)
				s = 1;

		}
		
	}
	//setcolor(RED);//�����ı���ɫ
	//settextstyle(35, 0, "����");//�������弰��С
	//outtextxy(170, 130, "��¼��֤ʧ��");
	//system("pause");
	return s;
}


////////////////////////////////////////////////////////////////////////////////////////
////��ȡ������Ϣ��ת��
string getroom()
{
	///////��ʼ��
	room r;
	ifstream ifs;
	vector<room> Vr;
	string s;

	ifs.open(COMPUTER_FILE, ios::in);
	if (!ifs.is_open())
	{
		return 0;
	}

	while (ifs >> r.room_name && ifs >> r.count&& ifs >> r.Used_count)
	{
		Vr.push_back(r);
	}
	ifs.close();

	for (int i = 0; i < Vr.size(); ++i)
	{
		s += Vr[i].room_name;
		s += "            ";
		s += Vr[i].count;
		s += "            ";
		s += Vr[i].Used_count;
		s += "\n\n";
	}
	return s;
}