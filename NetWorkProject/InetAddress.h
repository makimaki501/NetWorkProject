#ifndef _INETADDRESS_H_
#define _INETADDRESS_H_

#include<string>

//インターネットアドレスクラス
class InetAddress {
public:
	//コンストラクタ
	InetAddress(unsigned int address = InetAddress::None);
	//コンストラクタ
	InetAddress(const std::string &address);
	//ホストアドレスの取得
	std::string getHostAddress()const;
	//代入演算子オーバーロード
	InetAddress&operator=(const InetAddress&other);
	//代入演算子オーバーロード
	InetAddress&operator=(const std::string&host);
	//IPアドレスを返す
	unsigned long getAddress()const;
public:
	//無効なIPアドレス
	const static unsigned long None;
private:
	//IPアドレス
	unsigned long mIPAddress;

};

#endif // !_INETADDRESS_H_
