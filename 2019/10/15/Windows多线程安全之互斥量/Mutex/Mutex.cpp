#include "Mutex.h"

Mutex::Mutex(char* lpName):lpName(lpName)
{
	// bInitialOwner�ڶ�����������ȷ���������ĳ�ʼӵ���ߡ�
	this->hMutex = CreateMutexA(NULL, false, this->lpName);
}

Mutex::~Mutex()
{
	this->destroy();
}

const char& Mutex::getName()
{
	return *(this->lpName);
}

// �����ٽ���
int Mutex::lock()
{
	// INFINITE����ʾ�����ȴ�
	return WaitForSingleObject(this->hMutex, INFINITE);
}

// �ͷ��ٽ���
bool Mutex::unlock()
{
	return ReleaseMutex(this->hMutex);
}

bool Mutex::destroy()
{
	return CloseHandle(this->hMutex);
}
