#ifndef _SERVERTHREAD_H_
#define _SERVERTHREAD_H_

#include"Thread.h"
#include"CriticalSection.h"
#include<list>
#include<boost/shared_ptr.hpp>

//�N���C�A���g�X���b�h
class ClientThread;

//�T�[�o�[�X���b�h�N���X
class ServerThread:public Thread
{
public:
	//�R���X�g���N�^
	ServerThread(int port);
	//�f�X�g���N�^
	~ServerThread();
	//�T�[�o�[�X���b�h�̋N��
	void run();
	//�N���C�A���g�̒ǉ�
	void addClient(ClientThread*client);
	//�N���C�A���g�̍폜
	void removeClient();
	//�N���C�A���g�����ׂč폜
	void clearClient();
	//�T�[�o�[�X���b�h�̏I��
	void end();
	//�|�[�g�ԍ��̎擾
	int getPort()const;
	//�I�����Ă��邩���ׂ�
	bool isEnd();
	//�N���C�A���g�Ƀ��b�Z�[�W�𑗐M
	void sendClient(const std::string&message);
private:
	//�N���C�A���g�X���b�h�̃|�C���^�^
	typedef boost::shared_ptr<ClientThread>ClientThreadPtr;
	//�N���C�A���g�X���b�h�̃R���e�i�^
	typedef std::list<ClientThreadPtr>ClientContainer;
	//�|�[�g�ԍ�
	int mPort;
	//�I���t���O
	bool mIsEnd;
	//�N���C�A���g�X���b�h�R���e�i
	ClientContainer mClientContainer;
	//�N���C�A���g�X���b�h�R���e�i���b�N
	CriticalSection mClientContainerLook;
};

#endif // !_SERVERTHREAD_H_


