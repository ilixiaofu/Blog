#include <stdio.h>
#include <assert.h>
#include "CriticalSection.h"

int count = 0;

DWORD WINAPI ThreadProc1(LPVOID lpParam)
{
	CriticalSection* cs = (CriticalSection*)lpParam;
	for (int i = 0; i < 10; i++)
	{
		cs->lock();
		count++;
		printf("id = %d, Count = %d\n", GetCurrentThreadId(), count);
		Sleep(200);
		cs->unlock();
	}
	return 0;
}

DWORD WINAPI ThreadProc2(LPVOID lpParam)
{
	CriticalSection* cs = (CriticalSection*)lpParam;
	for (int i = 0; i < 10; i++)
	{
		cs->lock();
		count++;
		printf("id = %d, Count = %d\n", GetCurrentThreadId(), count);
		Sleep(200);
		cs->unlock();
	}
	return 0;
}

int main(int argc, char* argv[])
{
	CriticalSection* cs = new CriticalSection();
	HANDLE hThread[2] = { 0 };
	hThread[0] = CreateThread(NULL, 0, ThreadProc1, cs, 0, NULL);
	// ����һ��������߳�
	hThread[1] = CreateThread(NULL, 0, ThreadProc2, cs, CREATE_SUSPENDED, NULL);
	// �ָ�������߳�
	ResumeThread(hThread[1]);

	// �ȴ������߳�ִ�н���
	WaitForMultipleObjects(2, hThread, true, INFINITE);
	printf("all thread execu over\n");
	delete cs;
}