#include <stdio.h>
#include <assert.h>
#include "Mutex.h"

int count = 0;

DWORD WINAPI ThreadProc1(LPVOID lpParam)
{
	Mutex* mutext = (Mutex*)lpParam;
	for (int i = 0; i < 100; i++)
	{
		mutext->lock();
		count++;
		printf("id = %5d, Count = %d\n", GetCurrentThreadId(), count);
		Sleep(80);
		mutext->unlock();
	}
	return 0;
}

DWORD WINAPI ThreadProc2(LPVOID lpParam)
{
	Mutex* mutext = (Mutex*)lpParam;
	for (int i = 0; i < 100; i++)
	{
		mutext->lock();
		count++;
		printf("id = %5d, Count = %d\n", GetCurrentThreadId(), count);
		Sleep(80);
		mutext->unlock();
	}
	return 0;
}

int main(int argc, char* argv[])
{
	Mutex mutext(NULL);
	HANDLE hThread[2] = { 0 };
	hThread[0] = CreateThread(NULL, 0, ThreadProc1, &mutext, 0, NULL);
	// ����һ��������߳�
	hThread[1] = CreateThread(NULL, 0, ThreadProc2, &mutext, 0, NULL);
	// �ȴ������߳�ִ�н���
	WaitForMultipleObjects(2, hThread, true, INFINITE);
	printf("all thread execu over\n");

	/*
	OpenMutexA(
	_In_ DWORD dwDesiredAccess,
	_In_ BOOL bInheritHandle,
	_In_ LPCSTR lpName
	);
	dwDesiredAccess���Ի������������Ȩ�޵����ã�MUTEX_ALL_ACCESS ����Ի��������ȫ���ʣ�
	MUTEX_MODIFY_STATE ����ʹ�� ReleaseMutex ������SYNCHRONIZE �����������ͬ��ʹ�ã�
	bInheritHandle���Ƿ�ϣ���ӽ��̼̳л���������ľ����һ������Ϊfalse��
	lpName��Ҫ�򿪵Ļ�������������ƣ�
	*/
}