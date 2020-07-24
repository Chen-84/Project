#include "stdafx.h"
#include "QQMessage.h"
//ʵ��Ⱥ������

QQMessage::QQMessage()
{
}


QQMessage::~QQMessage()
{
}


////////////////////////////////////////////////////////////////////////////////////////
//Ϊ���ܺ���дһ�����,��*msg����Ҫ���͵���Ϣ
void QQMessage::start(const wchar_t *msg)
{
	//������Ҫ���͵���Ϣ
	m_msg = CString(msg);

	//����һ���߳�
	_beginthreadex(NULL,0,QQMessage::RunThredProc,NULL,0,NULL);
}



////////////////////////////////////////////////////////////////////////////////////////
//����һ���߳�
unsigned int QQMessage::RunThredProc(void* parm)
{
	QQMessage::Instance()->SendAll();   //������������
	return 0;
}


////////////////////////////////////////////////////////////////////////////////////////
//���͵�����
void QQMessage:: SendAll()
{
	//����Ϣճ����ճ����
	AaaToClipBoard();
	
    int fals = 1;
	//1.�ҵ�����   FindWindow(L"���ڵ�������",L"����");
	HWND qqhend = FindWindow(L"TXGuiFoundation", L"QQ");

	//2.�ҵ���qq�����ǲ������������ǰ�� 
	HWND fronthwnd = GetForegroundWindow();
	if (qqhend != fronthwnd)  //�ж�qq�����ǲ������������ǰ�� 
	{
		if (!SetForegroundWindow(qqhend))//���������ǰ�� ����Ҫ��qq���ڷŵ���ǰ�� 
		{
			MessageBox(NULL, L"�Ҳ���QQ����", NULL, NULL);
		}
	}

	int group = 1;
	
	//ģ�ⰴ��Tab Tab
	PreesKey(VK_TAB);
	PreesKey(VK_TAB);

	PreesKey(VK_DOWN);
	//ģ�ⰴ���س�	
	PreesKey(VK_RETURN);

	while (1)
	{
		//ģ�ⰴ��Down
		PreesKey(VK_DOWN);
		//ģ�ⰴ���س�	
		PreesKey(VK_RETURN);
		//ģ�ⰴ��Down
		PreesKey(VK_DOWN);
		//ģ�ⰴ���س�	
		PreesKey(VK_RETURN);

		HWND curhwnd = GetForegroundWindow();
		if (curhwnd==qqhend)
		{
			MessageBox(NULL, L"�ѷ�����ϣ�", NULL, NULL);
			break;
		}

	    ///////////////////////////////////////////////////////////////
		//�������Ѿ�����ϵ����

		////������Ϣ
		SendMsg();
		//ģ�ⰴ��Tab Tab
		PreesKey(VK_TAB);
		PreesKey(VK_TAB);
	}

}


////////////////////////////////////////////////////////////////////////////////////////
//ģ�ⰴ��
void QQMessage:: PreesKey(BYTE vkey)
{
	keybd_event(vkey, 0, 0, 0);  //ģ��һ������  ����
	Sleep(100);
	keybd_event(vkey, 0, KEYEVENTF_KEYUP, 0);  //ģ��һ������  ����
	Sleep(100);
}


////////////////////////////////////////////////////////////////////////////////////////
//������Ϣ
void QQMessage:: SendMsg()
{
	/////////////////////////////////////
	//Ctrl+V

	//ģ��Ctrl ����
	keybd_event(VK_CONTROL, 0, 0, 0); 
	Sleep(100);
	//ģ��V ����
	keybd_event(0x56, 0, 0, 0);
	Sleep(100);

	//ģ��V ����
	keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
	Sleep(100);
	//ģ��Ctrl����
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
	Sleep(100);

	/////////////////////////////////////////////
	//�س�������  
	PreesKey(VK_RETURN);

	//ģ��ESC�˳�
	PreesKey(VK_ESCAPE);
}


////////////////////////////////////////////////////////////////////////////////////////
//��Ҫ����Ϣ����
void QQMessage:: AaaToClipBoard()
{
	int memLenth = m_msg.GetLength()*sizeof(wchar_t)+2;
	HANDLE hGlobalMenory = GlobalAlloc(GHND,memLenth);
	void* memAddr = GlobalLock(hGlobalMenory);
	ZeroMemory(memAddr,memLenth);

	memcpy(memAddr,(const void*)m_msg.GetBuffer(),memLenth);

	GlobalUnlock(hGlobalMenory);

	//���������
	::OpenClipboard(NULL);
	::EmptyClipboard();
	::SetClipboardData(CF_UNICODETEXT,hGlobalMenory);
	::CloseClipboard();
}