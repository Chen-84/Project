#include "Client.hpp"

;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////������

///////////////////////////////////////////////////////////////////
////���ļ��ж�ȡ����

bool FileUtil::Read(const std::string &name, std::string *body)
{
	//�����ļ���
	std::ifstream fs(name, std::ios::binary);//�Զ�������ʽ��
	if (fs.is_open() == false){
		cout << "open file " << name << "failed\n";
		return false;
	}
	// boost::filesystem::file_size() ��ȡ�ļ���С
	int64_t fsize = boost::filesystem::file_size(name);
	body->resize(fsize); // ��body����ռ��������
	fs.read(&(*body)[0], fsize);
	if (fs.good() == false){
		cout << "file" << name << "read data failed!\n";
		return false;
	}
	fs.close();
	return true;
}

///////////////////////////////////////////////////////////////////
////���ļ���д������
bool FileUtil::Write(const std::string &name, const std::string &body)
{
	//����ļ��� --ofstream Ĭ�ϴ�ʱ����ļ�����
	std::ofstream ofs(name, std::ios::binary);
	if (ofs.is_open() == false){
		std::cout << "open file " << name << "failed\n";
		return false;
	}

	ofs.write(&body[0], body.size());
	if (ofs.good() == false){
		std::cout << "file" << name << "write data failed!\n";
		return false;
	}
	ofs.close();
	return true;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////���ݹ���ģ��
/////////////////////////////////////////////////////////////////////////////
////�����ļ��б���Ϣ
bool DataManager::Insert(const string &key, const string &val)
{
	_backup_list[key] = val;
	Storage();
	return true;
}


/////////////////////////////////////////////////////////////////////////////
////ͨ���ļ�����ȡetag��Ϣ
bool DataManager::GetEtag(const string &key, string*val)
{
	auto it = _backup_list.find(key);
	if (it == _backup_list.end()){
		return false;
	}
	*val = it->second;
	return true;
}


/////////////////////////////////////////////////////////////////////////////
////��ʼ������ԭ������
bool DataManager::lnitLoad()
{
	//�������ļ�����ļ�������Ϣ��ȡ����
	string body;
	if (FileUtil::Read(_store_file, &body) == false){
		return false;
	}

	//�������л��ĸ�ʽ���д���
	vector<string> list;
	boost::split(list, body, boost::is_any_of("\r\n"),
		boost::token_compress_off);//�����ݰ���/r/n���зָ�

	for (auto i : list){
		size_t pos = i.find(" ");
		if (pos == std::string::npos){
			continue;
		}
		string key = i.substr(0, pos);
		string val = i.substr(pos + 1);

		Insert(key, val);
	}
	return true;
}


/////////////////////////////////////////////////////////////////////////////
////ÿ�θ�������֮�󣬳־û��洢
bool DataManager::Storage()
{
	//�������л�
	std::stringstream tmp; //����һ��string��
	auto it = _backup_list.begin();
	for (; it != _backup_list.end(); ++it){
		tmp << it->first << " " << it->second << "\r\n";
	}

	_store_file = "C_filelist.text";
	FileUtil::Write(_store_file, tmp.str());
	return true;
	return true;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////Ŀ¼���ģ��

/////////////////////////////////////////////////////////////////////////////
////��ȡ��Ҫ���ݵ��ļ��б�---���Ŀ¼�������ļ��������ȡetagȻ����бȶ�
bool CloudClient::GetBackUpFileList(vector<string> *list)
{
	//�����Ҫ��ص�Ŀ¼�����ڣ��򴴽�
	if (boost::filesystem::exists(_listen_dir) == false){
		boost::filesystem::create_directory(_listen_dir);
	}

	//1.��ȡָ��Ŀ¼�µ������ļ�����
	boost::filesystem::directory_iterator begin(_listen_dir);
	boost::filesystem::directory_iterator end;
	for (; begin != end; ++begin){
		if (boost::filesystem::is_directory(begin->status())){
			//�����Ŀ¼���򲻽��б���
			continue;
		}
		string pathname = begin->path().string();//��ȡ�ļ�·����+�ļ���
		string name = begin->path().filename().string();//��ȡ�ļ���
		string cur_etag;

		//2.������㵱ǰ��etagֵ
		GetEtag(pathname,&cur_etag);

		//3.��data_manage�д��ڵ�ԭ��etag���бȶ�
		string old_etag;
		data_manage.GetEtag(name,&old_etag);
		if (cur_etag != old_etag){
			list->push_back(name);
		}
	}
	return true;
}



/////////////////////////////////////////////////////////////////////////////
////����һ���ļ���etag��Ϣ(etag: �ļ���С ���ļ������һ���޸�ʱ��)
bool CloudClient::GetEtag(const string &pathname, string *etag)
{
	int64_t fsize = boost::filesystem::file_size(pathname);
	time_t mtime = boost::filesystem::last_write_time(pathname);
	*etag = to_string(fsize) + " " + to_string(mtime);
	return true;
}


/////////////////////////////////////////////////////////////////////////////
////���������ļ���������
bool CloudClient::Start()
{
	//����������Ϣ
	data_manage.lnitLoad();
	while (1)
	{
		vector<string> list;
		//��ȡ��������Ҫ���ݵ��ļ�����
		GetBackUpFileList(&list);

		for (int i = 0; i < list.size(); ++i){
			string name = list[i];
			string pathname = _listen_dir + name;

			//��ȡ�ļ�����
			string body;
			FileUtil::Read(pathname, &body);


			httplib::Client client(_srv_ip, _srv_port);

			//����Put���󣬽��б���
			string req_path = "/" + name;
			auto rsp = client.Put(req_path.c_str(), body, "application/octet-stream");//������������
			if (rsp == NULL || (rsp != NULL && rsp->status != 200)){

				//ʧ��
				cout << "backup failed!" << endl;
				continue;
			}

			//���ݳɹ������������
			cout << "backup success!" << endl;
			string etag;
			GetEtag(pathname, &etag);
			data_manage.Insert(name, etag);		
		}
		Sleep(1000);
	}
	return true;
}