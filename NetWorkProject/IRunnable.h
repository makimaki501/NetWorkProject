#ifndef _IRUNNABLE_H_
#define _IRUNNABLE_H_

//�X���b�h���s�C���^�[�t�F�[�X
class IRunnable
{
public:
	//�f�X�g���N�^
	virtual ~IRunnable() {}
	//�X���b�h���s
	virtual void run() = 0;
};

#endif // !_IRUNNABLE_H_
