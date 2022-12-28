#include "ProcessManager.h"
#include <thread>
#include <stdio.h>
#include <iostream>
#include <iterator>
#include <sys/types.h>
#include <unistd.h>
#include <csignal>
#include "utiles.h"
#include "Error.h"
CProcessManager* signal_object = nullptr;
CProcessManager* CProcessManager::instancePtr = NULL;

void signal_handler(int signum) { signal_object->SignalHandler(signum); }

CProcessManager::CProcessManager() 
{ 
	mHandelProcessInfo = make_shared<std::map<string,string>>();
	mStopPrint = true; 
}

void CProcessManager::SignalHandler(int signum)
{
	std::cout << "Interrupt signal (" << signum << ") received.\n";
	mStopPrint = false;
}
void CProcessManager::Run() 
{
	signal_object = this;
	//ctrl C
	signal(SIGINT, signal_handler);
	//pkill
	signal(SIGTERM, signal_handler);
	std::thread t(&CProcessManager::PrintProccesInfo, this);
	
	t.join();
	std::cout << "EXIT" << std::endl;
}

void CProcessManager::PrintProccesInfo()
{
	
	int result = SUCCESS;
	while (mStopPrint)
	{
		result = filTheHandelProcessInfoMap();
		if (result!=SUCCESS)
		{
		   cout << "error: "<< result;
		   break;
		}
		
		for(const auto [v,k] : *mHandelProcessInfo)
		{
  			 std::cout << v<< " " << k << endl ;
  	        }
  	        std::cout<<"\n";
  	       
		std::this_thread::sleep_for(std::chrono::microseconds(1000));
	}
}
int CProcessManager::filTheHandelProcessInfoMap()
{
	int result = SUCCESS;
	result= mProcess.getPid(mHandelProcessInfo);
	if (result!=SUCCESS)
	{
		return result;
	}
	
	result = mProcess.getPpid(mHandelProcessInfo);
	if (result!=SUCCESS)
	{
		return result;
	}
	
	result = mProcess.getPppid(mHandelProcessInfo);
	if (result!=SUCCESS)
	{
		return result;
	}
	
	result = mProcess.getPcmd(mHandelProcessInfo);
	if (result!=SUCCESS)
	{
		return result;
	}
	
	result= mProcess.getFileName(mHandelProcessInfo);
	if (result!=SUCCESS)
	{
		return result;
	}
	
	result= mProcess.getFullPath(mHandelProcessInfo);
	if (result!=SUCCESS)
	{
		return result;
	}
	

	result = mProcess.getFileSize(mHandelProcessInfo);
	if (result!=SUCCESS)
	{
		return result;
	}
	result = mProcess.getVirtualMemSize(mHandelProcessInfo);
	if (result!=SUCCESS)
	{
		return result;
	}
	
	result = mProcess.getUid(mHandelProcessInfo);
	if (result!=SUCCESS)
	{
		return result;
	}
	
	result = mProcess.getNumOfFileDescriptorsOpen(mHandelProcessInfo);
	if (result!=SUCCESS)
	{
		return result;
	}
	
	return result;


}
