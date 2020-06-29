#include "ServerThread.h"
#include "ClientThread.h"
#include "AcceptThread.h"
#include "Socket.h"
#include<boost/mem_fn.hpp>
#include<boost/bind.hpp>

//�R���X�g���N�^
ServerThread::ServerThread(int port) :
	mPort(port),
	mIsEnd(false)
{
}

//�f�X�g���N�^
ServerThread::~ServerThread()
{
	//�����I��
	end();
}

//�X���b�h�̎��s
void ServerThread::run()
{
	//�X���b�h���J�n
	mIsEnd = false;
	//�A�N�Z�v�g�X���b�h���쐬����
	std::auto_ptr<AcceptThread>acceptor(new AcceptThread(*this));
	//��M�X���b�h���N��
	acceptor->start();
	//�I������܂ŌJ��Ԃ�
	while (isEnd() == false)
	{
		//�I�������N���C�A���g���폜
		removeClient();
		//���̃X���b�h�ɐ����n��
		Thread::sleep(0);
	}
	//�A�N�Z�v�g�X���b�h�������I��
	acceptor->end();
	//�N���C�A���g��S�ď���
	clearClient();
	//�I���t���O��ݒ�
	mIsEnd = true;
}

//�N���C�A���g�̒ǉ�
void ServerThread::addClient(ClientThread * client)
{
	CriticalSection::Lock guard(mClientContainerLook);
	//�N���C�A���g��o�^
	mClientContainer.push_back(ClientThreadPtr(client));

	//�N���C�A���g���X���b�h�N��
	client->start();

}

void ServerThread::removeClient()
{
	CriticalSection::Lock guard(mClientContainerLook);
	//�I�����Ă���N���C�A���g���폜
	mClientContainer.remove_if(boost::mem_fn(&ClientThread::isEnd));
}

void ServerThread::clearClient()
{
}

//�����I��
void ServerThread::end()
{
	//�I���t���O��ݒ肷��
	mIsEnd = true;
	//�X���b�h�̏I����҂�
	join();
}

//�|�[�g�ԍ��̎擾
int ServerThread::getPort() const
{
	return mPort;
}

bool ServerThread::isEnd()
{
	return false;
}

//�N���C�A���g�Ƀ��b�Z�[�W�𑗐M
void ServerThread::sendClient(const std::string & message)
{
	CriticalSection::Lock guard(mClientContainerLook);

	//�S�N���C�A���g�Ƀ��b�Z�[�W�𑗂�
	std::for_each(
		mClientContainer.begin(),
		mClientContainer.end(),
		boost::bind(boost::mem_fn(&ClientThread::send), _1, message)
	);
}
