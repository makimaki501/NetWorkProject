#ifndef _INETADDRESS_H_
#define _INETADDRESS_H_

#include<string>

//�C���^�[�l�b�g�A�h���X�N���X
class InetAddress {
public:
	//�R���X�g���N�^
	InetAddress(unsigned int address = InetAddress::NONE);
	//�R���X�g���N�^
	InetAddress(const std::string &address);
	//�z�X�g�A�h���X�̎擾
	std::string getHostAddress()const;
	//������Z�q�I�[�o�[���[�h
	InetAddress&operator=(const InetAddress&other);
	//������Z�q�I�[�o�[���[�h
	InetAddress&operator=(const std::string&host);
	//IP�A�h���X��Ԃ�
	unsigned long getAddress()const;
public:
	//������IP�A�h���X
	const static unsigned long NONE;
private:
	//IP�A�h���X
	unsigned long mIPAddress;

};

#endif // !_INETADDRESS_H_
