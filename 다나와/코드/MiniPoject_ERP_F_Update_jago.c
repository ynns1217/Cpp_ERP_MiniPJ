#include "local.h"
#include"MiniProject_ERP_1struct.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

void Update_jago(int number)
{
	result* _result;
	result* find;
	int result_count;
	char Select_WH[10];
	int a[6] = { 0 };
	char temp_int[10];

	if (initalizing("Jaego") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	//char item_number[100] = "num_item='CP10'";

	if (_select("*", "chulgo_item", &select_result_str) == -1) {	// 만든 양식을 토대로 창고목록에서 내부 칼럼정보를 선택해 받아옴
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if ((result_count = recv_result(&_result, select_result_str)) == -1) {		// select로 받아온 정보를 _result 포인트 구조체에 멤버로 저장함
		printf("%s\n", err_msg);												// 구조체양식은 연결리스트

		file_column_free();
		return -1;
	}

	// 이후 출고값
	a[0] = ((*(_result->_int_data)) + number);									//	CP10
	a[1] = ((*(_result->next->_int_data)) + number);							//	HR10
	a[2] = ((*(_result->next->next->_int_data)) + number);						//	KE10
	a[3] = ((*(_result->next->next->next->_int_data)) + number);				//	MB10
	a[4] = ((*(_result->next->next->next->next->_int_data)) + number);			//	MO10
	a[5] = ((*(_result->next->next->next->next->next->_int_data)) + number);	//	CA10
	 


	char update_jago_from_ibgo[100] = "chulgo_item=";
	itoa(a[0], temp_int, 10);
	strcat(update_jago_from_ibgo, temp_int);
	

	if (_update("chulgo_item='CP10'", update_jago_from_ibgo) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_update("chulgo_item='HR10'", update_jago_from_ibgo) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_update("chulgo_item='KE10'", update_jago_from_ibgo) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_update("chulgo_item='MB10'", update_jago_from_ibgo) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_update("chulgo_item='MO10'", update_jago_from_ibgo) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_update("chulgo_item='CA10'", update_jago_from_ibgo) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	file_column_free();							// 발주리스트파일(Buy_item) 닫기
	result_free(_result, result_count);			// _result 포인트구조체 삭제

}


