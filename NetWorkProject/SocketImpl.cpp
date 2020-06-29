#include "SocketImpl.h"
#include"SocketExeption.h"
#include<memory>

/** ��M���V���b�g�_�E��*/
const int SocketImpl::SHUTDOWN_RECEIVE = SD_RECEIVE;
/** ���M���V���b�g�_�E��*/
const int SocketImpl::SHUTDOWN_SEND = SD_SEND;
/** ����M���V���b�g�_�E��*/
const int SocketImpl::SHUTDOWN_BOTH = SD_BOTH;

//�R���X�g���N�^
SocketImpl::SocketImpl()
	:mSocket(INVALID_SOCKET)
{
}

//�f�X�g���N�^
SocketImpl::~SocketImpl()
{
	//�\�P�b�g�����
	close();
}

//�\�P�b�g�̐ڑ�
void SocketImpl::connect(const InetSocketAddress & address)
{
	//�V�����\�P�b�g���쐬����
	SOCKET sock = ::socket(AF_INET, SOCK_STREAM, 0);

	//�\�P�b�g���쐬�ł������H
	if (sock == INVALID_SOCKET) {
		throw SocketException("�\�P�b�g���쐬�ł��܂���");
	}

	//�T�[�o�[�ւ̃A�h���X���쐬
	SOCKADDR_IN serverAddress;
	std::memset(&serverAddress, 0, sizeof(SOCKADDR_IN));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(address.getPort());
	serverAddress.sin_addr.s_addr = address.getInetAddress().getAddress();

	//�T�[�o�[�Ɛڑ�����
	if (::connect(sock, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
		::closesocket(sock);
		throw SocketException("�ڑ��ł��܂���ł���");
	}

	//���ɃI�[�v�����Ă���ꍇ�͕���
	close();

	//�\�P�b�g�̃A�h���X��ݒ�
	mSocketAddress = address;

	//�\�P�b�g�̃n���h����ݒ�
	mSocket = sock;
}

void SocketImpl::close()
{
	//�ڑ������H
	if (isConnected() == false) {
		return;
	}
	//�\�P�b�g���V���b�g�_�E������
	shutdown(SHUTDOWN_BOTH);

	//�\�P�b�g�����
	::closesocket(mSocket);

	//�\�P�b�g�A�h���X��������
	mSocketAddress = InetSocketAddress();

	//�\�P�b�g�n���h����������
	mSocket = INVALID_SOCKET;
}

//�ڑ���̃\�P�b�g�Ƀf�[�^�𑗐M
int SocketImpl::send(const void * buffer, int size)
{
	int result = ::send(mSocket, (const char*)buffer, size, 0);

	if (result == SOCKET_ERROR || result == 0) {
		throw SocketException("���M�ł��܂���ł���");
	}

	return result;
}

//�ڑ���̃\�P�b�g����f�[�^����M
int SocketImpl::receive(void * buffer, int size)
{
	int result = ::recv(mSocket, (char*)buffer, size, 0);

	if (result == SOCKET_ERROR || result == 0) {
		throw SocketException("��M�ł��܂���ł���");
	}

	return result;
}

//�ڑ����󂯓����
SocketImpl * SocketImpl::accept()
{
	std::auto_ptr<SocketImpl>client(new SocketImpl());

	//�ڑ��̎󂯓�����s��
	SOCKADDR_IN saddr;
	int len = (int)sizeof(saddr);

	SOCKET sock = ::accept(mSocket, (SOCKADDR*)&saddr, &len);

	if (sock == INVALID_SOCKET) {
		throw SocketException("�ڑ��̎󂯓���Ɏ��s���܂���");
	}

	//�󂯓��ꂽ�ڑ��̃\�P�b�g�A�h���X��ݒ�
	client->mSocketAddress = InetSocketAddress(InetAddress(::inet_ntoa(saddr.sin_addr)), saddr.sin_port);

	//�󂯓��ꂽ�ڑ��̃\�P�b�g�n���h����ݒ�
	client->mSocket = sock;

	return client.release();
}

//�w�肳�ꂽ�|�[�g�ԍ��Ƀ\�P�b�g���o�C���h
void SocketImpl::bind(int port)
{
	//�V�����\�P�b�g���쐬����
	SOCKET sock = ::socket(AF_INET, SOCK_STREAM, 0);

	//�\�P�b�g���쐬�ł������H
	if (sock == INVALID_SOCKET) {
		throw SocketException("�\�P�b�g���쐬�ł��܂���");
	}

	//�\�P�b�g�ɖ��O��t����
	SOCKADDR_IN serverAddress;
	std::memset(&serverAddress, 0, sizeof(SOCKADDR_IN));

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

	//�o�C���h����
	if (::bind(sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
		::closesocket(sock);
		throw SocketException("�o�C���h�Ɏ��s���܂���");
	}

	//�\�P�b�g�̃A�h���X��ݒ�
	mSocketAddress = InetSocketAddress(InetAddress(INADDR_ANY), port);

	//�\�P�b�g�̃n���h����ݒ�
	mSocket = sock;
}

//�\�P�b�g�����X����Ԃɂ���
void SocketImpl::listen(int backlog)
{
	//�N���C�A���g����̐ڑ��҂��̏�Ԃɂ���
	if (::listen(mSocket, backlog) == SOCKET_ERROR) {
		throw SocketException("�ڑ��҂��̎��s");
	}
}

//�\�P�b�g�̃V���b�g�_�E�����s��
void SocketImpl::shutdown(int how)
{
	::shutdown(mSocket, how);
}

//�ڑ���̃\�P�b�g�̃\�P�b�g�A�h���X���擾
InetSocketAddress SocketImpl::getInetSocketAddress() const
{
	return mSocketAddress;
}

//�\�P�b�g�̃��[�J���\�P�b�g�A�h���X���擾
InetSocketAddress SocketImpl::getLocalInetSocketAddress() const
{
	SOCKADDR_IN saddr;
	int len = (int)sizeof(saddr);
	if (::getsockname(mSocket, (struct sockaddr*)&saddr, &len) == SOCKET_ERROR) {
		return InetSocketAddress(InetAddress());
	}

	return InetSocketAddress(saddr.sin_addr.s_addr, saddr.sin_port);
}

//�ڑ��������ׂ�
bool SocketImpl::isConnected() const
{
	return mSocket!=INVALID_SOCKET;
}

