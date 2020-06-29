#include "AcceptThread.h"
#include"ServerThread.h"
#include"ClientThread.h"
#include"Socket.h"
#include"SocketExeption.h"
#include"InetAddress.h"
#include<iostream>

//�R���X�g���N�^
AcceptThread::AcceptThread(ServerThread & server):
	mServer(server),
	mIsEnd(false)
{
}

//�f�X�g���N�^
AcceptThread::~AcceptThread()
{
	//�����I��
	end();
}

//�X���b�h�̋N��
void AcceptThread::run()
{
	mIsEnd = false;

	try {
		//�T�[�o�[�\�P�b�g���o�C���h����
		mServerSocket.bind(mServer.getPort());

		while (isEnd() == false) {
			std::cout << "�N���C�A���g�ڑ��҂�" << std::endl;
			//�N���C�A���g���󂯕t����
			std::auto_ptr<Socket>client(mServerSocket.accept());
			std::cout << client->getAddress().getHostAddress() << "�ڑ����܂���" << std::endl;
			std::string name = client->receive();
			//�T�[�o�[�ɃN���C�A���g��ǉ�����
			mServer.addClient(new ClientThread(mServer, client.release(),name));
			//���̃X���b�h�ɐ����n��
			Thread::sleep(0);
		}
	}
	catch (SocketException&) {
		//�\�P�b�g�����
		//�X���b�h�̏I��
		mIsEnd = true;
	}
}

//�����I��
void AcceptThread::end()
{
	//�I���t���O��ݒ�
	mIsEnd = true;
	//�\�P�b�g�����
	mServerSocket.close();
	//�X���b�h�̏I����҂�
	join();
}

//�I�����Ă��邩�H
bool AcceptThread::isEnd()
{
	return mIsEnd;
}
