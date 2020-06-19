#include<winsock2.h>
#include<stdio.h>
#include<string>
#include<stdlib.h>
#include<memory>
#include<iostream>

#include"Socket.h"
#include"ServerSocket.h"

#pragma comment (lib,"WSock32.lib")

//Socket*mSocket;

//チャット　サーバー関数
void ChatServer() {
	ServerSocket serverSocket;
	std::auto_ptr<Socket>socket;
	u_short port;
	//auto serverSocket = std::make_unique<ServerSocket>(port);

	//ポート番号の入力
	std::cout << "使用するポート番号-->";
	std::cin >> port;
	fflush(stdin);

	//ソケットをバインドして、リスン状態にする
	serverSocket.bind(port);
	std::cout << "バインドに成功しました" << std::endl;

	//接続を待機する
	socket = serverSocket.accept();
	std::cout << "接続の受け入れに成功しました\n";

	//serverSocket.close();

	//会話開始
	std::cout << "会話開始です\n";
	while (1) {
		std::string str;

		std::cout << "受信を待っています\n";
		str = socket->receive();


		//受信メッセージの表示
		std::cout << "受信-->" << str << std::endl;

		//送信メッセージの入力
		std::cout << "送信-->";
		std::cin >> str;
		fflush(stdin);

		//送信メッセ―ジを送る
		socket->send(str);

		//サーバー側から切断する
		if (!socket->isConnected()) {
			break;
		}

	}
	socket->close();
}

void ChatClient() {
	u_short port;
	std::auto_ptr<Socket>socket;
	//Socket *socket;
	std::string server;
	//HOSTENT*lpHost;


	//ポート番号の入力
	std::cout << "使用するポート番号-->";
	std::cin >> port;
	fflush(stdin);

	std::cout << "接続先のIPアドレスを入力してください-->";
	std::cin >> server;

	std::cout << "接続を開始します。" << std::endl;
	socket->connect(server, port);


	std::cout << "接続に成功しました。" << std::endl;

	std::cout << "会話を開始します。" << std::endl;

	while (1) {
		//送受信バッファ
		std::string szBuf;

		//送信メッセージの入力
		std::cout << "送信-->";
		std::cin >> szBuf;

		//メッセージの送信
		socket->send(szBuf);

		szBuf = socket->receive();
		std::cout << "受信-->" << server << std::endl;

	}

}
//
//int main() {
//	WSADATA wsaData;
//	int mode;
//
//	//WinSockの初期化
//	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
//		//初期化エラー
//		std::cout << "Winsockの初期化に失敗しました" << std::endl;
//		return 0;
//	}
//
//	//サーバーか？クライアントか？
//	std::cout << "サーバーなら0を入力 クライアントなら1を入力-->";
//	std::cin >> mode;
//
//	if (mode == 0) {
//		//サーバーとして起動
//		ChatServer();
//	}
//	else {
//		ChatClient();
//	}
//
//	//Winsockの終了処理
//	WSACleanup();
//}