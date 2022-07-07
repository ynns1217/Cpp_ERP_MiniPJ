#pragma warning(disable:4996)
#include"local.h"
#include"MiniProject_ERP_1struct.h"

void con_regi_choice();
int con_regi();
int con_item_regi();

void con_regi_choice() {
	int choice = 0;
	int con_regi_c = 0, con_item_c = 0;

	printf("[수주등록]\n\n");
	while (1) {
		printf("(0) 뒤로가기\n");
		printf("(1) 수주등록\n");
		printf("(2) 수주-품목등록\n");
		printf("\n입력 : ");
		scanf("%d", &choice);
		getchar();

		system("cls");
		if (choice == 0) {
			break;
		}
		else if (choice == 1) { //수주등록
			while (1) {
				con_regi_c = con_regi();
				if (con_regi_c == 0) {
					system("cls");
					break;
				}
				else if (con_regi_c == 1) {
					system("cls");
				}
				else {
					printf("\n# 잘못된 입력입니다!\n");
					system("pause");
					system("cls");
				}
			}
		}

		else if (choice == 2) {
			while (1) {
				con_item_c = con_item_regi();
				if (con_item_c == 0) {

					system("cls");
					break;
				}
				else if (con_item_c == 1) {

					system("cls");
				}
				else {
					printf("\n# 잘못된 입력입니다!\n");
					system("pause");
					system("cls");
				}
			}

		}

		else {
			printf("\n# 잘못된 입력입니다!\n");
			system("pause");
			system("cls");
		}
	}
	
}

int con_regi() {
	int choice = 0;

	con* c = (con*)malloc(sizeof(con));
	if (c == NULL) {
		printf("memory not allocated!\n");
		exit(1);
	}

	printf("[수주등록]-[수주등록]\n\n");
	printf("주문번호 주문일자 고객 과세구분(1.부가세포함/2.부가세미포함) 담당자\n"); 
	printf("===================================================================\n");
	printf("ex) 001 20220101 (주)다나와 1 최윤진\n\n");
	printf("입력 : ");
	scanf("%s ", c->con_num);
	scanf("%d ", &c->con_date);
	scanf("%s ", c->client);
	scanf("%d ", &c->VAT);
	scanf("%s", c->in_charge);
	getchar();

	//printf("%s %d %s %s %s\n", c->con_num, c->con_date, c->client, c->VAT, c->in_charge); //일단 입력은 잘 됨...

	char* values = (char*)malloc(500 * sizeof(char));
	strcpy(values, "'");
	//strcat(values, "\'");				//주문번호 작은 따옴표 붙이고 끝에 쉼표
	strcat(values, c->con_num);
	strcat(values, "\', ");

	char itoa_temp[20];
	itoa(c->con_date, itoa_temp, 10);  //주문날짜 문자열로 바꿔서 넣고 끝에 쉼표
	strcat(values, itoa_temp);
	strcat(values, ", ");

	strcat(values, "\'");			   //고객 값 작은 따옴표 붙이고 끝에 쉼표
	strcat(values, c->client);
	strcat(values, "\', ");
	
	itoa(c->VAT, itoa_temp, 10);
	strcat(values, itoa_temp);			   //부가세 값 작은 따옴표 붙이고 끝에 쉼표
	strcat(values, ", ");

	strcat(values, "\'");			   //담당자 작은 따옴표 붙이기
	strcat(values, c->client);
	strcat(values, "\'");

	//printf("values : %s\n", values); values에 값 잘 들어갔음

	if (initalizing("C:\\Users\\PKNU\\source\\repos\\Project_DS\\contract_regi") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert(values) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	printf("\n# 등록이 완료되었습니다!\n\n");

	//print_data();
	//printf("\n");

	free(c);
	free(values);

	file_column_free();

	printf("(0) 뒤로가기	(1) 계속등록\n");
	printf("\n입력 : ");
	scanf("%d", &choice);
	getchar();

	return choice;
}

int con_item_regi() {
	int choice = 0;

	char* check_conNum = (char*)malloc(sizeof(char) * 10);
	char* check_itemNum = (char*)malloc(sizeof(char) * 20);
	char* condition = (char*)malloc(sizeof(char) * 500);

	char* values = (char*)malloc(1000 * sizeof(char));

	con_item* c = (con_item*)malloc(sizeof(con_item));
	if (c == NULL) {
		printf("memory not allocated!\n");
		exit(1);
	}
	c->NO = 0;

	result* _result;
	int result_count;

	int con_date, vat;

	printf("[수주등록]-[물품등록]\n\n");
	printf("# 물품을 등록할 주문번호를 입력하세요.\n");
	printf("입력 : ");
	scanf("%s", check_conNum);
	getchar();
	
	//printf("%s\n", check_conNum);
	strcpy(condition, "con_num = '");
	strcat(condition, check_conNum);
	strcat(condition, "\'");
	//printf("%s\n", condition);

	if (initalizing("contract_regi") == -1) { //수주등록 파일 열기
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_select(condition, "con_num, con_date, client, VAT, in_charge", &select_result_str) == -1) { //입력한 주문번호가 존재하지 않을 때
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	else {													//입력한 주문번호가 존재할 때
		//printf("%s\n\n", select_result_str);			    
		strcpy(c->con_num, check_conNum);
		//@@@해당 수주 정보 주문날짜, VAT 값 불러와서 저장해놔야함
		if ((result_count = recv_result(&_result, select_result_str)) == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}
		result_print(_result, result_count); //해당 수주 정보 출력
		printf("\n");

		con_date = *(_result->next->_int_data);
		vat = *(_result->next->next->next->_int_data);

		//printf("%d %d\n", con_date, vat); //값 받아와졌음

		file_column_free();									//수주등록 파일 닫기
		result_free(_result, result_count);


		//해당 수주번호 존재할 때 입력할 품목의 품번 입력받기
		printf("품번 : "); 
		scanf("%s", check_itemNum);
		getchar();

		strcpy(condition, "item_NUMBER = '");
		strcat(condition, check_itemNum);
		strcat(condition, "\'");

		if (initalizing("ITEM") == -1) { //품목 파일 열기
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}

		if (_select(condition, "item_NAME", &select_result_str) == -1) { //입력한 품번이 존재하지 않을 때
			//printf("# 해당 품번이 존재하지 않습니다!\n");
			printf("%s\n", err_msg);
			file_column_free();
			return -1;
		}
		else { //입력한 품번이 존재할 때
			strcpy(c->item_num, check_itemNum); //품번 저장
			if ((result_count = recv_result(&_result, select_result_str)) == -1) {
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}

			strcpy(c->item_name, *(_result->_string_data));  //품명 저장해놓고

			file_column_free(); //품목 파일 닫기
			result_free(_result, result_count);

			printf("품명 : %s\n", c->item_name); //품명 출력
			
			printf("NO : %d\n", ++c->NO);
			while (1) {
				printf("납기일 : ");
				scanf("%d", &c->due_date);
				getchar();

				if (c->due_date < con_date) {
					printf("#납기일은 주문일과 같거나 이후여야 합니다!\n");
				}
				else break;
			}
			while (1) {
				printf("출하예정일 : ");
				scanf("%d", &c->date_shipment);
				getchar();

				if (c->date_shipment < con_date) {
					printf("# 출하예정일은 주문일과 같거나 이후여야 합니다!\n");
				}
				else break;
			}
			while (1) {
				printf("주문수량 : ");
				scanf("%d", &c->amount);
				getchar();

				if (c->amount <= 0) {
					printf("# 1이상의 수를 입력해야합니다!\n");
				}
				else break;
			}
			while (1) {
				printf("단가 : ");
				scanf("%d", &c->unit_price);
				getchar();

				if (c->amount <= 0) {
					printf("# 1이상의 수를 입력해야합니다!\n");
				}
				else break;
			}
			if (vat == 1) { //부가세포함일 때
				c->total_price = c->amount * c->unit_price; //합계액
				c->supply_price = ((c->total_price / 11) * 10); //공급가
				c->tax = c->total_price - c->supply_price; //부가세
			}
			else { //부가세미포함일 때
				c->supply_price = c->unit_price * c->amount; //공급가
				c->tax = c->supply_price / 10;	//부가세
				c->total_price = c->supply_price + c->tax; //합계액
			}
			printf("공급가 : %.2d\n", c->supply_price);
			printf("부가세 : %.2d\n", c->tax);
			printf("합계액 : %.2d\n", c->total_price);

			//여기까지 입력받을 거 입력받기 완. 이제 입력 받은거 파일에 insert 해줘야됨
			char itoa_temp[20];

			strcpy(values, "\'");
			strcat(values, c->con_num);
			strcat(values, "\', ");

			itoa(c->NO, itoa_temp, 10);
			strcat(values, itoa_temp);
			strcat(values, ", ");

			strcat(values, "\'");
			strcat(values, c->item_num);
			strcat(values, "\', ");

			strcat(values, "\'");
			strcat(values, c->item_name);
			strcat(values, "\', ");

			itoa(c->due_date, itoa_temp, 10);
			strcat(values, itoa_temp);
			strcat(values, ", ");

			itoa(c->date_shipment, itoa_temp, 10);
			strcat(values, itoa_temp);
			strcat(values, ", ");

			itoa(c->amount, itoa_temp, 10);
			strcat(values, itoa_temp);
			strcat(values, ", ");

			itoa(c->unit_price, itoa_temp, 10);
			strcat(values, itoa_temp);
			strcat(values, ", ");

			itoa(c->supply_price, itoa_temp, 10);
			strcat(values, itoa_temp);
			strcat(values, ", ");

			itoa(c->tax, itoa_temp, 10);
			strcat(values, itoa_temp);
			strcat(values, ", ");

			itoa(c->total_price, itoa_temp, 10);
			strcat(values, itoa_temp);

			//printf("values : %s\n", values); //values에 값 잘 들어갔음
			if (initalizing("contract_item_regi") == -1) {
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}

			if (_insert(values) == -1) {
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}
			
			printf("\n# 등록이 완료되었습니다!\n\n");
			file_column_free();
		}

	}

	printf("(0) 뒤로가기	(1) 계속등록\n");
	printf("\n입력 : ");
	scanf("%d", &choice);
	getchar();

	free(check_conNum);
	free(check_itemNum);
	free(condition);
	free(values);
	free(c);

	return choice;
}