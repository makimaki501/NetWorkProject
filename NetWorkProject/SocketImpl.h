#ifndef  _SOCKETIMPL_H_
#define _SOCKETIMPL_H_

#include<winsock2.h>
#include"InetSocketAddress.h"

//�\�P�b�g�̎����N���X
class SocketImpl
{
public:
	//�R���X�g���N�^
	SocketImpl();
	//�f�X�g���N�^
	~SocketImpl();
	//�\�P�b�g�̐ڑ�
	void connect(const InetSocketAddress&address);
	//�\�P�b�g�����
	void close();
	//�ڑ���̃\�P�b�g�Ƀf�[�^�𑗐M
	int send(const void* buffer, int size);
	//�ڑ���̃\�P�b�g����f�[�^����M
	int receive(void*buffer, int size);
	//�ڑ����󂯓����
	SocketImpl*accept();
	//�w�肳�ꂽ�|�[�g�ԍ��Ƀ\�P�b�g���o�C���h����
	void bind(int port);
	//�\�P�b�g�����X����Ԃɂ���
	void listen(int backlog = 0);
	//�\�P�b�g�̃V���b�g�_�E�����s��
	void shutdown(int how);
	//�ڑ���̃\�P�b�g�̃\�P�b�g�A�h���X���擾
	InetSocketAddress getInetSocketAddress()const;
	//���[�J���\�P�b�g�A�h���X���擾
	InetSocketAddress getLocalInetSocketAddress()const;
	//�ڑ��������ׂ�
	bool isConnected()const;
private:
	//�R�s�[�֎~
	SocketImpl(const SocketImpl&other);
	SocketImpl&operator=(const SocketImpl&other);
public:
	//��M���V���b�g�_�E��
	const static int SHUTDOWN_RECEIVE;
	//���M���V���b�g�_�E��
	const static int SHUTDOWN_SEND;
	//����M���V���b�g�_�E��
	const static int SHUTDOWN_BOTH;
private:
	//�\�P�b�g�n���h��
	SOCKET mSocket;
	//�\�P�b�g�A�h���X
	InetSocketAddress mSocketAddress;
};


#endif //  _SOCKETIMPL_H_
