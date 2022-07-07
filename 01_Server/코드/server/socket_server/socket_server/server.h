#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _INT 1
#define _FLOAT 2
#define _DOUBLE 3
#define _CHAR 4
#define _VARCHAR 5
#define FILE_LOC_LENGTH 51
#define ERR_MSG_SIZE 51
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <WinSock2.h>
#include <Windows.h>
#include <process.h>
#include <stdbool.h>

#pragma comment(lib, "wsock32.lib")

typedef struct column {
	char* name;
	unsigned int length;
	int type;
	int start_index;
	struct column* next;
}column;
typedef struct search_data_to_string {
	char* str;
	struct search_data_to_string* next;
}sdts;

typedef struct file_info {
	column* head;
	column* tail;
	int data_start_index;
	int data_end_index;
	int data_line_length;
	FILE* F;
	char _file_location[FILE_LOC_LENGTH];
	char err_msg[ERR_MSG_SIZE];
	char* select_result_str;
}f_info;

static char pad = 255;
static char pad_seprator[2] = { 255,'\0' };


int initalizing(f_info *list, char* file_name);
int add_column(f_info *list, column tmp);
int _create(f_info *list, char* file_name, char* column_list);
int _insert(f_info *list, char* values);
int _delete(f_info *list, char* conditional);
int _update(f_info *list, char* conditional, char* set);
int _select(f_info *list, char* conditional, char* select);
void print_column(f_info *list);
int print_data(f_info *list);
void sdts_free(sdts* node);
void file_column_free(f_info *list);
