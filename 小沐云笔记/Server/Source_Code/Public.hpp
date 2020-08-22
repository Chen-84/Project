#ifndef _PUBLIC_H_
#define _PUBLIC_H_

#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <pthread.h>
#include <thread>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <zlib.h>
#include <time.h>
#include "httplib.h"
using namespace std;


#define HOT_EVENT 20  //�ж��Ƿ����ȵ��ļ���ʱ���׼
#define TEST_TIME 30  //�ж��Ƿ����ȵ��ļ���ʱ����
#define FILE_DIR       "../file/"      //�ļ�����Ŀ¼
#define GZFILE_DIR     "../gzfile/"    //ѹ���ļ���Ŀ¼
#define DATA_FILE      "../datafile/S_filelist.text" 

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


#endif /*_PUBLIC_H_ */
