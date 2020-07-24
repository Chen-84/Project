#ifndef _PUBLIC_H
#define _PUBLIC_H

#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<windows.h>//�������
#include<time.h>//ʳ�����
#include<conio.h>//�������
#include<graphics.h>//ͼ�ν����
//#include<mmsystem.h>//��ý���豸�ӿ�
#pragma comment(lib,"Winmm.lib")
using namespace std;



/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
////�ඨ��



/////////////////////////////////////////////////////////////////////////////////////////////////////
////������
class room
{
public:
	string room_name;
	string count;
	string Used_count;

};



/////////////////////////////////////////////////////////////////////////////////////////////////////
////ԤԼ��Ϣ��
class order
{
public:
	order()
	{}
	order(string id, string name, string week, string time, string roomid, string state)
	{
		_id = id;
		_name = name;
		_week = week;
		_time = time;
		_roomid = roomid;
		_state = state;
	}
public:
	void Writeorder();//д��ԤԼ״̬
	static string order::Readorder(int flas, string s_id);//����ԤԼ״̬    flas==1,ֻ���Լ�����Ϣ  flas==2,��ȫ����Ϣ
	string _id;
	string _name;
	string _week;
	string _time;
	string _roomid;
	string _state;//ԤԼ״̬ 0��ԤԼʧ��     1��ԤԼ��   2��ԤԼ�ɹ�
	int count=0;

};



/////////////////////////////////////////////////////////////////////////////////////////////////////
////��ݳ�����
class Identity
{
public:
	////���캯��
	Identity()
	{}
	Identity(string name, string pwd) :m_name(name), m_pwd(pwd)
	{}

	////�����˵�
	virtual void  operMenu(char* _name) = 0;

	string m_name;//�û���
	string m_pwd; //����
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
////ѧ����
class Student: public Identity
{
public:
	////���캯��
	Student()
	{}
	Student(string id, string name, string pwd);
	

public:

	

	////�����˵�
	int Student_menu(Student &st);//�����˵�
	virtual void  operMenu(char* _name);;
public:
	////���ܺ��������ӿ�
	void showcomputer();
	int applyorder();//����ԤԼ
	int showmyorder();//�鿴�ҵ�ԤԼ
	static int showallorder();//�鿴����ԤԼ
	int cancelorder();//ȡ��ԤԼ
	vector<room> Vr;
	string m_id;//ѧ��
	
};


/////////////////////////////////////////////////////////////////////////////////////////////////////
////��ʦ��
class Teacher:public Identity
{
public:
	////���캯��
	Teacher()
	{}
	Teacher(string empid, string name, string pwd) :Identity(name, pwd)
	{
		m_empid = empid;
	}

public:
	////�����˵�
	int Teacher_menu(Teacher &t);//�����˵�
	virtual void  operMenu(char* _name);
	void Modifycomputer(int n);//�޸Ļ�����Ϣ
public:
	////���ܺ��������ӿ�
	int validorder();//���ԤԼ
	int  Marking();//����
	string m_empid;//��ʦְ�����
};


/////////////////////////////////////////////////////////////////////////////////////////////////////
////����Ա��
class Administrator:public Identity
{
public:
	////���캯��
	Administrator()
	{}
	Administrator(string name, string pwd) :Identity(name, pwd)
	{
		
	}

public:
	////�����˵�
	int  Administrator_menu(Administrator &ads);//�����˵�
	virtual void  operMenu(char* _name);//��ʾ�˵�����
public:

	////���ܺ��������ӿ�
	int addperson();//����˺�
	int showperson();//�鿴�˺�
	static int showcomputer();//�鿴������Ϣ
	int cleanfile();//���ԤԼ��¼


	string initvector_s();//����ѧ������
	string initvector_t();//�����ʦ����
	vector<Student> Vstu;
	vector<Teacher> Vtea;
	
};




/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
////���������ӿ�
void WindowInit(string _s);////��ʼ������
void Login_failed_menu(int s); //��֤ʧ�ܽ���
void Main_menu();//���˵�
string getroom();


void printStudent(Student& s);//��ʾ��ʦ��Ϣ
void printTeacher(Teacher& t);//��ʾ��ʦ��Ϣ


int LoginIn(string filename, int type);//��¼����������ΪҪ�������ļ�����ݡ�type: 1 ѧ��    2 ��ʦ   3����Ա    
int LoginIn_Verification(ifstream* ifs, char *name, char *pwd);////ѧ������ʦ��¼��֤







#endif  /*_PUBLIC_H*/