#ifndef _CLIENTTHREAD_H_
#define _CLIENTTHREAD_H_

#include"Thread.h"
#include<string>
#include<memory>

//�T�[�o�[�X���b�h�N���X
class ServerThread;

//�\�P�b�g�N���X
class Socket;

//�N���C�A���g�X���b�h�N���X
class ClientThread :public Thread
{
public:
	ClientThread(ServerThread&server, Socket*socket, const std::string&name);
	//�f�X�g���N�^
	~ClientThread();
	//�X���b�h�̋N��
	void run();
	//���b�Z�[�W�𑗐M
	void send(const std::string&message);
	//�����I��
	void end();
	//�X���b�h���I�����Ă��邩�H
	bool isEnd();
private:
	//�T�[�o�[�X���b�h
	ServerThread&mServer;
	//�N���C�A���g�p�̑���M�\�P�b�g
	std::auto_ptr<Socket>mSocket;
	//���[�U�[��
	std::string mName;
	//�I���t���O
	bool mIsEnd;
};
#endif // !_CLIENTTHREAD_H_


