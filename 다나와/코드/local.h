#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _INT 1
#define _FLOAT 2
#define _DOUBLE 3
#define _CHAR 4
#define _VARCHAR 5
#define ERR_MSG_SIZE 51

#define MENU_LENGTH 21
#define DATE_LENGTH 11

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

//로컬

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

//서버

typedef struct result_column {
	char* name;
	int type;

	int* _int_data;
	float* _float_data;
	double* _double_data;
	char* _char_data;
	char** _string_data;
	struct result_column* next;

}result;

//클라이언트


static char pad = 255;
static char pad_seprator[2] = { 255,'\0' };
static char* _file_location;
char err_msg[ERR_MSG_SIZE];
char* select_result_str;   //로컬로 빠짐 (서버)
//로컬

int initalizing(char* file_name);
int add_column(column tmp); 
int _create(char* file_name, char* column_list);
int _insert(char* values);
int _delete(char* conditional);
int _update(char* conditional, char* set);
int _select(char* conditional, char* select, char** result);
void print_column();
int print_data();
void sdts_free(sdts* node);
void file_column_free();

//서버

int recv_result(result** result_head, char* receive);
result* find_result(result* result_head, char* column_name);
void result_print(result* result_head, int result_count);
int int_is_null(int _int_data);
int float_is_null(float _float_data);
int double_is_null(double _double_data);
int char_is_null(char _char_data);
int string_is_null(char* _string_data);
void result_free(result* node, int result_count);

//클라이언트