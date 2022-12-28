#include "ProcessManager.h"
int main()
{
	//CMainThread m;
	CProcessManager* m = CProcessManager::getInstance();
	m->Run();

}
