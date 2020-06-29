#include"Thread.h"
#include"CriticalSection.h"
#include<iostream>

//��s�N���X
class Bank
{
public:
	//�R���X�g���N�^
	Bank(int money) :mCash(money)
	{
	}

	//���������o��
	int dispenseCash(int money)
	{
		//�����A�N�Z�X���b�N���s��
		CriticalSection::Lock guard(mCashLock);

		//��s�̎c���������o�����z��菭�Ȃ�
		if (mCash < money) {
			std::cout << "�������s�����Ă��܂�\n";
			//�����o���Ȃ��ꍇ�̓}�C�i�X��Ԃ�
			return -1;
		}
		std::cout << "�����������o�����܂��E�E�E\n";
		mCash -= money;
		return money;
	}

	//Bank�̌����c��
	void printCash()
	{
		//�����A�N�Z�X���b�N���s��
		CriticalSection::Lock guard(mCashLock);

		std::cout << "��s�̌���" << mCash << std::endl;
	}
private:
	//��s�̌����c��
	int mCash;
	//�����A�N�Z�X���b�N
	CriticalSection mCashLock;
};

//�T�N����s(�O���[�o���ȃN���X)
Bank SakuraBank(1000);

//�c���N�̃N���X
class Tanaka :public Thread
{
public:
	//�X���b�h�̎��s
	void run()
	{
		int money;
		//��s���猻���������o���Ȃ��Ȃ�܂ň����o��
		do {
			//��s����100�~�����o��
			std::cout << "�c���N100�~�����o��\n";
			money = SakuraBank.dispenseCash(100);
		} while (money >= 0);
	}
};

//��،N�̃N���X
class Suzuki :public Thread
{
public:
	//�X���b�h�̎��s
	void run()
	{
		int money;
		//��s���猻���������o���Ȃ��Ȃ�܂ň����o��
		do {
			//��s����100�~�����o��
			std::cout << "��،N50�~�����o��\n";
			money = SakuraBank.dispenseCash(50);
		} while (money >= 0);
	}
};
//
//void main()
//{
//	Tanaka tanaka; //�c���N�X���b�h
//	Suzuki suzuki; //��،N�X���b�h
//
//	//�c���N�X���b�h�J�n
//	tanaka.start();
//	//��،N�X���b�h�J�n
//	suzuki.start();
//
//	//�c���N�̏I����҂�
//	tanaka.join();
//	//��،N�̏I����҂�
//	suzuki.join();
//
//	//��s�̌�����\��
//	SakuraBank.printCash();
//}