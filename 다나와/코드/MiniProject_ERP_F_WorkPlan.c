#include "local.h"
#include"MiniProject_ERP_1struct.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

int Insert_Production_Plan_File(void) {
	result* _result;
	result* find;
	int result_count;
	char Select_Item[20];

	if (initalizing("contract_item_regi") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	printf("\n");
	print_data();
	file_column_free();

	printf("\n품번을 선택해주세요 : ");		// 출력된 품목목록에서 원하는 품목번호를 보고 입력
	scanf("%s", Select_Item);	// CASE01

	char select_num_item[100] = "item_NUMBER ="; // char* conditional =  "item_NAME = Select_item";
	strcat(select_num_item, Select_Item); // item_NUMBER = CASE01

	char Parameter_Insert[1000] = { NULL };
	char temp_int[20] = { 0 };

	if (initalizing(Select_Item) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	printf("\n");
	print_data();

	file_column_free();

	if (initalizing("ITEM") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_select(select_num_item, "item_NUMBER, item_NAME, item_GOAL", &select_result_str) == -1) // 만든 양식을 토대로 품목목록에서 내부 칼럼정보를 선택해 받아옴
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if ((result_count = recv_result(&_result, select_result_str)) == -1) // select로 받아온 정보를 _result 포인트 구조체에 멤버로 저장함
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	//result_print(_result, result_count);

	strcat(Parameter_Insert, "\'");
	strcat(Parameter_Insert, *(_result->_string_data));
	strcat(Parameter_Insert, "\', ");

	strcat(Parameter_Insert, "\'");							// 문자열의 경우 앞뒤로 작은따옴표 필요 , '
	strcat(Parameter_Insert, *(_result->next->_string_data));		// 받아온 결과를 저장, 'CPU
	strcat(Parameter_Insert, "\', ");						// 문자열의 경우 앞뒤로 작은따옴표 필요 + 끝났음을 의미하는 띄어쓰기, 'CPU', 

	itoa(*(_result->next->next->_int_data), temp_int, 10);        // 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	strcat(Parameter_Insert, ", ");

	file_column_free();

	int order_VAR;
	printf("순서를 입력해주세요 : ");
	scanf("%d", &order_VAR); // Order 값 입력

	itoa(order_VAR, temp_int, 10);
	strcat(Parameter_Insert, temp_int);
	strcat(Parameter_Insert, ", "); // Parameter_insert('CPU', 'PC01', 100, )+ 'order_VAR', = 'CPU', 'PC01', 100, 'order', 

	int ETC_NUM;
	printf("작업예정일을 입력해주세요 : ");
	scanf("%d", &ETC_NUM);

	itoa(ETC_NUM, temp_int, 10);						    // 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	strcat(Parameter_Insert, ", ");                         // Parameter_insert('CPU', 'PC01', 100, 'order', ) + ETC_NUM(20220309), = 'CPU', 'PC01', 100, 'order', 20220309, 

	int Quantity_NUM;
	printf("수량을 입력해주세요 : ");                      // Quantity_NUM - 수량
	scanf("%d", &Quantity_NUM);

	itoa(Quantity_NUM, temp_int, 10);						    // 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						    // parameter ~ = 'CPU', 'PC01', 100, 'order', 20220309, 15

	if (initalizing("Production_Plan_Registration") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert(Parameter_Insert) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	

	print_data();
	printf("\n");

	file_column_free();
	return Quantity_NUM;
}

void Insert_Work_order_File() {
	result* _result;
	result* find;
	int result_count;
	char Select_Item[20];
	char Customer_name[20];
	char Parameter_Insert[1000] = { NULL };
	char temp_int[20] = { 0 };

	if (initalizing("Production_Plan_Registration") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	printf("\n");
	print_data();
	printf("\n");

	file_column_free();

	if (initalizing("contract_item_regi") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	printf("품번을 선택해주세요 : ");		// 출력된 품목목록에서 원하는 품목번호를 보고 입력
	scanf("%s", Select_Item);	// CASE01

	char select_num_item[100] = "item_num ="; // char* conditional =  "item_NAME = Select_item";
	strcat(select_num_item, Select_Item); // item_NUMBER = CASE01

	if (_select(select_num_item, "due_date, item_num, item_name", &select_result_str) == -1) // 만든 양식을 토대로 품목목록에서 내부 칼럼정보를 선택해 받아옴
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if ((result_count = recv_result(&_result, select_result_str)) == -1) // select로 받아온 정보를 _result 포인트 구조체에 멤버로 저장함
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}


	itoa(*(_result->_int_data), temp_int, 10);
	strcat(Parameter_Insert, temp_int);
	strcat(Parameter_Insert, ", "); // Parameter_insert('CPU', 'PC01', 100, )+ 'Due_Date', = 'CPU', 'PC01', 100, 'order',

	int Quantity;

	printf("지시수량을 입력하시오 : ");
	scanf("%d", &Quantity);      // 지시수량 입력 

	itoa(Quantity, temp_int, 10);
	strcat(Parameter_Insert, temp_int);
	strcat(Parameter_Insert, ", ");

	char Work_Instruction_Number[20];

	printf("작업지시번호를 입력하시오 : ");
	scanf("%s", Work_Instruction_Number); // 작업지시번호 값 입력

	strcat(Parameter_Insert, "\'");
	strcat(Parameter_Insert, Work_Instruction_Number);
	strcat(Parameter_Insert, "\', ");

	char LOT[20];

	printf("LOT를 입력하시오 : ");
	scanf("%s", &LOT);   //LOT 값 입력

	strcat(Parameter_Insert, "\'");
	strcat(Parameter_Insert, LOT);
	strcat(Parameter_Insert, "\', ");

	strcat(Parameter_Insert, "\'");     //불러온값 붙이기
	strcat(Parameter_Insert, *(_result->next->_string_data));
	strcat(Parameter_Insert, "\', ");

	strcat(Parameter_Insert, "\'");
	strcat(Parameter_Insert, *(_result->next->next->_string_data));
	strcat(Parameter_Insert, "\'");

	file_column_free();

	printf("\n");

	//COSTOMER 
	if (initalizing("contract_regi") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_select("*", "client", &select_result_str) == -1) // 만든 양식을 토대로 품목목록에서 내부 칼럼정보를 선택해 받아옴
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if ((result_count = recv_result(&_result, select_result_str)) == -1) // select로 받아온 정보를 _result 포인트 구조체에 멤버로 저장함
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	result_print(_result, result_count);
	printf("\n\n");

	printf("고객명을 입력하시오 : ");
	scanf("%s", Customer_name);
	printf("\n");
	char select_customer[100] = "client ="; // char* conditional =  "item_NAME = Select_item";
	strcat(select_customer, Customer_name); // item_NUMBER = CASE01


	if (_select(select_customer, "client", &select_result_str) == -1) // 만든 양식을 토대로 품목목록에서 내부 칼럼정보를 선택해 받아옴
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if ((result_count = recv_result(&_result, select_result_str)) == -1) // select로 받아온 정보를 _result 포인트 구조체에 멤버로 저장함
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	//customer
	strcat(Parameter_Insert, "\, ");   // (    ,     ,     | <- 여기서 끝났기때문에 ,를 써줘야함
	strcat(Parameter_Insert, "\'");
	strcat(Parameter_Insert, *(_result->_string_data));
	strcat(Parameter_Insert, "\'");

	file_column_free();

	if (initalizing("Work_Order_Registration") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert(Parameter_Insert) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();
	printf("\n");

	file_column_free();

}
