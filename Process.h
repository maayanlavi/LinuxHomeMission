
#pragma once
#include <iostream>
#include <atomic>  
#include <csignal>
#include <memory>
#include <map>
#include <string>
#include <vector>

using namespace std;
	class CProcess
	{
	public:
		CProcess();
		int getPid (shared_ptr<map<string,string>>& processInfo);
		int getPpid (shared_ptr<map<string,string>>& processInfo);
		int getPppid (shared_ptr<map<string,string>>& processInfo);
		int getPcmd (shared_ptr<map<string,string>>& processInfo);
		int getFileName (shared_ptr<map<string,string>>& processInfo);
		int getFullPath (shared_ptr<map<string,string>>& processInfo);
		int getFileSize (shared_ptr<map<string,string>>& processInfo);
		int getVirtualMemSize (shared_ptr<map<string,string>>& processInfo);
		int getUid (shared_ptr<map<string,string>>& processInfo);
		int getNumOfFileDescriptorsOpen (shared_ptr<map<string,string>>& processInfo);

	
	private:
		int getProcFileContent(const string& iPid,
		const string &iSubFileName,
		vector<string>& oContent,  char separator = '\n');



	};
	
