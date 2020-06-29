//#include<windows.h>
//#include<winsock2.h>
//#include<sstream>
//#include<string>
//
//#include"resource2.h"
//#include"ChatClientThread.h"
//
//#pragma comment(lib,"WSock32.lib")
//
////ダイアログボックスの処理
//BOOL CALLBACK MyDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
//{
//	//チャットクアイアント
//	static ChatClientThread chatClient(11);
//	//タイマのID
//	const static UINT ID_TIMER = 1;
//	//ポート番号
//	int port;
//
//	switch (msg)
//	{
//	case WM_INITDIALOG:          //ダイアログの初期化メッセージ
//		//メッセージ表示テキストボックスの初期化
//		SendMessage(
//			GetDlgItem(hDlg, IDC_EDIT_MESSAGE),
//			EM_LIMITTEXT,
//			(WPARAM)64 * 1024,
//			0
//		);
//		//送信メッセ―ジテキストボックス初期化
//		SendMessage(
//			GetDlgItem(hDlg, IDC_EDIT_SEND),
//			EM_LIMITTEXT,
//			(WPARAM)1024,
//			0
//		);
//		//200ミリ秒毎のタイマイベントを設定する
//		SetTimer(hDlg, ID_TIMER, 200, NULL);
//		break;
//
//
//	case WM_COMMAND:            //ボタンが押された場合の処理
//		switch (LOWORD(wp)) {
//		case IDOK:
//			break;
//
//		case IDCANCEL:               //キャンセルボタンが押された
//
//		case IDC_BUTTON_END:         //終了ボタンが押された
//			//タイマを停止する
//			KillTimer(hDlg, ID_TIMER);
//			//サーバーに終了メッセージを送信
//			chatClient.sendMessage("c_end");
//			//チャットクライアントの強制終了
//			chatClient.end();
//			//ダイアログボックスを閉じる
//			EndDialog(hDlg, LOWORD(wp));
//			break;
//
//		case IDC_BUTTON_CONNECT:     //接続ボタンが押された
//			//アドレスを取得
//			char address[256];
//			GetDlgItemText(hDlg, IDC_EDIT_SERVER, address, sizeof(address));
//			//ポート番号を取得
//			int flag;
//			port = GetDlgItemInt(hDlg, IDC_EDIT_PORT, &flag, FALSE);
//			//ユーザー名を取得
//			char name[256];
//			GetDlgItemText(hDlg, IDC_EDIT_ID, name, sizeof(name));
//			//ユーザー名を設定する
//			chatClient.setName(name);
//			//サーバーのアドレスを設定する
//			chatClient.setServerAddress(InetSocketAddress(std::string(address), port));
//			//チャットクライアントを設定
//			chatClient.start();
//			//接続ボタンを押せなくなる
//			EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_CONNECT), FALSE);
//			break;
//
//		case IDC_BUTTON_SEND:        //送信ボタンが押された
//			//送信メッセージを取得
//			char send_message[1024];
//			GetDlgItemText(hDlg, IDC_EDIT_SEND, send_message, sizeof(send_message));
//			//サーバーにメッセージを送信
//			chatClient.sendMessage(send_message);
//			break;
//		}
//
//	case WM_TIMER:
//		//メッセージ用文字列ストリーム
//		std::stringstream message;
//		//メッセージバッファの内容を文字列ストリームに出力
//		chatClient.printMessage(message);
//		//メッセージを表示する
//		SetDlgItemText(hDlg, IDC_EDIT_MESSAGE, message.str().c_str());
//		break;
//	}
//
//	return FALSE;
//}
//
////ウィンドウのメイン関数
//int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPreInst, LPSTR lpsCmdLine, int nCmdShow)
//{
//	////WinSockの初期化
//	//WSADATA wsaData;
//	//WSAStartup(MAKEWORD(1, 1), &wsaData);
//
//	////ダイアログボックスを開く
//	//DialogBox(hCurInst, (LPCWSTR)IDD_CLIENT, NULL, (DLGPROC)MyDlgProc);
//
//	////WinSock終了処理
//	//WSACleanup();
//
//	return 0;
//}
