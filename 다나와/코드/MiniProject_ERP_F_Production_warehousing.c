#include "local.h"
#include"MiniProject_ERP_1struct.h"
//생산품창고입고처리
//합격품과 무검사품을 부품창고로 입고 / 불합격은 제외함 

void Production_warehousing()
{
	while(1){
	//생산품창고입고처리
	char* select_column = "Work_Instruction_Number, performance_num, Item_Number, Name, performance_quantity, Customer, LOT";
	char select_work[100] = { NULL };
	char work_order_Insert[1000] = { NULL };
	char Parameter_Insert[1000] = { NULL };
	char stock_num_del[1000] = { NULL };
	int temp_int[20] = { 0 };
	result* _result;
	int result_count;
	char stock_num_Insert[100] = { NULL };
	int stock_date_Insert = 0;
	char stock_warehouse_Insert[100] = { NULL };
	char stock_location_Insert[100] = { NULL };
	int stock_count_Insert = 0;
	char stock_num_delete[100] = { NULL };
	int Select = 0;

	printf("\n ==== < 원하는 메뉴선택 > ====\n\n");
	printf("\t1. 전체 데이터 조회\n\t2. 생산품창고입고처리 등록\n\t3. 생산품창고입고처리 삭제\n\t4. 뒤로가기\n");
	scanf("%d", &Select);

		switch (Select) {
		case 1: //전체 데이터 조회 
			system("cls");
			if (initalizing("product_warehous") == -1) {
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}
			else {
				//printf("%s\n\n", select_result_str);
			}
			print_data();
			file_column_free();
			break;
		case 2: //생산품창고입고처리
			system("cls");
			if (initalizing("performance") == -1) {
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}
			print_data();
			//실적번호 등록 
			printf("\n생산품창고입고처리를 등록할 실적번호를 골라주세요: ");
			scanf("%s", select_work);
			char select_work_condition[100] = "performance_num=";
			strcat(work_order_Insert, "\'");
			strcat(work_order_Insert, select_work);
			strcat(work_order_Insert, "\'");
			strcat(select_work_condition, work_order_Insert);

			//선택한 지시번호로 작업실적등록 데이터를 받아와서 저장함 
			if (_select(select_work_condition, select_column, &select_result_str) == -1) {
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}
			else {
				//printf("%s\n\n", select_result_str);
			}

			if ((result_count = recv_result(&_result, select_result_str)) == -1) {
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}
			//result_print(_result, result_count); //이전의 값 저장되있음 

			//작업실적등록 테이블 닫음
			file_column_free();

			//생산품창고입고처리 테이블 만들기 위해서 받아온 값 저장 
			printf("\n\n");
			strcat(Parameter_Insert, "\'");
			strcat(Parameter_Insert, *(_result->_string_data));
			strcat(Parameter_Insert, "\', ");

			strcat(Parameter_Insert, "\'");
			strcat(Parameter_Insert, *(_result->next->_string_data));
			strcat(Parameter_Insert, "\', ");

			strcat(Parameter_Insert, "\'");
			strcat(Parameter_Insert, *(_result->next->next->_string_data));
			strcat(Parameter_Insert, "\', ");

			strcat(Parameter_Insert, "\'");
			strcat(Parameter_Insert, *(_result->next->next->next->_string_data));
			strcat(Parameter_Insert, "\', ");

			_itoa(*(_result->next->next->next->next->_int_data), temp_int, 10);
			strcat(Parameter_Insert, temp_int);
			strcat(Parameter_Insert, ", ");

			strcat(Parameter_Insert, "\'");
			strcat(Parameter_Insert, *(_result->next->next->next->next->next->_string_data));
			strcat(Parameter_Insert, "\', ");

			strcat(Parameter_Insert, "\'");
			strcat(Parameter_Insert, *(_result->next->next->next->next->next->next->_string_data));
			strcat(Parameter_Insert, "\'");

			//생산품창고입고처리 DB열기 
			

			//입고번호, 입고일자, 입고장소, 입고수량을 받아와서 생산품창고입고처리에 작성
			printf("\n입고번호를 입력하세요: ");
			scanf("%s", stock_num_Insert);

			printf("입고일자를 입력하세요: ");
			scanf("%d", &stock_date_Insert);


			if (initalizing("WareHouse") == -1) {		// 창고파일(WareHouse) 오픈
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}

			print_data();							// 창고목록 출력
			printf("\n");
			file_column_free();

			printf("입고창고를 입력하세요: ");
			scanf("%s", stock_warehouse_Insert);

			printf("입고장소를 입력하세요: ");
			scanf("%s", stock_location_Insert);

			printf("입고수량을 입력하세요: ");
			scanf("%d", &stock_count_Insert);

			strcat(Parameter_Insert, ", \'");
			strcat(Parameter_Insert, stock_num_Insert);
			strcat(Parameter_Insert, "\', ");

			_itoa(stock_date_Insert, temp_int, 10);
			strcat(Parameter_Insert, temp_int);
			strcat(Parameter_Insert, ", ");

			strcat(Parameter_Insert, "\'");
			strcat(Parameter_Insert, stock_warehouse_Insert);
			strcat(Parameter_Insert, "\', ");

			strcat(Parameter_Insert, "\'");
			strcat(Parameter_Insert, stock_location_Insert);
			strcat(Parameter_Insert, "\', ");

			_itoa(stock_count_Insert, temp_int, 10);
			strcat(Parameter_Insert, temp_int);

			if (initalizing("product_warehous") == -1) {
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}


			if (_insert(Parameter_Insert) == -1) {
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}

			print_data();
			file_column_free();
			break;
		case 3:
			system("cls");
			//생산품창고입고처리 DB열기
			if (initalizing("product_warehous") == -1) {
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}
			print_data();
			printf("삭제할 입고번호를 입력하세요: ");
			scanf("%s", stock_num_delete);
			char stock_num_num[100] = "stock_num=";
			strcat(stock_num_del, stock_num_delete);
			strcat(stock_num_num, stock_num_del);

			if (_delete(stock_num_num) == -1) {
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}
			print_data();
			file_column_free();
			break;
		case 4:
			return;
		default:
			break;
		}
	}
}