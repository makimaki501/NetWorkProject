////#define _CRT_SECURE_NO_WARNINGS
//#include<winsock.h>
//#include<stdio.h>
//#include<string.h>
//#include<stdlib.h>
//
//#pragma comment (lib,"WSock32.lib")
//
////�`���b�gprogram�@�T�[�o�[�֐�
//void ChatServer(void) {
//	SOCKET listen_s;
//	SOCKET s;
//	SOCKADDR_IN saddr;
//	SOCKADDR_IN from;
//	int fromlen;
//	u_short uport;
//
//	//�|�[�g�ԍ��̓���
//	printf("�g�p����|�[�g�ԍ�--��");
//	scanf("%hd", &uport);
//	fflush(stdin);
//
//	//���X���\�P�b�g���I�[�v��
//	listen_s = socket(AF_INET, SOCK_STREAM, 0);
//	if (listen_s == INVALID_SOCKET) {
//		printf("���X���\�P�b�g�I�[�v���G���[");
//		WSACleanup();
//		return;
//	}
//	printf("���X���\�P�b�g���I�[�v�����܂���\n");
//
//	//�\�P�b�g�ɖ��O��t����
//	memset(&saddr, 0, sizeof(SOCKADDR_IN));
//	saddr.sin_family = AF_INET;
//	saddr.sin_port = htons(uport);
//	saddr.sin_addr.s_addr = INADDR_ANY;
//	if (bind(listen_s, (struct sockaddr*)&saddr, sizeof(saddr)) == SOCKET_ERROR) {
//		printf("binderror");
//		closesocket(listen_s);
//		return;
//	}
//	printf("bind�����ł�");
//
//	//�N���C�A���g����̐ڑ��҂��̏�Ԃɂ���
//	if (listen(listen_s, 0) == SOCKET_ERROR) {
//		printf("listen�G���[\n");
//		closesocket(listen_s);
//		return;
//	}
//	printf("listen�����ł�\n");
//
//	//�ڑ���ҋ@����
//	printf("accept�őҋ@���܂�\n");
//	fromlen = (int)sizeof(from);
//	s = accept(listen_s, (SOCKADDR*)&from, &fromlen);
//	if (s == INVALID_SOCKET) {
//		printf("accept�G���[\n");
//		closesocket(listen_s);
//		return;
//	}
//	printf("%s���ڑ����Ă��܂���\n", inet_ntoa(from.sin_addr));
//	printf("accept�֐������ł�\n");
//
//	//���X���\�P�b�g�͂����s�v
//	closesocket(listen_s);
//
//	//��b�J�n
//	printf("��b�J�n�ł�\n");
//	while (1)
//	{
//		//����M�o�b�t�@
//		int nRcv;
//		char szBuf[1024];
//
//		printf("��M��҂��Ă��܂�\n");
//
//		//�f�[�^�̓ǂݏo��
//		nRcv = recv(s, szBuf, sizeof(szBuf) - 1, 0);
//		if (nRcv == SOCKET_ERROR) {
//			printf("recv�G���[�ł�\n");
//			break;
//		}
//		szBuf[nRcv] = '\0';
//
//		//�ڑ��ؒf�̃`�F�b�N
//		if (strcmp(szBuf, "c_end") == 0) {
//			printf("�N���C�A���g���ڑ���ؒf���܂���\n");
//			break;
//		}
//
//		//��M���b�Z�[�W�̕\��
//		printf("��M-->%s&n", szBuf);
//
//		//���M���b�Z�[�W�̓���
//		printf("���M-->");
//		scanf("%s", szBuf);
//		fflush(stdin);
//
//		//���M���b�Z�[�W�𑗂�
//		send(s, szBuf, (int)strlen(szBuf), 0);
//
//		//�T�[�o�[������ؒf����
//		if (strcmp(szBuf, "s_end") == 0) {
//			break;
//		}
//	}
//	//�\�P�b�g�����
//	closesocket(s);
//}
//
////�`���b�g�v���O���� �N���C�A���g�J�n
//void ChatClient() {
//	SOCKET s;
//	SOCKADDR_IN saddr;
//	u_short uport;
//	char szServer[1024];
//	HOSTENT*lpHost;
//	unsigned int addr;
//
//	//�|�[�g�ԍ��̓���
//	printf("�g�p����|�[�g�ԍ�-->");
//	scanf("%hd", &uport);
//	fflush(stdin);
//
//	//�T�[�o���܂��̓T�[�o��IP�A�h���X�����
//	printf("�T�[�o��-->");
//	scanf("%s", szServer);
//	fflush(stdin);
//
//	//�\�P�b�g���I�[�v��
//	s = socket(AF_INET, SOCK_STREAM, 0);
//	if (s == INVALID_SOCKET) {
//		printf("�\�P�b�g�I�[�v���G���[\n");
//		return;
//	}
//
//	//�T�[�o�[�𖼑O�Ŏ擾����
//	lpHost = gethostbyname(szServer);
//	if (lpHost == NULL) {
//		//�T�[�o�[��IP�A�h���X�Ŏ擾����
//		addr = inet_addr(szServer);
//		lpHost = gethostbyaddr((char*)&addr, 4, AF_INET);
//	}
//	if (lpHost == NULL) {
//		printf("Host��������܂���\n");
//		closesocket(s);
//		return;
//	}
//
//	//�N���C�A���g�\�P�b�g���T�[�o�[�ɐڑ�
//	memset(&saddr, 0, sizeof(SOCKADDR_IN));
//	saddr.sin_family = lpHost->h_addrtype;
//	saddr.sin_port = htons(uport);
//	saddr.sin_addr.s_addr = *((u_long*)lpHost->h_addr);
//
//	if (connect(s, (SOCKADDR*)&saddr, sizeof(saddr)) == SOCKET_ERROR) {
//		printf("�T�[�o�[�Ɛڑ��ł��܂���ł���\n");
//		closesocket(s);
//		return;
//	}
//	printf("�T�[�o�[�ɐڑ��ł��܂���\n");
//
//	while (1)
//	{
//		//����M�o�b�t�@
//		int nRcv;
//		char szBuf[1024];
//
//		//���M�f�[�^����
//		printf("���M-->");
//		scanf("%s", szBuf);
//		fflush(stdin);
//
//		//�f�[�^�𑗐M����	
//		send(s, szBuf, (int)strlen(szBuf), 0);
//
//		//�ڑ���ؒf���邩�H
//		if (strcmp(szBuf, "c_end") == 0) {
//			break;
//		}
//
//		//�T�[�o�[����̃f�[�^����M����
//		nRcv = recv(s, szBuf, sizeof(szBuf) - 1, 0);
//		if (nRcv == SOCKET_ERROR) {
//			printf("��M�G���[\n");
//			break;
//		}
//		szBuf[nRcv] = '\0';
//
//		if (strcmp(szBuf, "s_end") == 0) {
//			printf("�T�[�o�[���ڑ���ؒf���܂���\n");
//			break;
//		}
//		//��M�f�[�^�̕\��
//		printf("��M-->%s&n", szBuf);
//	}
//
//	//�\�P�b�g�����
//	closesocket(s);
//}
//
//////�`���b�g�v���O�����@���C���֐�
////void main(void) {
////	WSADATA wsaData;
////	int mode;
////
////	//WinSock�̏�����
////	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
////		//�������G���[
////		printf("Winsock�̏������Ɏ��s���܂���\n");
////		return;
////	}
////
////	//�T�[�o�[���H�N���C�A���g���H
////	printf("�T�[�o�[�Ȃ�0����́@�N���C�A���g�Ȃ�1�����-->");
////	scanf("%d",&mode);
////	fflush(stdin);
////
////	if (mode == 0) {
////		//�T�[�o�[�Ƃ��ċN��
////		ChatServer();
////	}
////	else {
////		//�N���C�A���g�Ƃ��ċN��
////		ChatClient();
////	}
////
////	//Winsock�̏I������
////	WSACleanup();
////}