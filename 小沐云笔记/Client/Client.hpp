#ifndef _CLIENT_H_
#define _CLIENT_H_ 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////ģ��ӿ�-�ͻ���
#include<iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include<boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include "httplib.h"
using namespace std;

#define STORE_FILE "./C_filelist.text"
#define LISTEN_DIR "./backup/"
#define SERVER_IP   "192.168.80.100"
#define SERVER_PORT  9090


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////������

///////////////////////////////////////////////////////////////////
////�ļ�����
class FileUtil
{
public:
	static bool Read(const std::string &name, std::string *body);//���ļ��ж�ȡ����
	static bool Write(const std::string &name, const std::string &body);//���ļ���д������
};



///////////////////////////////////////////////////////////////////
////ѹ������
class CompressUtil
{
public:
	static bool Compress(const std::string &src, const std::string &dst);//ѹ����Դ�ļ����ƣ�ѹ�������ƣ�
	static bool UnCompress(const std::string &src, const std::string &dst); // ��ѹ����ѹ�������ƣ�Դ�ļ����ƣ�
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////���ݹ���ģ��
class DataManager{
public:
	DataManager(const string &filename) :_store_file(filename){}
	bool Insert(const string &key, const string &val);//�����ļ��б���Ϣ
	bool GetEtag(const string &key, string*val);//ͨ���ļ�����ȡetag��Ϣ
	bool lnitLoad();///��ʼ������ԭ������
	bool Storage();//ÿ�θ�������֮�󣬳־û��洢

private:
	string _store_file; //���ݳ־û��洢·��/�ļ���
	unordered_map<string, string> _backup_list;//�ļ��б���Ϣ
};




////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////Ŀ¼���ģ��
class CloudClient{
public:
	CloudClient(const string &filename, const string &store_file, const string srv_ip, uint16_t srv_port)
		:_listen_dir(filename), data_manage(STORE_FILE), _srv_ip(srv_ip), _srv_port(srv_port){}

	bool GetBackUpFileList(vector<string> *list);//��ȡ��Ҫ���ݵ��ļ��б�---���Ŀ¼�������ļ��������ȡetagȻ����бȶ�
	bool GetEtag(const string &pathname, string *etag);//����һ���ļ���etag��Ϣ
	bool Start();//���������ļ���������
private:
	string _listen_dir; //���ģ��Ҫ��ص�Ŀ¼����   
	DataManager data_manage;
	string _srv_ip;
	uint16_t _srv_port;
};




#endif /*_CLIENT_H_*/

