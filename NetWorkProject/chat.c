//#define _CRT_SECURE_NO_WARNINGS
#include<winsock.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#pragma comment (lib,"WSock32.lib")

//チャットprogram　サーバー関数
void ChatServer(void) {
	SOCKET listen_s;
	SOCKET s;
	SOCKADDR_IN saddr;
	SOCKADDR_IN from;
	int fromlen;
	u_short uport;

	//ポート番号の入力
	printf("使用するポート番号--＞");
	scanf("%hd", &uport);
	fflush(stdin);

	//リスンソケットをオープン
	listen_s = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_s == INVALID_SOCKET) {
		printf("リスンソケットオープンエラー");
		WSACleanup();
		return;
	}
	printf("リスンソケットをオープンしました\n");

	//ソケットに名前を付ける
	memset(&saddr, 0, sizeof(SOCKADDR_IN));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(uport);
	saddr.sin_addr.s_addr = INADDR_ANY;
	if (bind(listen_s, (struct sockaddr*)&saddr, sizeof(saddr)) == SOCKET_ERROR) {
		printf("binderror");
		closesocket(listen_s);
		return;
	}
	printf("bind成功です");

	//クライアントからの接続待ちの状態にする
	if (listen(listen_s, 0) == SOCKET_ERROR) {
		printf("listenエラー\n");
		closesocket(listen_s);
		return;
	}
	printf("listen成功です\n");

	//接続を待機する
	printf("acceptで待機します\n");
	fromlen = (int)sizeof(from);
	s = accept(listen_s, (SOCKADDR*)&from, &fromlen);
	if (s == INVALID_SOCKET) {
		printf("acceptエラー\n");
		closesocket(listen_s);
		return;
	}
	printf("%sが接続してきました\n", inet_ntoa(from.sin_addr));
	printf("accept関数成功です\n");

	//リスンソケットはもう不要
	closesocket(listen_s);

	//会話開始
	printf("会話開始です\n");
	while (1)
	{
		//送受信バッファ
		int nRcv;
		char szBuf[1024];

		printf("受信を待っています\n");

		//データの読み出し
		nRcv = recv(s, szBuf, sizeof(szBuf) - 1, 0);
		if (nRcv == SOCKET_ERROR) {
			printf("recvエラーです\n");
			break;
		}
		szBuf[nRcv] = '\0';

		//接続切断のチェック
		if (strcmp(szBuf, "c_end") == 0) {
			printf("クライアントが接続を切断しました\n");
			break;
		}

		//受信メッセージの表示
		printf("受信-->%s&n", szBuf);

		//送信メッセージの入力
		printf("送信-->");
		scanf("%s", szBuf);
		fflush(stdin);

		//送信メッセージを送る
		send(s, szBuf, (int)strlen(szBuf), 0);

		//サーバー側から切断する
		if (strcmp(szBuf, "s_end") == 0) {
			break;
		}
	}
	//ソケットを閉じる
	closesocket(s);
}

//チャットプログラム クライアント開始
void ChatClient() {
	SOCKET s;
	SOCKADDR_IN saddr;
	u_short uport;
	char szServer[1024];
	HOSTENT*lpHost;
	unsigned int addr;

	//ポート番号の入力
	printf("使用するポート番号-->");
	scanf("%hd", &uport);
	fflush(stdin);

	//サーバ名またはサーバのIPアドレスを入力
	printf("サーバ名-->");
	scanf("%s", szServer);
	fflush(stdin);

	//ソケットをオープン
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET) {
		printf("ソケットオープンエラー\n");
		return;
	}

	//サーバーを名前で取得する
	lpHost = gethostbyname(szServer);
	if (lpHost == NULL) {
		//サーバーをIPアドレスで取得する
		addr = inet_addr(szServer);
		lpHost = gethostbyaddr((char*)&addr, 4, AF_INET);
	}
	if (lpHost == NULL) {
		printf("Hostが見つかりません\n");
		closesocket(s);
		return;
	}

	//クライアントソケットをサーバーに接続
	memset(&saddr, 0, sizeof(SOCKADDR_IN));
	saddr.sin_family = lpHost->h_addrtype;
	saddr.sin_port = htons(uport);
	saddr.sin_addr.s_addr = *((u_long*)lpHost->h_addr);

	if (connect(s, (SOCKADDR*)&saddr, sizeof(saddr)) == SOCKET_ERROR) {
		printf("サーバーと接続できませんでした\n");
		closesocket(s);
		return;
	}
	printf("サーバーに接続できました\n");

	while (1)
	{
		//送受信バッファ
		int nRcv;
		char szBuf[1024];

		//送信データ入力
		printf("送信-->");
		scanf("%s", szBuf);
		fflush(stdin);

		//データを送信する	
		send(s, szBuf, (int)strlen(szBuf), 0);

		//接続を切断するか？
		if (strcmp(szBuf, "c_end") == 0) {
			break;
		}

		//サーバーからのデータを受信する
		nRcv = recv(s, szBuf, sizeof(szBuf) - 1, 0);
		if (nRcv == SOCKET_ERROR) {
			printf("受信エラー\n");
			break;
		}
		szBuf[nRcv] = '\0';

		if (strcmp(szBuf, "s_end") == 0) {
			printf("サーバーが接続を切断しました\n");
			break;
		}
		//受信データの表示
		printf("受信-->%s&n", szBuf);
	}

	//ソケットを閉じる
	closesocket(s);
}

////チャットプログラム　メイン関数
//void main(void) {
//	WSADATA wsaData;
//	int mode;
//
//	//WinSockの初期化
//	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
//		//初期化エラー
//		printf("Winsockの初期化に失敗しました\n");
//		return;
//	}
//
//	//サーバーか？クライアントか？
//	printf("サーバーなら0を入力　クライアントなら1を入力-->");
//	scanf("%d",&mode);
//	fflush(stdin);
//
//	if (mode == 0) {
//		//サーバーとして起動
//		ChatServer();
//	}
//	else {
//		//クライアントとして起動
//		ChatClient();
//	}
//
//	//Winsockの終了処理
//	WSACleanup();
//}