#include "ChatClientThread.h"

//�R���X�g���N�^
ChatClientThread::ChatClientThread(unsigned int bufferSize) :
	mMessageBuffer(bufferSize)
{
}

//�f�X�g���N�^
ChatClientThread::~ChatClientThread()
{
	//�����I��
	end();
}

//���[�U�[���̐ݒ�
void ChatClientThread::setName(const std::string & name)
{
	mName = name;
}

//�T�[�o�[�̃\�P�b�g�A�h���X�̐ݒ�
void ChatClientThread::setServerAddress(const InetSocketAddress & address)
{
	mServerAddress = address;
}

//�X���b�h�̎��s
void ChatClientThread::run()
{
	//���b�Z�[�W�o�b�t�@��������
	mMessageBuffer.clear();
	mMessageBuffer.add("�T�[�o�[�ɐڑ����Ă��܂��c");

	try {
		//�T�[�o�[�ɐڑ�����
		mSocket.connect(mServerAddress);
		mMessageBuffer.add("�T�[�o�[�ɐڑ��ł��܂���");
		//���[�U�[���𑗐M����
		sendMessage(mName);
		//�ڑ����͎�M����
		while (isConnect() == true) {
			//�T�[�o�[����̃��b�Z�[�W���o�b�t�@�ɒǉ�
			mMessageBuffer.add(mSocket.receive());
			//���̃X���b�h�ɐ����n��
			Thread::sleep(0);
		}
	}
	catch (SocketException&e) {
		mMessageBuffer.add(e.what());
	}
	//�\�P�b�g�����
	mSocket.close();
	mMessageBuffer.add("�ؒf���܂���");
}

//���b�Z�[�W�𑗐M
void ChatClientThread::sendMessage(const std::string & message)
{
	//�ڑ����łȂ���Α��M�ł��Ȃ�
	if (isConnect() == false) {
		return;
	}
	//���b�Z�[�W�̑��M���s��
	try {
		mSocket.send(message);
	}
	catch(SocketException&e){
		mMessageBuffer.add(e.what());
	}
}

//���b�Z�[�W�̏o��
void ChatClientThread::printMessage(std::ostream & out)
{
	mMessageBuffer.print(out);
}

//�ڑ������H
bool ChatClientThread::isConnect()
{
	return mSocket.isConnected();
}

//�����I��
void ChatClientThread::end()
{
	//�\�P�b�g�������I�ɕ���
	mSocket.close();
	//�X���b�h�̏I����҂�
	join();
}
