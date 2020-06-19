#ifndef _INETSOCKETADDRESS_H_
#define _INETSOCKETADDRESS_H_

#include"InetAddress.h"

//�C���^�[�l�b�g�\�P�b�g�A�h���X�N���X
class InetSocketAddress {
public:
	//�R���X�g���N�^
	InetSocketAddress(const InetAddress&address = InetAddress(), int port = 0);
	//�C���^�[�l�b�g�A�h���X�̎擾
	const InetAddress&getInetAddress()const;
	//�|�[�g�ԍ��̎擾
	int getPort()const;

private:
	//�C���^�[�l�b�g�A�h���X
	InetAddress mAddress;
	//�|�[�g�ԍ�
	int mPort;
};

#endif // !_INETSOCKETADDRESS_H_
