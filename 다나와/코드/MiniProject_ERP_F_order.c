#include "local.h"
#include"MiniProject_ERP_1struct.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)


void insertOrderData(void)		// 발주 등록
{
	result* _result;
	result* find;
	int result_count;

	time_t timer;
	struct tm* t;
	timer = time(NULL);
	t = localtime(&timer);

	int today_date = 0;
	today_date = ((t->tm_year + 1900) * 10000) + ((t->tm_mon + 1) * 100) + (t->tm_mday);	// 오늘 날짜( 20220304 꼴 )

	char Select_Item[100];
	char Select_Person[100];
	char Parameter_Insert[1000] = { NULL };
	char temp_int[20] = { 0 };

	int num_orderList = 0;
	printf("발주등록 번호를 입력하세요 : ");
	scanf("%d", &num_orderList);

	itoa(num_orderList, temp_int, 10);					// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);
	strcat(Parameter_Insert, ", ");

	printf("\n\n");

	//품목선택
	if (initalizing("ITEM") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();		// 품목목록 출력
	printf("\n");

	printf("\n품목 번호를 입력해주세요 : ");		// 출력된 품목목록에서 원하는 품목번호를 보고 입력
	scanf("%s", Select_Item);						// 품목번호를 입력받아 저장

	char select_num_item[100] = "item_NUMBER=";
	strcat(select_num_item, Select_Item);

	if (_select(select_num_item, "item_NAME, item_NUMBER, item_LOT", &select_result_str) == -1) // 만든 양식을 토대로 품목목록에서 내부 칼럼정보를 선택해 받아옴
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

	strcat(Parameter_Insert, "\'");							// 문자열의 경우 앞뒤로 작은따옴표 필요
	strcat(Parameter_Insert, *(_result->_string_data));		// 받아온 결과를 저장
	strcat(Parameter_Insert, "\', ");						// 문자열의 경우 앞뒤로 작은따옴표 필요 + 끝났음을 의미하는 띄어쓰기

	strcat(Parameter_Insert, "\'");							// 문자열의 경우 앞뒤로 작은따옴표 필요
	strcat(Parameter_Insert , *(_result->next->_string_data));
	strcat(Parameter_Insert, "\', ");						// 끝났음을 의미하는 띄어쓰기

	strcat(Parameter_Insert, "\'");							// 문자열의 경우 앞뒤로 작은따옴표 필요
	strcat(Parameter_Insert, *(_result->next->next->_string_data));		// 받아온 결과를 저장
	strcat(Parameter_Insert, "\', ");

															// // ex) 여기까지 [Parameter_Insert = 'warehouse1', 1999, 'SampleItem1', 19999, ]
	// printf("%s", Parameter_Insert);

	printf("\n\n");
	result_free(_result, result_count);
	file_column_free();


	// 날짜입력
	itoa(today_date, temp_int, 10);							// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	strcat(Parameter_Insert, ", ");							// 끝났음을 의미하는 띄어쓰기
	//printf("%s", Parameter_Insert);


	// 담당자입력
	if (initalizing("Person_responsibe") == -1) 
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();									// 담당자목록 출력
	printf("\n");

	printf("\n담당자 번호를 입력해주세요 : ");		    // 출력된 담당자목록에서 원하는 담당자번호 를 보고 입력
	scanf("%s", Select_Person);						// 담당자 번호를 입력받아 저장

	char select_num_person[100] = "num_responsible=";
	strcat(select_num_person, Select_Person);

	if (_select(select_num_person, "name_responsible, num_responsible", &select_result_str) == -1) // 만든 양식을 토대로 담당자목록에서 내부 칼럼정보를 선택해 받아옴
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

	strcat(Parameter_Insert, "\'");							// 문자열의 경우 앞뒤로 작은따옴표 필요
	strcat(Parameter_Insert, *(_result->_string_data));		// 받아온 결과를 저장
	strcat(Parameter_Insert, "\', ");						// 문자열의 경우 앞뒤로 작은따옴표 필요 + , 로 다음 데이터 받을 준비

															// ex) 여기까지 [Parameter_Insert = 'warehouse1' ]

	itoa(*(_result->next->_int_data), temp_int, 10);		// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	strcat(Parameter_Insert, ", ");							// , 로 다음 데이터 받을 준비

	// printf("%s", Parameter_Insert);

	printf("\n\n");
	result_free(_result, result_count);
	file_column_free();



	// 입고수량,단가입력 및 계산값 입력
	int num_orderCnt = 0;
	printf("발주수량을 입력하세요 : ");						// 발주 수량 입력
	scanf("%d", &num_orderCnt);
	printf("\n");

	itoa(num_orderCnt, temp_int, 10);						// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	strcat(Parameter_Insert, ", ");							// , 로 다음 데이터 받을 준비

	int bill = 0;
	printf("단가를 입력하세요 : ");							// 단가 입력
	scanf("%d", &bill);

	itoa(bill, temp_int, 10);								// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	strcat(Parameter_Insert, ", ");							// , 로 다음 데이터 받을 준비

	int pay_in = bill * num_orderCnt;						// 공급가액 삽입 (단가 * 발주수량)

	itoa(pay_in, temp_int, 10);								// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	strcat(Parameter_Insert, ", ");							// , 로 다음 데이터 받을 준비

	int tax = pay_in / 10;									// 부가세 삽입 (공급가액 / 10)

	itoa(tax, temp_int, 10);								// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	strcat(Parameter_Insert, ", ");							// , 로 다음 데이터 받을 준비

	int pay_sum = pay_in + tax;								// 합계액 삽입 (공급가액 + 부가세)

	itoa(pay_sum, temp_int, 10);							// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	strcat(Parameter_Insert, ", ");							// , 로 다음 데이터 받을 준비

	itoa(num_orderCnt, temp_int, 10);						// 남은 발주 수량으로 위에서 입력 받은 num_orderCnt 발주 수량 사용
	strcat(Parameter_Insert, temp_int);

	// printf("%s", Parameter_Insert);
	printf("\n\n");

	// 발주테이블에 완성된 파라미터 입력
	if (initalizing("Buy_item") == -1) 
	{
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
	printf("\n==========================================================================\n");

	printf("\n\n");
	file_column_free();
}

void orderList(void)
{
	if (initalizing("Buy_item") == -1)
	{
		printf("%s\n", err_msg);
	}

	print_data();
	printf("\n==========================================================================\n");

	printf("\n\n");
	file_column_free();
}

void deleteOrderData(void)
{
	char Select_order[100];

	if (initalizing("Buy_item") == -1)
	{
		printf("%s\n", err_msg);
	}

	print_data();
	printf("\n");

	printf("\n취소할 발주 번호를 입력해주세요 : ");		// 출력된 품목목록에서 원하는 품목번호를 보고 입력
	scanf("%s", Select_order);

	char select_num_order[100] = "num_BuyList=";
	strcat(select_num_order, Select_order);
	printf("%s", select_num_order);

	if (_delete(select_num_order) == -1) // 만든 양식을 토대로 품목목록에서 내부 칼럼정보를 선택해 받아옴
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();
	printf("\n==========================================================================\n");

	printf("\n\n");
	file_column_free();
}