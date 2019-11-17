#include <stdio.h>
#include <assert.h>
#include "Semaphores.h"

int count = 0;

DWORD WINAPI ThreadProc1(LPVOID lpParam)
{
	Semaphores* semaphores = (Semaphores*)lpParam;
	for (int i = 0; i < 100; i++)
	{
		semaphores->lock();
		count++;
		printf("id = %5d, Count = %d\n", GetCurrentThreadId(), count);
		Sleep(80);
		semaphores->unlock();
	}
	return 0;
}

DWORD WINAPI ThreadProc2(LPVOID lpParam)
{
	Semaphores* semaphores = (Semaphores*)lpParam;
	for (int i = 0; i < 100; i++)
	{
		semaphores->lock();
		count++;
		printf("id = %5d, Count = %d\n", GetCurrentThreadId(), count);
		Sleep(80);
		semaphores->unlock();
	}
	return 0;
}

DWORD WINAPI ThreadProc3(LPVOID lpParam)
{
	Semaphores* semaphores = (Semaphores*)lpParam;
	for (int i = 0; i < 100; i++)
	{
		semaphores->lock();
		count++;
		printf("id = %5d, Count = %d\n", GetCurrentThreadId(), count);
		Sleep(80);
		semaphores->unlock();
	}
	return 0;
}

int main(int argc, char* argv[])
{
	Semaphores semaphores(NULL, 3, 3);
	HANDLE hThread[3] = { 0 };
	hThread[0] = CreateThread(NULL, 0, ThreadProc1, &semaphores, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, ThreadProc2, &semaphores, 0, NULL);
	hThread[2] = CreateThread(NULL, 0, ThreadProc3, &semaphores, 0, NULL);
	// �ȴ������߳�ִ�н���
	WaitForMultipleObjects(3, hThread, true, INFINITE);
	printf("all thread execu over\n");

	/*
	OpenSemaphoreA(
    _In_ DWORD dwDesiredAccess,
    _In_ BOOL bInheritHandle,
    _In_ LPCSTR lpName
    );
	dwDesiredAccess���Ի������������Ȩ�޵����ã�SEMAPHORE_ALL_ACCESS ����Ի��������ȫ���ʣ�
	SEMAPHORE_MODIFY_STATE ����ʹ�� ReleaseSemaphore ������SYNCHRONIZE �����������ͬ��ʹ�ã�
	bInheritHandle���Ƿ�ϣ���ӽ��̼̳л���������ľ����һ������Ϊfalse��
	lpName��Ҫ�򿪵Ļ�������������ƣ�
	*/
}