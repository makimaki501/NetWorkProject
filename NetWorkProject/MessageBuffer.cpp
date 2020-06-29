#include "MessageBuffer.h"

//�R���X�g���N�^
MessageBuffer::MessageBuffer(unsigned int bufferSize) :
	mBufferSize(bufferSize)
{
}

//���b�Z�[�W������
void MessageBuffer::clear()
{
	CriticalSection::Lock guard(mBufferLock);
	mBuffer.clear();
}

//���b�Z�[�W��ǉ�
void MessageBuffer::add(const std::string & message)
{
	CriticalSection::Lock guard(mBufferLock);
	//�o�b�t�@�Ƀ��b�Z�[�W��ǉ�
	mBuffer.push_back(message);
	//�o�b�t�@�T�C�Y�𒴂�����1�s�폜
	if (mBuffer.size() > mBufferSize) {
		mBuffer.pop_front();
	}
}

//���b�Z�[�W�o�b�t�@�̏o��
void MessageBuffer::print(std::ostream & out)
{
	CriticalSection::Lock guard(mBufferLock);

	//���b�Z�[�W���o�͂���
	for (MessageContainer::size_type i = 0; i < mBuffer.size(); i++) {
		out << mBuffer[i] + "\r\n";
	}
}
