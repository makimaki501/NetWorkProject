#include "CriticalSection.h"

//�R���X�g���N�^
CriticalSection::CriticalSection()
{
	::InitializeCriticalSection(&mCriticalSection);
}

//�f�X�g���N�^
CriticalSection::~CriticalSection()
{
	::DeleteCriticalSection(&mCriticalSection);
}

//�N���e�B�J���Z�N�V�����J�n
void CriticalSection::enter()
{
	::EnterCriticalSection(&mCriticalSection);
}

//�N���e�B�J���Z�N�V�����I��
void CriticalSection::leave()
{
	;; LeaveCriticalSection(&mCriticalSection);
}

//�R���X�g���N�^
CriticalSection::Lock::Lock(CriticalSection & cs):
	mCriticalSection(cs)
{
	mCriticalSection.enter();
}

//�f�X�g���N�^
CriticalSection::Lock::~Lock()
{
	mCriticalSection.leave();
}
