#ifndef _ACCEPTTHREAD_H_
#define _ACCEPTTHREAD_H_

#include"ServerSocket.h"
#include"Thread.h"

//サーバースレッドクラス
class ServerThread;

//アクセプトスレッドクラス
class AcceptThread:public Thread
{
public:
	//コンストラクタ
	AcceptThread(ServerThread&server);
	//デストラクタ
	~AcceptThread();
	//スレッドの実行
	void run();
	//強制終了
	void end();
	//終了しているか？
	bool isEnd();
private:
	//サーバースレッド
	ServerThread&mServer;
	//サーバーソケット
	ServerSocket mServerSocket;
	//終了フラグう
	bool mIsEnd;
};
#endif // !_ACCEPTTHREAD_H_


