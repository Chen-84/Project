#ifndef _SERVER_H_
#define _SERVER_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////ģ��ӿڡ��������






/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////���ݹ���ģ��
class DataManager
{
public:
	DataManager(const std::string &path):_back_file(path)
    {
        pthread_rwlock_init(&_rwlock,NULL);
    }
	~DataManager()
    {
        pthread_rwlock_destroy(&_rwlock);
    }

public:
	bool Exists(const string &name);//�ж��ļ��Ƿ����
	bool IsCompress(const string &name); //�ж��ļ��Ƿ�ѹ��
	bool NonCompressed(vector<string> *list); //��ȡδѹ���ļ��б�
	bool Insert(const std:: string &src, const std::string &dst); //�����������
	bool GetAllName(vector<string> *list); //��ȡ�����ļ�����
    bool GetGzName(const string &src,string *dst); //����Դ�ļ����ƣ���ȡѹ��������
	bool Storage(); //���ݳ־û��洢
	bool InitLoad(); //���������ʱ���������ļ���Ϣ

private:
	string _back_file; // �־û�������Ϣ�洢�ļ�����
	unordered_map<string, string> _file_list; //���ݹ�������
	pthread_rwlock_t _rwlock; //ʹ�ö�д������_file_list�Ĳ���--������д����
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////���ȵ��ļ�ѹ��ģ��
class NonHotCompress
{
public:
    NonHotCompress(const std::string file_name , const std::string gz_name)
        :_file_dir(file_name),_gz_dir(gz_name){}
public:
	/*******************************************/
	/*  ѭ��ÿ��һ��ʱ�䣺
	1.��ȡδѹ���ļ��б�        2.����ж��Ƿ����ȵ��ļ�
	3.���Ƿ��ȵ��ļ�����ѹ��    4.�������� */
	/*******************************************/
	bool Start(); //����ѹ��ģ��

private:
	bool FilelsHot(const string &filename);//�ж��ļ��Ƿ���һ���ȵ��ļ�

private:
    string _file_dir; //�����ļ�Ŀ¼
	string _gz_dir;   //ѹ���ļ��Ĵ��·��
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////����ͨ��ģ��
class Server{
public:
	Server()
	{}
	~Server()
	{}

public:
	bool Start();//��ʼ�HTTP������������ҵ����
private:
	//�ļ��ϴ�����Ļص�������
	static void UpLoad(const httplib::Request &req, httplib::Response &rsp);
	//�ļ��б�����Ļص�������
	static void List(const httplib::Request &req, httplib::Response &rsp);
	//�ļ���������Ļص�������
	static void DownLoad(const httplib::Request &req, httplib::Response &rsp);

private:
	string file_dir;//�ϴ��ļ��Ĵ��·��
	httplib::Server _server;//�http�������Ķ���
};







#endif /* _SERVER_H_ */
