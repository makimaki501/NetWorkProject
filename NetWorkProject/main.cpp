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
////�_�C�A���O�{�b�N�X�̏���
//BOOL CALLBACK MyDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
//{
//	//�`���b�g�N�A�C�A���g
//	static ChatClientThread chatClient(11);
//	//�^�C�}��ID
//	const static UINT ID_TIMER = 1;
//	//�|�[�g�ԍ�
//	int port;
//
//	switch (msg)
//	{
//	case WM_INITDIALOG:          //�_�C�A���O�̏��������b�Z�[�W
//		//���b�Z�[�W�\���e�L�X�g�{�b�N�X�̏�����
//		SendMessage(
//			GetDlgItem(hDlg, IDC_EDIT_MESSAGE),
//			EM_LIMITTEXT,
//			(WPARAM)64 * 1024,
//			0
//		);
//		//���M���b�Z�\�W�e�L�X�g�{�b�N�X������
//		SendMessage(
//			GetDlgItem(hDlg, IDC_EDIT_SEND),
//			EM_LIMITTEXT,
//			(WPARAM)1024,
//			0
//		);
//		//200�~���b���̃^�C�}�C�x���g��ݒ肷��
//		SetTimer(hDlg, ID_TIMER, 200, NULL);
//		break;
//
//
//	case WM_COMMAND:            //�{�^���������ꂽ�ꍇ�̏���
//		switch (LOWORD(wp)) {
//		case IDOK:
//			break;
//
//		case IDCANCEL:               //�L�����Z���{�^���������ꂽ
//
//		case IDC_BUTTON_END:         //�I���{�^���������ꂽ
//			//�^�C�}���~����
//			KillTimer(hDlg, ID_TIMER);
//			//�T�[�o�[�ɏI�����b�Z�[�W�𑗐M
//			chatClient.sendMessage("c_end");
//			//�`���b�g�N���C�A���g�̋����I��
//			chatClient.end();
//			//�_�C�A���O�{�b�N�X�����
//			EndDialog(hDlg, LOWORD(wp));
//			break;
//
//		case IDC_BUTTON_CONNECT:     //�ڑ��{�^���������ꂽ
//			//�A�h���X���擾
//			char address[256];
//			GetDlgItemText(hDlg, IDC_EDIT_SERVER, address, sizeof(address));
//			//�|�[�g�ԍ����擾
//			int flag;
//			port = GetDlgItemInt(hDlg, IDC_EDIT_PORT, &flag, FALSE);
//			//���[�U�[�����擾
//			char name[256];
//			GetDlgItemText(hDlg, IDC_EDIT_ID, name, sizeof(name));
//			//���[�U�[����ݒ肷��
//			chatClient.setName(name);
//			//�T�[�o�[�̃A�h���X��ݒ肷��
//			chatClient.setServerAddress(InetSocketAddress(std::string(address), port));
//			//�`���b�g�N���C�A���g��ݒ�
//			chatClient.start();
//			//�ڑ��{�^���������Ȃ��Ȃ�
//			EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_CONNECT), FALSE);
//			break;
//
//		case IDC_BUTTON_SEND:        //���M�{�^���������ꂽ
//			//���M���b�Z�[�W���擾
//			char send_message[1024];
//			GetDlgItemText(hDlg, IDC_EDIT_SEND, send_message, sizeof(send_message));
//			//�T�[�o�[�Ƀ��b�Z�[�W�𑗐M
//			chatClient.sendMessage(send_message);
//			break;
//		}
//
//	case WM_TIMER:
//		//���b�Z�[�W�p������X�g���[��
//		std::stringstream message;
//		//���b�Z�[�W�o�b�t�@�̓��e�𕶎���X�g���[���ɏo��
//		chatClient.printMessage(message);
//		//���b�Z�[�W��\������
//		SetDlgItemText(hDlg, IDC_EDIT_MESSAGE, message.str().c_str());
//		break;
//	}
//
//	return FALSE;
//}
//
////�E�B���h�E�̃��C���֐�
//int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPreInst, LPSTR lpsCmdLine, int nCmdShow)
//{
//	////WinSock�̏�����
//	//WSADATA wsaData;
//	//WSAStartup(MAKEWORD(1, 1), &wsaData);
//
//	////�_�C�A���O�{�b�N�X���J��
//	//DialogBox(hCurInst, (LPCWSTR)IDD_CLIENT, NULL, (DLGPROC)MyDlgProc);
//
//	////WinSock�I������
//	//WSACleanup();
//
//	return 0;
//}
