#include "Thread.h"
#include<iostream>

//Test1�X���b�h�N���X
class Test1 :public Thread
{
public:
	//Test1�X���b�h�̏���
	void run() {
		for (int i = 0; i < 10; i++) {
			std::cout << "Test1�̃N���X���s\n";
			//1�b�ԃX���[�v����
			Thread::sleep(1000);
		}
	}
};

//Test2�X���b�h�N���X
class Test2 :public Thread
{
public:
	//Test2�X���b�h�̏���
	void run()
	{
		for (int i = 0; i < 10; i++) {
			std::cout << "Test2�̃N���X���s\n";
			//0.5�b�ԃX���[�v����
			Thread::sleep(500);
		}
	}
};

////main�֐�
//int main()
//{
//	Test1 test1;
//	Test2 test2;
//
//	//Test1�X���b�h�̎��s���J�n
//	test1.start();
//	//Test2�X���b�h�̎��s���J�n
//	test2.start();
//
//	for (int i = 0; i < 10; i++) {
//		std::cout << "Main�֐��̎��s\n";
//		//0.2�b�ԃX���[�v
//		Thread::sleep(200);
//	}
//
//	//Test1�̏I����҂�
//	test1.join();
//	//Test2�̏I����҂�
//	test2.join();
//}