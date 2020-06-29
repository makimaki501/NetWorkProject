#ifndef _CHATCLIENTTHREAD_H_
#define _CHATCLIENTTHREAD_H_

#include "Thread.h"
#include"MessageBuffer.h"
#include"CriticalSection.h"
#include"Socket.h"
#include"InetSocketAddress.h"
#include<string>

//�`���b�g�N���C�A���g�X���b�h�N���X
class ChatClientThread:public Thread
{
public:
	//�R���X�g���N�^
	ChatClientThread(unsigned int bufferSize);
	//�f�X�g���N�^
	~ChatClientThread();
	//���[�U�[���̐ݒ�
	void setName(const std::string&name);
	//�T�[�o�[�̃\�P�b�g�A�h���X�̐ݒ�
	void setServerAddress(const InetSocketAddress&address);
	//�X���b�h�̎��s
	void run();
	//���b�Z�[�W�𑗐M
	void sendMessage(const std::string&message);
	//���b�Z�[�W�̏o��
	void printMessage(std::ostream&out);
	//�ڑ������H
	bool isConnect();
	//�����I������
	void end();
private:
	//�T�[�o�[�̃\�P�b�g�A�h���X
	InetSocketAddress mServerAddress;
	//���[�U�[��
	std::string mName;
	//���b�Z�[�W�o�b�t�@
	MessageBuffer mMessageBuffer;
	//�ʐM�p�\�P�b�g
	Socket mSocket;

};

#endif // !_CHATCLIENTTHREAD_H_


