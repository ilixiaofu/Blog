#include <stdio.h>
#include <assert.h>
#include "Event.h"

#define MAX 100

int apple = 0;
Event proEvent(NULL, true, true);
Event consumeEvent(NULL, false, true);

// �������̺߳���
DWORD WINAPI Product(LPVOID lpParam)
{
	while (1) {
		proEvent.wait();
		if (apple >= MAX) {
			proEvent.notify(consumeEvent.getEvent());
			proEvent.reset();
		}
		else {
			apple++;
			printf("Product id = %5d, Count = %d\n", GetCurrentThreadId(), apple);
		}
		Sleep(60);
	}
	return 0;
}

// �������̺߳���
DWORD WINAPI ConsumerPro(LPVOID lpParam)
{
	while (true) {
		consumeEvent.wait();
		if (apple == 0) {
			consumeEvent.notify(proEvent.getEvent());
			consumeEvent.reset();
		}
		else {
			apple--;
			printf("id = %5d, Count = %d\n", GetCurrentThreadId(), apple);
		}
		Sleep(60);
	}
}


int main(int argc, char* argv[])
{
	HANDLE hThread[2] = { 0 };
	hThread[0] = CreateThread(NULL, 0, Product, NULL, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, ConsumerPro, NULL, 0, NULL);
	// �ȴ������߳�ִ�н���
	WaitForMultipleObjects(2, hThread, true, INFINITE);
	printf("all thread execu over\n");
}