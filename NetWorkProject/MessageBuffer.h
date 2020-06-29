#ifndef _MESSAGEBUFFER_H_
#define _MESSAGEBUFFER_H_

#include"CriticalSection.h"
#include<deque>
#include<string>	
#include<ostream>

class MessageBuffer
{
public:
	//�R���X�g���N�^
	MessageBuffer(unsigned int bufferSize);
	//���b�Z�[�W����
	void clear();
	//���b�Z�[�W��ǉ�
	void add(const std::string&message);
	//���b�Z�[�W�o�b�t�@�̏o��
	void print(std::ostream&out);

private:
	//���b�Z�[�W�o�b�t�@
	typedef std::deque<std::string>MessageContainer;
	//���b�Z�[�W�o�b�t�@
	MessageContainer mBuffer;
	//���b�Z�[�W�̍ő吔
	MessageContainer::size_type mBufferSize;
	//�o�b�t�@�p�N���e�B�J���Z�N�V����
	CriticalSection mBufferLock;
};

#endif // !_MESSAGEBUFFER_H_



