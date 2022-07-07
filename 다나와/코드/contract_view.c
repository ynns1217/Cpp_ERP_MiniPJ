#pragma warning(disable:4996)
#include"local.h"
#include"MiniProject_ERP_1struct.h"

int con_view() {
    int choice = 0;

    char* check_conNum = (char*)malloc(sizeof(char) * 10);
    char* condition = (char*)malloc(sizeof(char) * 500);

    result* _result;
    int result_count;

    while (1) {
        printf("[수주현황]\n\n");
        printf("[주문목록]\n");
        if (initalizing("contract_regi") == -1) { //수주등록 파일 열기
            printf("%s\n", err_msg);

            file_column_free();
            return -1;
        }
        if (_select("*", "con_num, con_date, client, VAT, in_charge", &select_result_str) == -1) { //전체조회
            printf("%s\n", err_msg);

            file_column_free();
            return -1;
        }
        if ((result_count = recv_result(&_result, select_result_str)) == -1) {
            printf("%s\n", err_msg);

            file_column_free();
            return -1;
        }

        result_print(_result, result_count);
        printf("\n");

        printf("# 조회할 주문번호를 입력하세요.\n");
        printf("입력 : ");
        scanf("%s", check_conNum);
        getchar();
        printf("\n");

        strcpy(condition, "con_num = '");
        strcat(condition, check_conNum);
        strcat(condition, "\'");

        if (_select(condition, "con_num, con_date, client, VAT, in_charge", &select_result_str) == -1) { //입력한 주문번호가 존재하지 않을 때
            printf("%s\n", err_msg);

            file_column_free();
            return -1;
        }
        if ((result_count = recv_result(&_result, select_result_str)) == -1) {
            printf("%s\n", err_msg);

            file_column_free();
            return -1;
        }

        result_print(_result, result_count);
        printf("\n");
        file_column_free();   //수주등록 파일 닫기
        result_free(_result, result_count);


        if (initalizing("contract_item_regi") == -1) { //수주-물품등록 파일 열기
            printf("%s\n", err_msg);

            file_column_free();
            return -1;
        }
        if (_select(condition, "con_num, NO, item_num, item_name, due_date, date_shipment, amount, unit_price, supply_price, tax, total_price", &select_result_str) == -1) {
            printf("%s\n", err_msg);

            file_column_free();
            return -1;
        }
        if ((result_count = recv_result(&_result, select_result_str)) == -1) {
            printf("%s\n", err_msg);

            file_column_free();
            return -1;
        }

        result_print(_result, result_count);
        printf("\n\n");
        file_column_free();   //수주-물품등록 파일 닫기
        result_free(_result, result_count);

        printf("(0) 뒤로가기   (1) 계속조회\n");
        printf("\n입력 : ");
        scanf("%d", &choice);
        getchar();

        if (choice == 0) {
            system("cls");
            break;
        }
        else if (choice == 1) {
            system("cls");
        }
        else {
            printf("\n# 잘못된 입력입니다!\n");
            system("pause");
            system("cls");
        }
    }

    free(check_conNum);
    free(condition);
}