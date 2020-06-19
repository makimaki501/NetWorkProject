#ifndef _SERVERSOCKET_H_
#define _SERVERSOCKET_H_

#include "Socket.h"	
#include<memory>

class SocketImpl;

//�T�[�o�[�\�P�b�g�N���X
class ServerSocket
{
public:
	//�R���X�g���N�^
	ServerSocket();
	//�R���X�g���N�^(�o�C���h����)
	ServerSocket(int port, int backlog = 0);
	//�f�X�g���N�^
	virtual ~ServerSocket();
	//�ڑ��v����ҋ@���āA�\�P�b�g���󂯓����
	std::auto_ptr<Socket>accept();
	//�\�P�b�g���o�C���h���āA���X����Ԃɂ���
	void bind(int port, int backlog = 0);
	//�\�P�b�g�����
	void close();
	//�\�P�b�g�̃A�h���X���擾
	InetAddress getAddress()const;
	//�\�P�b�g�̃|�[�g�ԍ����擾
	int getPort()const;
private:
	//�R�s�[�֎~
	ServerSocket(const ServerSocket&other);
	ServerSocket&operator=(const ServerSocket&other);
private:
	//�\�P�b�g�����N���X
	std::auto_ptr<SocketImpl>mImpl;
};

#endif // _SERVERSOCKET_H_
