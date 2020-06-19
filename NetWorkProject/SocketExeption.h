#ifndef _SOCKETEXCEPTION_H_
#define _SOCKETEXCEPTION_H_

#include<stdexcept>

//�\�P�b�g��O�N���X
class SocketException :public std ::runtime_error
{
public:
	//�R���X�g���N�^
	SocketException(const std::string&msg)
		:std::runtime_error(msg)
	    {
	    }

};

#endif // !_SOCKETEXCEPTION_H_

