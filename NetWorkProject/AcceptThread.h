#ifndef _ACCEPTTHREAD_H_
#define _ACCEPTTHREAD_H_

#include"ServerSocket.h"
#include"Thread.h"

//�T�[�o�[�X���b�h�N���X
class ServerThread;

//�A�N�Z�v�g�X���b�h�N���X
class AcceptThread:public Thread
{
public:
	//�R���X�g���N�^
	AcceptThread(ServerThread&server);
	//�f�X�g���N�^
	~AcceptThread();
	//�X���b�h�̎��s
	void run();
	//�����I��
	void end();
	//�I�����Ă��邩�H
	bool isEnd();
private:
	//�T�[�o�[�X���b�h
	ServerThread&mServer;
	//�T�[�o�[�\�P�b�g
	ServerSocket mServerSocket;
	//�I���t���O��
	bool mIsEnd;
};
#endif // !_ACCEPTTHREAD_H_


