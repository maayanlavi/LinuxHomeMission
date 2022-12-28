
#pragma once
#include <iostream>
#include <atomic>  
#include <csignal>
#include <map>
#include "Process.h"

	class CProcessManager
	{
	private:
		std::atomic<bool> mStopPrint;
		CProcess mProcess;
		std::shared_ptr<std::map<std::string,std::string>> mHandelProcessInfo;
		int filTheHandelProcessInfoMap();
		static CProcessManager* instancePtr;
		CProcessManager();

		
	public:
		CProcessManager(const CProcessManager& obj) = delete;
		static CProcessManager* getInstance() 
		{
			if (instancePtr == NULL)
			{
				instancePtr = new CProcessManager();
				return instancePtr;
			}
			else 
			{
				return instancePtr;
			}
		}
		void Run();
		void SignalHandler(int signum);
		void PrintProccesInfo();

	};

	
