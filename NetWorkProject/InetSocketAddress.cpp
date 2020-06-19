#include "InetSocketAddress.h"

//�R���X�g���N�^
InetSocketAddress::InetSocketAddress(const InetAddress & address, int port):
	mAddress(address),
	mPort(port)
{
}

//�C���^�[�l�b�g�A�h���X�̎擾
const InetAddress & InetSocketAddress::getInetAddress() const
{
	return mAddress;
}

//�|�[�g�ԍ��̎擾
int InetSocketAddress::getPort() const
{
	return mPort;
}
