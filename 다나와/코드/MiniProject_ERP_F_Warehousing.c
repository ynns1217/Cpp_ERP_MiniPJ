#include "local.h"
#include"MiniProject_ERP_1struct.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
int num = 4;			// 샘플데이터수 + 1

void Insert_WarehousingData_from_BuyingList(void)	// 발주입고 - 발주정보를 불러와서 입력
{
	result* _result;
	result* find;
	int result_count;
	char Select_WH[10];

	time_t timer;
	struct tm* t;
	timer = time(NULL);
	t = localtime(&timer);

	int today_date = 0;
	today_date = ((t->tm_year + 1900) * 10000) + ((t->tm_mon + 1) * 100) + (t->tm_mday);	// 오늘 날짜( 20220304 꼴 )

	
	char Parameter_Insert[1000] = { NULL };				// 최종으로 _insert함수로 넣어줄 문자열 (sample.c에서의 value와 같다)
	char temp_int[20] = { 0 };							// int값을 문자열로 바꿀때 쓸 임시 문자열
	char Select_BuyingList_num[20] = { 0 };				// 발주번호 입력받을 임시 문자열변수
	

	// 창고선택
	if (initalizing("WareHouse") == -1) {		// 창고파일(WareHouse) 오픈
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();							// 창고목록 출력
	printf("\n");

	printf("\n입고할 창고번호를 입력해주세요 : ");		// 출력된 창고목록에서 원하는 창고번호를 보고 입력
	scanf("%s", Select_WH);					// 창고번호를 입력받아 저장
											// ex) 1999를 입력함 = [Select_WH = 1999](문자열임을 주의)
	
	char select_num_warehouse[100] = "num_warehouse=";
	strcat(select_num_warehouse, Select_WH);	// select함수에 조건으로 입력하기 위한 양식만들기
												
	if (_select(select_num_warehouse, "name_warehouse, num_warehouse", &select_result_str) == -1) {	// 만든 양식을 토대로 창고목록에서 내부 칼럼정보를 선택해 받아옴
		printf("%s\n", err_msg);

		file_column_free();		// 창고파일(WareHouse) 닫음
		return -1;
	}


	if ((result_count = recv_result(&_result, select_result_str)) == -1) {		// select로 받아온 정보를 _result 포인트 구조체에 멤버로 저장함
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	// num_In_WareHouse
	itoa(num, temp_int, 10);								// 전역변수num 은 초기값으로 현재 입력되있는 샘플데이터의 갯수(= 3)값을 가짐
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	strcat(Parameter_Insert, ", ");							// 다음 내용을 위한 쉼표(',')와 띄어쓰기(' ')

	// name_warehouse
	strcat(Parameter_Insert, "\'");							// 문자열의 경우 앞뒤로 작은따옴표 필요
	strcat(Parameter_Insert, *(_result->_string_data));		// 받아온 결과를 저장
	strcat(Parameter_Insert, "\', ");						// 문자열의 경우 앞뒤로 작은따옴표 필요 + 끝났음을 의미하는 띄어쓰기

															// ex) 여기까지 Parameter_Insert = [4, 'warehouse1', ]
	// num_warehouse
	itoa(*(_result->next->_int_data), temp_int, 10);		// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(Parameter_Insert, temp_int);						// 변환한 문자열을 Parameter_Insert에 붙임
	strcat(Parameter_Insert, ", ");							// 끝났음을 의미하는 띄어쓰기

															// ex) 여기까지 Parameter_Insert = [4, 'warehouse1', 1999, ]

	printf("\n\n");
	result_free(_result, result_count);			// 결과값 저장 노드(동적할당)헤제
	file_column_free();							// 창고파일(WareHouse) 닫음

	// 발주리스트 출력 및 정보 받아오기
	if (initalizing("Buy_item") == -1)	// 발주리스트(Buy_item) 파일열기
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}


	print_data();				// 발주리스트 목록출력
	printf("\n");

	printf("\n정보를 불러올 발주번호를 입력해주세요 : ");			// 출력된 발주목록에서 처리할 발주번호를 입력
	scanf("%s", Select_BuyingList_num);				// 입력한 발주번호를 저장

	char select_num_BuyList[100] = "num_BuyList=";			// select함수를 사용하기 위해 조건에 넣을 문자열변수선언
	strcat(select_num_BuyList, Select_BuyingList_num);		// 생성한 문자열에 입력한 발주번호를 넣어 양식을 완성

	// 완성한 양식을 조건으로 발주리스트에서 [품목명/번호/루트넘버, 입고날짜, 담당자이름/번호, 발주수량, 단가, 공급가액, 세금, 합계액, 남은 발주수량] 을 받아옴 
	if (_select(select_num_BuyList, "item_NAME, item_NUMBER, item_LOT, date, name_responsible, num_responsible, num_buy, bill, pay_in, tax, pay_sum, rest_num_in", &select_result_str) == -1) {	// 만든 양식을 토대로 창고목록에서 내부 칼럼정보를 선택해 받아옴
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if ((result_count = recv_result(&_result, select_result_str)) == -1) {		// select로 받아온 정보를 _result 포인트 구조체에 멤버로 저장함
		printf("%s\n", err_msg);												// 구조체양식은 연결리스트

		file_column_free();
		return -1;
	}
		
	

	// name_item
	strcat(Parameter_Insert, "\'");							
	strcat(Parameter_Insert, *(_result->_string_data));		
	strcat(Parameter_Insert, "\', ");						

	// 여기까지 Parameter_Insert = [4, 'warehouse1', 1999, 'SampleItem1', ]

	//num_item
	char temp_num_item[10] = "'";
	strcat(Parameter_Insert, "\'");
	strcat(Parameter_Insert, *(_result->next->_string_data));
	strcat(Parameter_Insert, "\', ");

	strcat(temp_num_item, *(_result->next->_string_data));
	strcat(temp_num_item, "\'");

	// 여기까지 Parameter_Insert = [4, 'warehouse1', 1999, 'SampleItem1', 19999, ]

	//LOT_number
	strcat(Parameter_Insert, "\'");												
	strcat(Parameter_Insert, *(_result->next->next->_string_data));		
	strcat(Parameter_Insert, "\', ");										

	// 여기까지 Parameter_Insert = [4, 'warehouse1', 1999, 'SampleItem1', 19999, 'RA00001', ]

	//date
	itoa(*(_result->next->next->next->_int_data), temp_int, 10);		
	strcat(Parameter_Insert, temp_int);						
	strcat(Parameter_Insert, ", ");							

	// 여기까지 Parameter_Insert = [4, 'warehouse1', 1999, 'SampleItem1', 19999, 'RA00001', 20220304, ]

	//name_responsible
	strcat(Parameter_Insert, "\'");							
	strcat(Parameter_Insert, *(_result->next->next->next->next->_string_data));		
	strcat(Parameter_Insert, "\', ");						

	// 여기까지 Parameter_Insert = [4, 'warehouse1', 1999, 'SampleItem1', 19999, 'RA00001', 20220304, 'SamplePerson1', ]

	//num_responsible
	itoa(*(_result->next->next->next->next->next->_int_data), temp_int, 10);		
	strcat(Parameter_Insert, temp_int);						
	strcat(Parameter_Insert, ", ");

	// 여기까지 Parameter_Insert = [4, 'warehouse1', 1999, 'SampleItem1', 19999, 'RA00001', 20220304, 'SamplePerson1', 199, ]

	// 입고수량 입력
	int num_InWarehouse = 0;
	printf("입고수량을 입력하세요 : ");
	scanf("%d", &num_InWarehouse);

	itoa(num_InWarehouse, temp_int, 10);					
	strcat(Parameter_Insert, temp_int);						
	strcat(Parameter_Insert, ", ");

	// 80을 입력했다는 가정
	// 여기까지 Parameter_Insert = [4, 'warehouse1', 1999, 'SampleItem1', 19999, 'RA00001', 20220304, 'SamplePerson1', 199, 80, ]
	
	// bill = 단가
	int bill = *(_result->next->next->next->next->next->next->next->_int_data);
	itoa(bill, temp_int, 10);		
	strcat(Parameter_Insert, temp_int);						
	strcat(Parameter_Insert, ", ");
	
	// 여기까지 Parameter_Insert = [4, 'warehouse1', 1999, 'SampleItem1', 19999, 'RA00001', 20220304, 'SamplePerson1', 199, 80, 1000, ]


	// pay_in = 공급가
	int pay_in = num_InWarehouse * bill;	// 입고수량 * 단가
	itoa(pay_in, temp_int, 10);		
	strcat(Parameter_Insert, temp_int);						
	strcat(Parameter_Insert, ", ");

	// 여기까지 Parameter_Insert = [4, 'warehouse1', 1999, 'SampleItem1', 19999, 'RA00001', 20220304, 'SamplePerson1', 199, 80, 1000, 80000, ]
	
	// tax =세금
	int tax = pay_in / 10;		// 공급가 / 10
	itoa(tax, temp_int, 10);		
	strcat(Parameter_Insert, temp_int);						
	strcat(Parameter_Insert, ", ");
	
	// 여기까지 Parameter_Insert = [4, 'warehouse1', 1999, 'SampleItem1', 19999, 'RA00001', 20220304, 'SamplePerson1', 199, 80, 1000, 80000, 8000, ]

	// pay_sum = 합계액
	int pay_sum = pay_in + tax;		// 세금 + 공급가
	itoa(pay_sum, temp_int, 10);		
	strcat(Parameter_Insert, temp_int);						
	
	// 여기까지 Parameter_Insert = [4, 'warehouse1', 1999, 'SampleItem1', 19999, 'RA00001', 20220304, 'SamplePerson1', 199, 80, 1000, 80000, 8000, 88000]

	// rest_num_in (입고이전 값)
	int rest_num_for_Warehousing_after;					// 입고후 남은 발주량
	int rest_num_for_Warehousing_before = *(_result->next->next->next->next->next->next->next->next->next->next->next->_int_data);		// 입고전 남은발주량
	
	// rest_num_in (입고이후 값)
	rest_num_for_Warehousing_after = rest_num_for_Warehousing_before - num_InWarehouse;			//  (입고후 남은 발주량 = 입고전 남은 발주량 - 입고량)
	if (rest_num_for_Warehousing_after < 0)
	{
		printf("\n === !!! 잘못된 입고수량을 입력하셨습니다. !!! === \n");
		printf(" 입고수량은 남은 발주수량을 넘어설수 없습니다.\n");
		printf(" - 입고수량 : %d\n", num_InWarehouse);
		printf(" - 남은 발주수량: %d\n\n", rest_num_for_Warehousing_before);
		return -1;
	}
																						


	
	printf("\n\n");
	file_column_free();							// 발주리스트파일(Buy_item) 닫기
	result_free(_result, result_count);			// _result 포인트구조체 삭제
	

	if (initalizing("In_WareHouse") == -1) {
		printf("%s\n", err_msg); 

		file_column_free();
		return -1;
	}

	if (_insert(Parameter_Insert) == -1)
	{	// = _insert("4, 'warehouse1', 1999, 'SampleItem1', 19999, 'RA00001', 20220304, 'SamplePerson1', 199, 80, 1000, 80000, 8000, 88000") 가 된다
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();
	printf("\n\n");
	file_column_free();

	if (initalizing("Buy_item") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	char update_rest_num_BuyList_before[100] = "rest_num_in=";
	char update_rest_num_BuyList_after[100] = "rest_num_in=";

	itoa(rest_num_for_Warehousing_before, temp_int, 10);		// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(update_rest_num_BuyList_before, temp_int);				// 변환한 문자열을 Parameter_Insert에 붙임

	itoa(rest_num_for_Warehousing_after, temp_int, 10);			// 받아온 정보가 int형이므로 문자열로 형변환수행
	strcat(update_rest_num_BuyList_after, temp_int);				// 변환한 문자열을 Parameter_Insert에 붙임

	// 입고한 다음 발주정보의 남은 발주수량을 업데이트한다
	if (_update(select_num_BuyList, update_rest_num_BuyList_after) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();
	printf("\n 입고되지 않은 남은 발주 수량은 < %d > 개입니다.\n", rest_num_for_Warehousing_after);
	num++;
	file_column_free();

	

	// 재고테이블에 해당품목수량 입고수량만큼 업데이트

	if (initalizing("Jaego") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	char item_number[100] = "num_item=";
	strcat(item_number, temp_num_item);

	if (_select(item_number, "ibgo_item", &select_result_str) == -1) {	// 만든 양식을 토대로 창고목록에서 내부 칼럼정보를 선택해 받아옴
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if ((result_count = recv_result(&_result, select_result_str)) == -1) {		// select로 받아온 정보를 _result 포인트 구조체에 멤버로 저장함
		printf("%s\n", err_msg);												// 구조체양식은 연결리스트

		file_column_free();
		return -1;
	}


	char update_jago_from_ibgo[100] = "ibgo_item=";
	num_InWarehouse = num_InWarehouse + (*(_result->_int_data));	// 기존 입고수량에 방금 입고된 수량을 더한값을 업데이트
	itoa(num_InWarehouse, temp_int, 10);
	strcat(update_jago_from_ibgo, temp_int);
	

	if (_update(item_number, update_jago_from_ibgo) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	file_column_free();							// 발주리스트파일(Buy_item) 닫기
	result_free(_result, result_count);			// _result 포인트구조체 삭제


}



void Insert_WarehousingData(void)		// 예외입고 - 정보를 하나하나 입력
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

	char Select_WH[10];
	char Select_Item[100];
	char Select_Person[100];
	char Parameter_Insert[1000] = { NULL };
	char temp_int[20] = { 0 };
	

	// 창고선택
	if (initalizing("WareHouse") == -1) {		// 창고파일(WareHouse) 오픈
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();				// 창고목록 출력
	printf("\n");

	printf("\n입고할 창고번호를 입력해주세요 : ");		// 출력된 창고목록에서 원하는 창고번호를 보고 입력
	scanf("%s", Select_WH);							// 창고번호를 입력받아 저장
													// ex) 1999를 입력함 = [Select_WH = 1999](문자열임을 주의)
		
	char select_num_warehouse[100] = "num_warehouse=";
	strcat(select_num_warehouse, Select_WH);		// select함수에 조건으로 입력하기 위한 양식만들기
													// ex) 여기까지 [select_num_warehouse] = [num_warehouse] = [1999]
	if (_select(select_num_warehouse, "name_warehouse, num_warehouse", &select_result_str) == -1) {	// 만든 양식을 토대로 창고목록에서 내부 칼럼정보를 선택해 받아옴
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}


	if ((result_count = recv_result(&_result, select_result_str)) == -1) {		// select로 받아온 정보를 _result 포인트 구조체에 멤버로 저장함
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	// num_Warehousing
	itoa(num, temp_int, 10);
	strcat(Parameter_Insert, temp_int);
	strcat(Parameter_Insert, ", ");						

	// name_warehouse
	strcat(Parameter_Insert, "\'");							
	strcat(Parameter_Insert, *(_result->_string_data));		
	strcat(Parameter_Insert, "\', ");						

	// 여기까지 [Parameter_Insert = 'warehouse1', ]

	// num_warehouse
	itoa(*(_result->next->_int_data), temp_int, 10);		
	strcat(Parameter_Insert, temp_int);						
	strcat(Parameter_Insert, ", ");							

	// 여기까지 [Parameter_Insert = 'warehouse1', 1999, ]

	printf("\n\n");
	result_free(_result, result_count);		// _result구조체 삭제
	file_column_free();						// 창고파일(WareHouse) 닫기


	//품목선택
	if (initalizing("ITEM") == -1) {  // 품목파일(item) 열기
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();		// 품목목록 출력
	printf("\n");

	printf("\n품목번호를 입력해주세요 : ");		// 출력된 창고목록에서 원하는 창고번호를 보고 입력
	scanf("%s", Select_Item);				// 창고번호를 입력받아 저장

	char select_num_item[100] = "item_NUMBER=";
	strcat(select_num_item, Select_Item);

	if (_select(select_num_item, "item_NAME, item_NUMBER, item_LOT", &select_result_str) == -1) {	// 만든 양식을 토대로 창고목록에서 내부 칼럼정보를 선택해 받아옴
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}


	if ((result_count = recv_result(&_result, select_result_str)) == -1) {		// select로 받아온 정보를 _result 포인트 구조체에 멤버로 저장함
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	// name_item
	strcat(Parameter_Insert, "\'");							
	strcat(Parameter_Insert, *(_result->_string_data));		
	strcat(Parameter_Insert, "\', ");						

	// 여기까지 [Parameter_Insert = 'warehouse1', 1999, 'SampleItem1', ]
	
	// num_item
	strcat(Parameter_Insert, "\'");
	strcat(Parameter_Insert, *(_result->next->_string_data));
	strcat(Parameter_Insert, "\', ");

	// 여기까지 [Parameter_Insert = 'warehouse1', 1999, 'SampleItem1', 19999, ]

	// LOT_number
	strcat(Parameter_Insert, "\'");										
	strcat(Parameter_Insert, *(_result->next->next->_string_data));		
	strcat(Parameter_Insert, "\', ");									
	
	// 여기까지 [Parameter_Insert = 'warehouse1', 1999, 'SampleItem1', 19999, 'RA0001', ]
	
	printf("\n\n");
	result_free(_result, result_count);		// _result 포인터 구조체 삭제
	file_column_free();						// 품목파일(item) 닫음


	// 날짜입력 - 자동계산
	itoa(today_date, temp_int, 10);		
	strcat(Parameter_Insert, temp_int);						
	strcat(Parameter_Insert, ", ");							

	// 여기까지 [Parameter_Insert = 'warehouse1', 1999, 'SampleItem1', 19999, 'RA0001', 20220304, ]

	// 담당자입력
	if (initalizing("Person_responsibe") == -1) {		
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();		// 담당자목록 출력
	printf("\n");

	printf("\n담당자번호를 입력해주세요 : ");		// 출력된 담당자목록에서 원하는 담당자번호를 보고 입력
	scanf("%s", Select_Person);					// 담당자번호를 입력받아 저장

	char select_num_person[100] = "num_responsible=";
	strcat(select_num_person, Select_Person);

	if (_select(select_num_person, "name_responsible, num_responsible", &select_result_str) == -1) {	
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}


	if ((result_count = recv_result(&_result, select_result_str)) == -1) {		// select로 받아온 정보를 _result 포인트 구조체에 멤버로 저장함
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	// 담당자 이름
	strcat(Parameter_Insert, "\'");							
	strcat(Parameter_Insert, *(_result->_string_data));		
	strcat(Parameter_Insert, "\', ");						

	// 담당자 번호
	itoa(*(_result->next->_int_data), temp_int, 10);		
	strcat(Parameter_Insert, temp_int);						
	strcat(Parameter_Insert, ", ");							

	// printf("%s", Parameter_Insert);

	printf("\n\n");
	result_free(_result, result_count);				// _result 포인터구조체 삭제
	file_column_free();								// 담당자파일(Person_responsibe) 닫기



	// 입고수량,단가입력 및 계산값 입력
	int num_InWarehouse = 0;
	printf("입고수량을 입력하세요 : ");
	scanf("%d", &num_InWarehouse);

	itoa(num_InWarehouse, temp_int, 10);					
	strcat(Parameter_Insert, temp_int);						
	strcat(Parameter_Insert, ", ");							

	// 단가
	int bill = 0;
	printf("단가를 입력하세요 : ");
	scanf("%d", &bill);

	itoa(bill, temp_int, 10);					
	strcat(Parameter_Insert, temp_int);						
	strcat(Parameter_Insert, ", ");							

	int pay_in = bill * num_InWarehouse;

	// 공급가
	itoa(pay_in, temp_int, 10);					
	strcat(Parameter_Insert, temp_int);						
	strcat(Parameter_Insert, ", ");						

	int tax = pay_in / 10;

	// 세금
	itoa(tax, temp_int, 10);					
	strcat(Parameter_Insert, temp_int);						
	strcat(Parameter_Insert, ", ");							

	// 합계액
	int pay_sum = pay_in + tax;
	itoa(pay_sum, temp_int, 10);					
	strcat(Parameter_Insert, temp_int);						

	
	printf("\n\n");

	// 입고테이블에 완성된 파라미터 입력
	if (initalizing("In_WareHouse") == -1) { // 입고파일(In_WareHouse) 열기
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert(Parameter_Insert) == -1)	// 완성된 양식화된 문자열을 _insert
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	num++;

	print_data();
	printf("\n\n");
	file_column_free();		// 입고파일(In_WareHouse) 닫기

	
	if (initalizing("Jaego") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	char item_number[100] = "num_item=";
	strcat(item_number, Select_Item);

	if (_select(item_number, "ibgo_item", &select_result_str) == -1) {	// 만든 양식을 토대로 창고목록에서 내부 칼럼정보를 선택해 받아옴
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if ((result_count = recv_result(&_result, select_result_str)) == -1) {		// select로 받아온 정보를 _result 포인트 구조체에 멤버로 저장함
		printf("%s\n", err_msg);												// 구조체양식은 연결리스트

		file_column_free();
		return -1;
	}


	char update_jago_from_ibgo[100] = "ibgo_item=";
	num_InWarehouse = num_InWarehouse + (*(_result->_int_data));	// 기존 입고수량에 방금 입고된 수량을 더한값을 업데이트
	itoa(num_InWarehouse, temp_int, 10);
	strcat(update_jago_from_ibgo, temp_int);

	
	if (_update(item_number, update_jago_from_ibgo) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	file_column_free();							// 발주리스트파일(Buy_item) 닫기
	result_free(_result, result_count);			// _result 포인트구조체 삭제


}

void print_Warehousing_state(void)		// 입고현황출력
{
		int Select_Sort = 0;
		if (initalizing("In_WareHouse") == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}

		print_data();
		printf("\n\n");

	file_column_free();
}

void delete_Warehousing(void)
{
	result* _result;
	result* find;
	int result_count;

	char Select_del_Warehousing[10];

	if (initalizing("In_WareHouse") == -1) { // 입고파일(In_WareHouse) 열기
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();
	printf("\n");

	printf("\n취소할 입고번호를 입력해주세요 : ");		// 출력된 품목목록에서 원하는 품목번호를 보고 입력
	scanf("%s", Select_del_Warehousing);

	char select_num_Warehousing[100] = "num_In_WareHouse=";
	strcat(select_num_Warehousing, Select_del_Warehousing);
	printf("%s", select_num_Warehousing);

	//if (_select(select_num_Warehousing, ", num_responsible", &select_result_str) == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}


	//if ((result_count = recv_result(&_result, select_result_str)) == -1) {		// select로 받아온 정보를 _result 포인트 구조체에 멤버로 저장함
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}


	if (_delete(select_num_Warehousing) == -1) // 만든 양식을 토대로 품목목록에서 내부 칼럼정보를 선택해 받아옴
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