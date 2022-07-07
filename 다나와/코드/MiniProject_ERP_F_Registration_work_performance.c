#include "local.h"
#include"MiniProject_ERP_1struct.h"

//작업실적등록(작업지시등록에서 받아옴)

void Registration_work_performance()
{	
	while(1){
	//작업실적등록
	char* select_column = "Work_Instruction_Number, Item_Number, Name, Customer, Quantity";
	char select_work[100] = { NULL };
	int indicated_quantity_Insert = 0;
	int performance_quantity_Insert[100] = {NULL};
	char LOT_Insert[100] = { NULL };
	char work_order_Insert[1000] = { NULL };
	char performance_num_del[1000] = { NULL };
	char Parameter_Insert[1000] = { NULL };
	int temp_int[20] = { 0 };
	char performance_num_delete[100] = { NULL };
	result* _result;
	int result_count;
	int Select = 0;

	printf("\n ==== < 원하는 메뉴선택 > ====\n\n");
	printf("\t1. 전체 데이터 조회\n\t2. 작업실적 등록\n\t3. 작업실적 삭제\n\t4. 뒤로가기\n");
	scanf("%d", &Select);

		switch (Select) {
		case 1:	//전체 데이터 조회 
			system("cls");
			if (initalizing("performance") == -1) {
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

		case 2: //작업실적등록
			system("cls");
			//작업지시등록 테이블 불러옴 
			if (initalizing("Work_Order_Registration") == -1) {
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}
			print_data();
			//작업지시번호 선택
			printf("\n작업실적을 등록할 작업지시번호를 골라주세요: ");
			scanf("%s", select_work);
			char select_work_condition[100] = "Work_Instruction_Number=";
			strcat(work_order_Insert, "\'");
			strcat(work_order_Insert, select_work);
			strcat(work_order_Insert, "\'");
			strcat(select_work_condition, work_order_Insert);

			//선택한 지시번호로 작업실적등록 값을 받아오기 위해 저장함
			if (_select(select_work_condition, select_column, &select_result_str) == -1) {
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}

			if ((result_count = recv_result(&_result, select_result_str)) == -1) {
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}

			//result_print(_result, result_count); //이전의 값 저장되있음 

			//작업지시등록 테이블 닫음
			file_column_free();

			//작업실적등록 테이블 만들기 위해서 받아온 값 저장 
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

			//작업실적등록 DB열기 
			if (initalizing("performance") == -1) {
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}

			//실적수량, 실적번호, LOT를 받아와서 작업실적등록에 작성 
			printf("실적수량을 입력하세요: ");
			scanf("%d", &indicated_quantity_Insert);
			printf("실적번호를 입력하세요: ");
			scanf("%s", &performance_quantity_Insert);
			printf("LOT를 입력하세요: ");
			scanf("%s", LOT_Insert);


			strcat(Parameter_Insert, ", ");
			_itoa(indicated_quantity_Insert, temp_int, 10);
			strcat(Parameter_Insert, temp_int);
			strcat(Parameter_Insert, ", ");

			strcat(Parameter_Insert, "\'");
			strcat(Parameter_Insert, performance_quantity_Insert);
			strcat(Parameter_Insert, "\', ");


			strcat(Parameter_Insert, "\'");
			strcat(Parameter_Insert, LOT_Insert);
			strcat(Parameter_Insert, "\'");

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
			//작업실적등록 DB열기 
			if (initalizing("performance") == -1) {
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}
			print_data();
			printf("삭제할 실적번호를 입력하세요 : ");
			scanf("%s", performance_num_delete);
			char select_performance_num[100] = "performance_num=";
			strcat(performance_num_del, "\'");
			strcat(performance_num_del, performance_num_delete);
			strcat(performance_num_del, "\'");
			strcat(select_performance_num, performance_num_del);
			
			if (_delete(select_performance_num) == -1) {
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
//예외처리, UI다듬기, 개수 넘어가면 안되고, %d에서 숫자입력하면 안되게 