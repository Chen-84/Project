#pragma once
class QQMessage
{
public:
	QQMessage();
	~QQMessage();
	

	//Ϊ�����дһ�����
	static QQMessage *Instance()
	{
		static QQMessage object;//�������󲢷���
		return &object;
	}

	//Ϊ���ܺ���дһ�����,��*msg����Ҫ���͵���Ϣ
	void start(const wchar_t *msg);


private:
	//����һ���߳�
	static unsigned int WINAPI RunThredProc(void* parm);

	//���͵�����
	void SendAll();

	//ģ�ⰴ��
	void PreesKey(BYTE vkey);

	//������Ϣ
	void SendMsg();

	//��Ҫ����Ϣ����
	void AaaToClipBoard();

private:
	CString m_msg;

};

