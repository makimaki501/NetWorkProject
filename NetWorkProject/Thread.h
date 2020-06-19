#ifndef _THREAD_H_
#define _THREAD_H_

#include "IRunnable.h"

//�X���b�h�N���X
class Thread :public IRunnable {
public:
	//�R���X�g���N�^
	Thread(IRunnable *runnable = 0);
	//�f�X�g���N�^
	virtual ~Thread();
	//�X���b�h�̊J�n
	virtual void start();
	//�X���b�h�̊J�n
	virtual void start(IRunnable*runnable);
	//�X���b�h�̏I����҂�
	void join();
	//�X���[�v����
	static void sleep(unsigned int millsecond);
	//�X���b�h�̎��s
	virtual void run();

private:
	//�R�[���o�b�N�֐�
	static void callback(void*runnable);

private:
	//�X���b�h�̃n���h��
	void* mHandle;
	//���s����X���b�h
	IRunnable*mRunnable;
};

#endif // !_THREAD_H_
