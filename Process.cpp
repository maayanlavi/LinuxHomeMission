#include "Process.h"
#include "Error.h"
#include <thread>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/types.h>
#include <unistd.h>
#include <sstream>
#include <filesystem>
#include <algorithm>
using namespace std;

CProcess::CProcess()
{
	
}

int CProcess::getProcFileContent(const string& iPid,
	const string &iSubFileName,
	vector<string>& oContent,  char separator)
{
	string proc = "/proc/";
	string fullProcPath = proc + iPid + iSubFileName;
	fstream file(fullProcPath, ios::in);
	string line;

	if (!file.is_open())
	{
		return ERROR_TO_OPEN_FILE;
	}
	while (getline(file, line, separator))
	{
		oContent.push_back(line);
	}

file.close();
	return SUCCESS;
}

int CProcess::getPid(shared_ptr<map<string, string>>& processInfo)
{
	pid_t pid = getpid();
	processInfo->insert(std::make_pair("pid:",to_string(pid)));	

	return SUCCESS;
}

int CProcess::getPpid(shared_ptr<map<string, string>>& processInfo)
{
	pid_t pid = getppid();
	processInfo->insert(std::make_pair("ppid:",to_string(pid)));	

	return SUCCESS;
}
int CProcess::getPppid(shared_ptr<map<string, string>>& processInfo)
{
	int result = SUCCESS;
	pid_t pid = getppid();
	vector<string> contentLines;
	result = getProcFileContent(to_string(pid), "/stat", contentLines,' ');
	if (result != SUCCESS)
	{
		return result;
	}
	if (contentLines.size() < 3)
	{
		return ERROR_MISS_PPID_IN_STAT_FILE;
	}
processInfo->insert(std::make_pair("pppid:",contentLines[3]));

	return result;
}

int CProcess::getPcmd(shared_ptr<map<string, string>>& processInfo)
{
	int result = SUCCESS;
	pid_t pid = getpid();
	vector<string> contentLines;
	string cmd;
	result = getProcFileContent(to_string(pid), "/cmdline", contentLines);
	if (result != SUCCESS)
	{
		return result;
	}
	for (auto& line : contentLines)
	{
		cmd += line;

	}
processInfo->insert(std::make_pair("process command line:",cmd));	
	return result;
}

int CProcess::getFileName(shared_ptr<map<string, string>>& processInfo)
{
		int result = SUCCESS;
		pid_t pid = getpid();
		vector<string> contentLines;
		result = getProcFileContent(to_string(pid), "/status", contentLines);
		if (result != SUCCESS)
		{
			return result;
		}
		std::string segment;
		bool nextValueIsName = false;
		for (auto& line : contentLines)
		{
			std::stringstream lineStream(line);
			while (std::getline(lineStream, segment, ':'))
			{
				
				if (nextValueIsName) 
				{
					processInfo->insert(std::make_pair("Name",segment));	
					return result;
				}
				if (segment == "Name")
				{
					nextValueIsName = true;
				}
			}

		}
		
		return ERROR_NAME_IS_MISSING;
}
int CProcess::getFullPath(shared_ptr<map<string, string>>&processInfo)
{		
		int result = SUCCESS;
		string path = get_current_dir_name();
		string fileName = processInfo->at("Name");
		remove(fileName.begin(), fileName.end(), '\t');
		string fullPath = path + "/" + fileName;
		processInfo->insert(std::make_pair("Path:",fullPath));
		return result;	
		//return ERROR_PATH_IS_MISSING;

}

int CProcess::getFileSize(shared_ptr<map<string, string>>&processInfo)
{
		int result = SUCCESS;
		pid_t pid = getpid();
		vector<string> contentLines;
		result = getProcFileContent(to_string(pid), "/status", contentLines);
		if (result != SUCCESS)
		{
			return result;
		}
		std::string segment;
		bool nextValueIsVmSize = false;
		for (auto& line : contentLines)
		{
			std::stringstream lineStream(line);
			while (std::getline(lineStream, segment, ':'))
			{
				
				if (nextValueIsVmSize) 
				{
					processInfo->insert(std::make_pair("fileSize:",segment));	
					return result;
				}
				if (segment == "VmSize")
				{
					nextValueIsVmSize = true;
				}
			}

		}
		
		return ERROR_VM_SIZE_IS_MISSING;
}

	int CProcess::getVirtualMemSize(shared_ptr<map<string, string>>&processInfo)
	{
		int result = SUCCESS;
		pid_t pid = getpid();
		vector<string> contentLines;
		result = getProcFileContent(to_string(pid), "/status", contentLines);
		if (result != SUCCESS)
		{
			return result;
		}
		std::string segment;
		bool nextValueIsVmpeak = false;
		for (auto& line : contentLines)
		{
			std::stringstream lineStream(line);
			while (std::getline(lineStream, segment, ':'))
			{
				
				if (nextValueIsVmpeak) 
				{
					processInfo->insert(std::make_pair("virtualMemorySize:",segment));	
					return result;
				}
				if (segment == "VmPeak")
				{
					nextValueIsVmpeak = true;
				}
			}

		}
		
		return ERROR_VM_PEAK_IS_MISSING;
	}

	int CProcess::getUid(shared_ptr<map<string, string>>&processInfo)
	{
		int result = SUCCESS;
		pid_t pid = getpid();
		vector<string> contentLines;
		result = getProcFileContent(to_string(pid), "/status", contentLines);
		if (result != SUCCESS)
		{
			return result;
		}
		string segment;
		bool nextValueIsVmsize = false;
		for (auto& line : contentLines)
		{
			stringstream lineStream(line);
			while (std::getline(lineStream, segment, ':'))
			{

				if (nextValueIsVmsize)
				{
					processInfo->insert(std::make_pair("uid:",segment)); 
					return result;
				}
				if (segment == "Uid")
				{
					nextValueIsVmsize = true;
				}
			}

		}

		return ERROR_UID_IS_MISSING;
	}


	int CProcess::getNumOfFileDescriptorsOpen(shared_ptr<map<string, string>>&processInfo)
	{
		
		int result = SUCCESS;
		pid_t pid = getpid();
		int count = 0;
		string proc = "/proc/";
		string subFolderName = "/fd";
		string fullProcPath = proc + to_string(pid) + subFolderName;
  		std::filesystem::path p1 { fullProcPath };
	
   		for (auto& p : std::filesystem::directory_iterator(p1))
   		{
     			 ++count;
   		}
   		
		processInfo-> insert(std::make_pair("NumFileDescriptors:",to_string(count)));
		return result;
	}














