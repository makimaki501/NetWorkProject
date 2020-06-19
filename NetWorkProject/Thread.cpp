#include "Thread.h"
#include<Windows.h>
#include<process.h>

//�R���X�g���N�^
Thread::Thread(IRunnable * runnable) :
	mHandle(0),
	mRunnable(runnable)
{
	if (mRunnable == 0) {
		mRunnable = this;
	}
}

//�f�X�g���N�^
Thread::~Thread()
{
}

//�X���b�h�̊J�n
void Thread::start()
{
	//�X���b�h���J�n
	mHandle = reinterpret_cast<void*>(::_beginthread(callback, 0, this));
}

//�X���b�h�̊J�n
void Thread::start(IRunnable * runnable)
{
	mRunnable = runnable;

	start();
}

//�X���b�h�̏I����҂�
void Thread::join()
{
	if (mHandle != 0) {
		::WaitForSingleObject(mHandle, INFINITE);
	}
}

//�X���[�v����
void Thread::sleep(unsigned int millsecond)
{
	::Sleep(millsecond);
}

//�X���b�h�̎��s
void Thread::run()
{
}

//�R�[���o�b�N�֐�
void Thread::callback(void * runnable)
{
	Thread*thread = reinterpret_cast<Thread*>(runnable);

	//�X���b�h�̏��������s����
	thread->mRunnable->run();

	//�X���b�h�n���h���𖳌��ɂ���
	thread->mHandle = 0;
}
