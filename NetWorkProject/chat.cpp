#include<winsock2.h>
#include<stdio.h>
#include<string>
#include<stdlib.h>
#include<memory>
#include<iostream>

#include"Socket.h"
#include"ServerSocket.h"

#pragma comment (lib,"WSock32.lib")

//Socket*mSocket;

//�`���b�g�@�T�[�o�[�֐�
void ChatServer() {
	ServerSocket serverSocket;
	std::auto_ptr<Socket>socket;
	u_short port;
	//auto serverSocket = std::make_unique<ServerSocket>(port);

	//�|�[�g�ԍ��̓���
	std::cout << "�g�p����|�[�g�ԍ�-->";
	std::cin >> port;
	fflush(stdin);

	//�\�P�b�g���o�C���h���āA���X����Ԃɂ���
	serverSocket.bind(port);
	std::cout << "�o�C���h�ɐ������܂���" << std::endl;

	//�ڑ���ҋ@����
	socket = serverSocket.accept();
	std::cout << "�ڑ��̎󂯓���ɐ������܂���\n";

	//serverSocket.close();

	//��b�J�n
	std::cout << "��b�J�n�ł�\n";
	while (1) {
		std::string str;

		std::cout << "��M��҂��Ă��܂�\n";
		str = socket->receive();


		//��M���b�Z�[�W�̕\��
		std::cout << "��M-->" << str << std::endl;

		//���M���b�Z�[�W�̓���
		std::cout << "���M-->";
		std::cin >> str;
		fflush(stdin);

		//���M���b�Z�\�W�𑗂�
		socket->send(str);

		//�T�[�o�[������ؒf����
		if (!socket->isConnected()) {
			break;
		}

	}
	socket->close();
}

void ChatClient() {
	u_short port;
	std::auto_ptr<Socket>socket;
	//Socket *socket;
	std::string server;
	//HOSTENT*lpHost;


	//�|�[�g�ԍ��̓���
	std::cout << "�g�p����|�[�g�ԍ�-->";
	std::cin >> port;
	fflush(stdin);

	std::cout << "�ڑ����IP�A�h���X����͂��Ă�������-->";
	std::cin >> server;

	std::cout << "�ڑ����J�n���܂��B" << std::endl;
	socket->connect(server, port);


	std::cout << "�ڑ��ɐ������܂����B" << std::endl;

	std::cout << "��b���J�n���܂��B" << std::endl;

	while (1) {
		//����M�o�b�t�@
		std::string szBuf;

		//���M���b�Z�[�W�̓���
		std::cout << "���M-->";
		std::cin >> szBuf;

		//���b�Z�[�W�̑��M
		socket->send(szBuf);

		szBuf = socket->receive();
		std::cout << "��M-->" << server << std::endl;

	}

}
//
//int main() {
//	WSADATA wsaData;
//	int mode;
//
//	//WinSock�̏�����
//	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
//		//�������G���[
//		std::cout << "Winsock�̏������Ɏ��s���܂���" << std::endl;
//		return 0;
//	}
//
//	//�T�[�o�[���H�N���C�A���g���H
//	std::cout << "�T�[�o�[�Ȃ�0����� �N���C�A���g�Ȃ�1�����-->";
//	std::cin >> mode;
//
//	if (mode == 0) {
//		//�T�[�o�[�Ƃ��ċN��
//		ChatServer();
//	}
//	else {
//		ChatClient();
//	}
//
//	//Winsock�̏I������
//	WSACleanup();
//}