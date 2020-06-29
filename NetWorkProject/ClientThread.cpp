#include "ClientThread.h"
#include"ServerThread.h"
#include"Socket.h"

//コンストラクタ
ClientThread::ClientThread(ServerThread & server, Socket * socket, const std::string&name) :
	mServer(server),
	mSocket(socket),
	mName(name),
	mIsEnd(false)
{
}

//デストラクタ
ClientThread::~ClientThread()
{
	//強制終了
	end();
}

//スレッドの起動
void ClientThread::run()
{
	//スレッドの開始
	mIsEnd = false;
	try {
		//入室したことを知らせる
		mServer.sendClient(mName + "さんが入室しました");
		//クライアントからのメッセージを処理する
		while (mIsEnd == false) {
			//クライアントからのデータを受信
			std::string message = mSocket->receive();
			//クライアントの切断要求をチェック
			if (message == "end") {
				break;
			}
			//ユーザー名を付加して、クライアントにメッセージを送信
			mServer.sendClient(mName + "：" + message);
			//他のスレッドに制御を渡す
			Thread::sleep(0);
		}
		//退室したことを知らせる
		mServer.sendClient(mName + "さんが退室しました");
	}
	catch (SocketException&) {
	}
	//終了フラグの設定
	mIsEnd = true;
}

void ClientThread::send(const std::string & message)
{
	mSocket->send(message);
}

//強制終了
void ClientThread::end()
{
	//終了フラグの設定
	mIsEnd = true;
	//ソケットを閉じる
	mSocket->close();
	//スレッドの終了を待つ
	join();
}

//スレッドが終了しているか調べる
bool ClientThread::isEnd()
{
	return mIsEnd;
}
