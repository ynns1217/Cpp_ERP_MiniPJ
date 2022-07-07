#include "server.h"

typedef struct ARGS {
	int port; SOCKET AccSock; SOCKADDR_IN ClieAdd; f_info list;
}ARGS;
unsigned int _stdcall listen_thread(unsigned int port);
unsigned int _stdcall process_thread(ARGS *args);
int msg_trans(char* msg, ARGS* args);
void main() {

	WSADATA WSAdata;
	HANDLE _listen[5];
	WSAStartup(WINSOCK_VERSION, &WSAdata);
	for (int i = 0; i < 5; i++)
		_listen[i] = (HANDLE)_beginthreadex(NULL, 0, listen_thread, 10000 + (i * 100), 0, NULL);

	for (int i = 0; i < 5; i++)
		WaitForMultipleObjects(5, _listen, true, INFINITE);

	for (int i = 0; i < 5; i++)
		CloseHandle(_listen[i]);


	WSACleanup();
	
}
unsigned int _stdcall listen_thread(unsigned int port) {
	SOCKET ConSock;
	SOCKADDR_IN ServAdd;
	
	int len = sizeof(SOCKADDR_IN);
		ConSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (ConSock == -1) {
			printf("생성실패\n");
			return;
		}
		ServAdd.sin_family = AF_INET;
		ServAdd.sin_addr.s_addr = htonl(INADDR_ANY);
		ServAdd.sin_port = htons(port);
		if (bind(ConSock, (SOCKADDR*)&ServAdd, sizeof(ServAdd)) == -1) {
			printf("바인딩 실패\n");
			return;
		}
		if (listen(ConSock, 1024) == -1) {
			printf("리슨 실패\n");
			return;
		}

		printf("%d포트 연결 대기중...\n", port);

	while (1) {
		ARGS *args = (ARGS*)malloc(sizeof(ARGS));
		args->list.select_result_str = 0; args->list.data_line_length = 0;
		args->AccSock = accept(ConSock, (SOCKADDR*)&(args->ClieAdd), &len);
		args->port = port;

		(HANDLE)_beginthreadex(NULL, 0, process_thread, args, 0, NULL);

	}
	closesocket(ConSock);
	return 0;
}

unsigned int _stdcall process_thread(ARGS *args) {

	char msg[256] = "";
	char res_msg[256] = "";
	char buff[16];
	if (args->AccSock == -1) {
		printf("연결 실패\n");
	return;
	}
	sprintf(buff, "%d.%d.%d.%d",
		args->ClieAdd.sin_addr.s_addr & 0x00FF,
		args->ClieAdd.sin_addr.s_addr >> 8 & 0x00FF,
		args->ClieAdd.sin_addr.s_addr >> 16 & 0x00FF,
		args->ClieAdd.sin_addr.s_addr >> 24 & 0x00FF);
	printf("[%d::%s]연결 성공\n", args->port, buff);
	recv(args->AccSock, msg, sizeof(msg), 0);
	printf("[%d::%s]수신 : %s\n", args->port, buff , msg);
	{
		int res = msg_trans(msg, args);
		if (res == -1) {
			strcpy(res_msg, args->list.err_msg);
		}
		else if (res==1){
			strcpy(res_msg, args->list.select_result_str);
			file_column_free(&args->list);
		}
		else {
			strcpy(res_msg, "SUCCESS");
		}
	}
	send(args->AccSock, res_msg, sizeof(res_msg), 0);
	printf("[%d::%s]송신 : %s\n", args->port, buff, res_msg);

	closesocket(args->AccSock);
	free(args);
	return 0;
}
int msg_trans(char* msg, ARGS *args) {
	char cp_msg[256];
	char dir[50];
	char *token;
	strcpy(cp_msg, msg);
	token = strtok(cp_msg, " ");
	strcpy(dir, token);
	strcat(dir, "\\");
	token = strtok(NULL, " ");
	if (strcmp(token, "CREATE") == 0) {
		char column_list[100];
		token = strtok(NULL, " ");
		token = strtok(NULL, " ");
		strcat(dir, token);
		token = strtok(NULL, "\0");
		token = token + 1;
		token[strlen(token) - 1] = '\0';
		strcpy(column_list, token);
		if (_create(&args->list, dir, column_list) == -1) {
			return -1;
		}
		return 0;
	}
	else if (strcmp(token, "INSERT") == 0) {
		char values[100];
		token = strtok(NULL, " ");
		token = strtok(NULL, " ");
		strcat(dir, token);
		if (initalizing(&args->list, dir) == -1)
			return -1;
		token = token + strlen(token) + 1;
		token = strtok(token, "(");
		token = strtok(NULL, "\0");
		token[strlen(token) - 1] = '\0';
		strcpy(values, token);
		if (_insert(&args->list,values) == -1) {
			file_column_free(&args->list);
			return -1;
		}
		file_column_free(&args->list);
		return 0;
	}
	else if (strcmp(token, "DELETE") == 0) {
		char cond[100];
		token = strtok(NULL, " ");
		token = strtok(NULL, " ");
		strcat(dir, token);
		token = strtok(NULL, " ");
		token = strtok(NULL, "\0");
		strcpy(cond, token);

		if (initalizing(&args->list, dir) == -1)
			return -1;
		if (_delete(&args->list, cond) == -1) {
			file_column_free(&args->list);
			return -1;
		}
		file_column_free(&args->list);
		return 0;
	}
	else if (strcmp(token, "UPDATE") == 0) {
		char set[100];
		char cond[100];
		token = strtok(NULL, " ");
		strcat(dir, token);
		token = strtok(NULL, " ");
		token = strtok(NULL, " ");
		strcpy(set, token);
		token = strtok(NULL, " ");
		token = strtok(NULL, " ");
		strcpy(cond, token);

		if (initalizing(&args->list, dir) == -1)
			return -1;
		if (_update(&args->list, cond, set) == -1) {
			file_column_free(&args->list);
			return -1;
		}
		file_column_free(&args->list);
		return 0;
	}
	else if (strcmp(token, "SELECT") == 0) {
		char cond[100];
		char select[100]="\0";

		token = strtok(NULL, " ");
		while (1) {
			strcat(select, token);
			if (token[strlen(token) - 1] == ',') {
				strcat(select, " ");
				token = strtok(NULL, " ");
			}
			else {
				break;
			}
		}
		token = strtok(NULL, " ");
		token = strtok(NULL, " ");
		strcat(dir, token);
		token = strtok(NULL, " ");
		token = strtok(NULL, " ");
		strcpy(cond, token);

		if (initalizing(&args->list, dir) == -1)
			return -1;
		if (_select(&args->list, cond, select) == -1) {
			file_column_free(&args->list);
			return -1;
		}
		return 1;
	}
	else {
		strcpy(args->list.err_msg, "QUERY ERROR");
		return -1;
	}
}