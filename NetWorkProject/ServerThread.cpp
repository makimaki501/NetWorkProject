#include "ServerThread.h"
#include "ClientThread.h"
#include "AcceptThread.h"
#include "Socket.h"
#include<boost/mem_fn.hpp>
#include<boost/bind.hpp>

//コンストラクタ
ServerThread::ServerThread(int port) :
	mPort(port),
	mIsEnd(false)
{
}

//デストラクタ
ServerThread::~ServerThread()
{
	//強制終了
	end();
}

//スレッドの実行
void ServerThread::run()
{
	//スレッドを開始
	mIsEnd = false;
	//アクセプトスレッドを作成する
	std::auto_ptr<AcceptThread>acceptor(new AcceptThread(*this));
	//受信スレッドを起動
	acceptor->start();
	//終了するまで繰り返し
	while (isEnd() == false)
	{
		//終了したクライアントを削除
		removeClient();
		//他のスレッドに制御を渡す
		Thread::sleep(0);
	}
	//アクセプトスレッドを強制終了
	acceptor->end();
	//クライアントを全て消去
	clearClient();
	//終了フラグを設定
	mIsEnd = true;
}

//クライアントの追加
void ServerThread::addClient(ClientThread * client)
{
	CriticalSection::Lock guard(mClientContainerLook);
	//クライアントを登録
	mClientContainer.push_back(ClientThreadPtr(client));

	//クライアントをスレッド起動
	client->start();

}

void ServerThread::removeClient()
{
	CriticalSection::Lock guard(mClientContainerLook);
	//終了しているクライアントを削除
	mClientContainer.remove_if(boost::mem_fn(&ClientThread::isEnd));
}

void ServerThread::clearClient()
{
}

//強制終了
void ServerThread::end()
{
	//終了フラグを設定する
	mIsEnd = true;
	//スレッドの終了を待つ
	join();
}

//ポート番号の取得
int ServerThread::getPort() const
{
	return mPort;
}

bool ServerThread::isEnd()
{
	return false;
}

//クライアントにメッセージを送信
void ServerThread::sendClient(const std::string & message)
{
	CriticalSection::Lock guard(mClientContainerLook);

	//全クライアントにメッセージを送る
	std::for_each(
		mClientContainer.begin(),
		mClientContainer.end(),
		boost::bind(boost::mem_fn(&ClientThread::send), _1, message)
	);
}
