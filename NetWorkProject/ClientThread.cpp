#include "ClientThread.h"
#include"ServerThread.h"
#include"Socket.h"

//�R���X�g���N�^
ClientThread::ClientThread(ServerThread & server, Socket * socket, const std::string&name) :
	mServer(server),
	mSocket(socket),
	mName(name),
	mIsEnd(false)
{
}

//�f�X�g���N�^
ClientThread::~ClientThread()
{
	//�����I��
	end();
}

//�X���b�h�̋N��
void ClientThread::run()
{
	//�X���b�h�̊J�n
	mIsEnd = false;
	try {
		//�����������Ƃ�m�点��
		mServer.sendClient(mName + "���񂪓������܂���");
		//�N���C�A���g����̃��b�Z�[�W����������
		while (mIsEnd == false) {
			//�N���C�A���g����̃f�[�^����M
			std::string message = mSocket->receive();
			//�N���C�A���g�̐ؒf�v�����`�F�b�N
			if (message == "end") {
				break;
			}
			//���[�U�[����t�����āA�N���C�A���g�Ƀ��b�Z�[�W�𑗐M
			mServer.sendClient(mName + "�F" + message);
			//���̃X���b�h�ɐ����n��
			Thread::sleep(0);
		}
		//�ގ��������Ƃ�m�点��
		mServer.sendClient(mName + "���񂪑ގ����܂���");
	}
	catch (SocketException&) {
	}
	//�I���t���O�̐ݒ�
	mIsEnd = true;
}

void ClientThread::send(const std::string & message)
{
	mSocket->send(message);
}

//�����I��
void ClientThread::end()
{
	//�I���t���O�̐ݒ�
	mIsEnd = true;
	//�\�P�b�g�����
	mSocket->close();
	//�X���b�h�̏I����҂�
	join();
}

//�X���b�h���I�����Ă��邩���ׂ�
bool ClientThread::isEnd()
{
	return mIsEnd;
}
