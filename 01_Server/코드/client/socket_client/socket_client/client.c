#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <WinSock2.h>
#include "client.h"

#pragma comment(lib, "wsock32.lib")
void d_initalizing(char* _ip_addr, char* _dir);
void d_close();
int _send(unsigned int port, char* msg, unsigned int is_select);
int query(char* msg);
void main() {
	d_initalizing("127.0.0.1", "DB");
	//query("CREATE TABLE A (COLUMN1 INT COLUMN2 VARCHAR(20))");
	//query("INSERT INTO A VALUES (12, 'aaa')");
	//query("UPDATE A SET COLUMN2='수정' WHERE COLUMN1=10");
	//query("DELETE FROM A WHERE COLUMN2='수정'");
	//query("SELECT COLUMN1, COLUMN2 FROM A WHERE *");
	d_close();
}
void d_initalizing(char* _ip_addr, char* _dir) {
	strcpy(ip_addr, _ip_addr);
	strcpy(dir, _dir);
}
void d_close() {
	ip_addr[0] = '\0';
	dir[0] = '\0';
}
int query(char* msg) {
	char f_msg[256];
	char check_select[7];
	WSADATA WSAdata;
	
	if (dir == NULL || dir[0] == '\0' || ip_addr == NULL || ip_addr[0] == '\0') {
		printf("MUST INIT FIRST\n");
		return;
	}

	strncpy(check_select, f_msg, 6);
	check_select[6] = '\0';
	WSAStartup(WINSOCK_VERSION, &WSAdata);
	{
		int i;
		if (strcmp(check_select, "INSERT") == 0) {
			for (i = 0; i < 5; i++) {
				if (_send(10000 + i * 100, msg, 1) == 0)
					break;
			}
		}
		else {
			for (i = 0; i < 5; i++) {
				if (_send(10000 + i * 100, msg, 0) == 0)
					break;
			}
		}
		if (i == 5) {
			printf("CONNECTION FAILED\n");

			WSACleanup();
			return -1;
		}
		else {

			WSACleanup();
			return 0;
		}
	}
}

int _send(unsigned int port, char *msg, unsigned int is_select) {
	SOCKET ConSock;
	SOCKADDR_IN ServAdd;
	char f_msg[256] = "";
	char recv_msg[256] = "";
	ConSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ConSock == -1) {

		closesocket(ConSock);
		printf("생성 실패");
		return -1;
	}

	ServAdd.sin_family = AF_INET;
	ServAdd.sin_addr.s_addr = inet_addr(ip_addr);
	ServAdd.sin_port = htons(port);

	if (connect(ConSock, (SOCKADDR*)&ServAdd, sizeof(ServAdd)) == -1) {

		closesocket(ConSock);
		printf("연결 실패\n");
		return -1;
	}
	sprintf(f_msg, "%s %s", dir, msg);

	send(ConSock, f_msg, sizeof(f_msg), 0);
	recv(ConSock, recv_msg, sizeof(recv_msg), 0);
	if (is_select == 0) {
		if (strcmp(recv_msg, "SUCCESS") != 0) {
			closesocket(ConSock);
			printf("%s\n", recv_msg);
			return 0;
		}
	}
	else {
		if (recv_msg[0] == '-1') {
			closesocket(ConSock);
			printf("%s\n", recv_msg);
			return 0;
		}
		else {
			select_result_str = (char*)malloc(strlen(recv_msg) + 1);
			strcpy(select_result_str, recv_msg);
		}
	}
	printf("SUCCESS\n");
	closesocket(ConSock);

	return 0;
}