#include "Event.h"

Event::Event(const char* lpName, bool bInitialState, bool bManualReset)
{
	/*
	CreateEventA(
	_In_opt_ LPSECURITY_ATTRIBUTES lpEventAttributes,
	_In_ BOOL bManualReset,
	_In_ BOOL bInitialState,
	_In_opt_ LPCSTR lpName
	);
	����˵��
	��һ��������ʾ��ȫ���ƣ�һ��ֱ�Ӵ���NULL��
	�ڶ�������ȷ���¼����ֶ���λ�����Զ���λ������TRUE��ʾ�ֶ���λ������FALSE��ʾ�Զ���λ�����Ϊ�Զ���λ����Ը��¼�����WaitForSingleObject()����Զ�����ResetEvent()ʹ�¼����δ����״̬��
	������������ʾ�¼��ĳ�ʼ״̬������TRUR��ʾ�Ѵ�����
	���ĸ�������ʾ�¼������ƣ�����NULL��ʾ�����¼���
	*/
	this->hEvent = CreateEvent(NULL, bManualReset, bInitialState, lpName);
}
Event::~Event()
{
	this->destroy();
}

bool Event::destroy()
{
	return CloseHandle(this->hEvent);
}

// Ĭ���������ȴ�
int Event::wait(int dwMilliseconds)
{
	return WaitForSingleObject(this->hEvent, dwMilliseconds);
}

/*����״̬*/
bool Event::notify(HANDLE houtEvent)
{
	return SetEvent(houtEvent);
}

/*δ����״̬*/
bool Event::reset()
{
	return ResetEvent(this->hEvent);
}

HANDLE Event::getEvent()
{
	return this->hEvent;
}