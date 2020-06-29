#ifndef _CLIENTTHREAD_H_
#define _CLIENTTHREAD_H_

#include"Thread.h"
#include<string>
#include<memory>

//サーバースレッドクラス
class ServerThread;

//ソケットクラス
class Socket;

//クライアントスレッドクラス
class ClientThread :public Thread
{
public:
	ClientThread(ServerThread&server, Socket*socket, const std::string&name);
	//デストラクタ
	~ClientThread();
	//スレッドの起動
	void run();
	//メッセージを送信
	void send(const std::string&message);
	//強制終了
	void end();
	//スレッドが終了しているか？
	bool isEnd();
private:
	//サーバースレッド
	ServerThread&mServer;
	//クライアント用の送受信ソケット
	std::auto_ptr<Socket>mSocket;
	//ユーザー名
	std::string mName;
	//終了フラグ
	bool mIsEnd;
};
#endif // !_CLIENTTHREAD_H_


