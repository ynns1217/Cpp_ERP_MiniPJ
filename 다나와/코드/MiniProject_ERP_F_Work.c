#include "local.h"
#include"MiniProject_ERP_1struct.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

void By_work(void)
{
    result* _result = NULL;
    result* find;
    int result_count = 0;
    workuse   WU;

    int Select = 0;
    char temp_int[20] = { 0 };
    char select_WU[100];
    char Parameter_Insert[1000] = { NULL };
    char select_num_work_Insert[1000] = { NULL };

    //작업지시 폴더 오픈
    if (initalizing("performance") == -1)
    {
        printf("%s\n", err_msg);

        file_column_free();
        return -1;
    }
    print_data();      //목록출력
    printf("\n");

    printf("\n===============================================================================================\n");
    printf("\n작업지시번호를 선택해주세요. : "); // 작업지시 번호 출력
    scanf("%s", &select_WU);

    char select_num_work[100] = "Work_Instruction_Number=";
    strcat(select_num_work_Insert, "\'");
    strcat(select_num_work_Insert, select_WU);      // 양식 선언
    strcat(select_num_work_Insert, "\'");
    strcat(select_num_work, select_num_work_Insert);

    if (_select(select_num_work, "Work_Instruction_Number, Item_Number, Name,performance_num, LOT", &select_result_str) == -1) {   // 만든 양식을 토대로 창고목록에서 내부 칼럼정보를 선택해 받아옴
        printf("%s\n", err_msg);

        file_column_free();
        return -1;
    } // 작업지시번호, 품번, 품명,작업실적번호, LOT 받아옴

    if ((result_count = recv_result(&_result, select_result_str)) == -1) {      // select로 받아온 정보를 _result 포인트 구조체에 멤버로 저장함
        printf("%s\n", err_msg);

        file_column_free();
        return -1;
    }

    //Performance_number 지시번호
    strcat(Parameter_Insert, "\'");
    strcat(Parameter_Insert, *(_result->_string_data));
    strcat(Parameter_Insert, "\', ");

    //num_item
    strcat(Parameter_Insert, "\'");
    strcat(Parameter_Insert, *(_result->next->_string_data));
    strcat(Parameter_Insert, "\', ");

    // name_item
    strcat(Parameter_Insert, "\'");
    strcat(Parameter_Insert, *(_result->next->next->_string_data));
    strcat(Parameter_Insert, "\', ");

    //Amountused 사용수량
    int use = 0;
    printf("\n사용수량를 입력해주세요.");
    scanf("%d", &use);

    itoa(use, temp_int, 10);
    strcat(Parameter_Insert, temp_int);
    strcat(Parameter_Insert, ",");

    //Performanced_number
    strcat(Parameter_Insert, "\'");
    strcat(Parameter_Insert, *(_result->next->next->next->_string_data));
    strcat(Parameter_Insert, "\', ");

    //LOT_NO
    strcat(Parameter_Insert, "\'");
    strcat(Parameter_Insert, *(_result->next->next->next->next->_string_data));
    strcat(Parameter_Insert, "\'");
    file_column_free();

    printf("\n%s를 입력하셨습니다.\n", Parameter_Insert);
    printf("\n===============================================================================================\n");
    printf("계속하려면 엔터를 눌러주세요~\n");
    printf("\n");
    _getch();

    if (initalizing("Work_Use") == -1) {      // 작업별 자재사용 테이블 오픈
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
    printf("\n\n");
    file_column_free();

    return;
}

void Product(void)
{
    result* _result = NULL;
    result* find;
    int result_count = 0;
    workuse   WU;

    int Select = 0;
    char temp_int[20] = { 0 };
    char select_WU[100];
    char Parameter_Insert[1000] = { NULL };
    char Num_item[20] = { 0 };            //물품번호를 입력받을 문자열 변수

    //작업지시테이블 오픈
    if (initalizing("performance") == -1)
    {
        printf("%s\n", err_msg);

        file_column_free();
        return -1;
    }
    print_data();      //목록출력
    printf("\n");

    printf("\n===============================================================================================\n");
    printf("\n                           작업지시번호를 선택해주세요. : "); // 작업지시 번호 출력
    scanf("%s", &select_WU);

    char select_num_work[100] = "Work_Instruction_Number=";
    strcat(select_num_work, select_WU);      // 양식 선언

    if (_select(select_num_work, "Work_Instruction_Number, Item_Number, Name,performance_num, LOT", &select_result_str) == -1) {   // 만든 양식을 토대로 창고목록에서 내부 칼럼정보를 선택해 받아옴
        printf("%s\n", err_msg);

        file_column_free();
        return -1;
    } // 작업지시번호, 품번, 품명,작업실적번호, LOTNO 받아옴

    if ((result_count = recv_result(&_result, select_result_str)) == -1) {      // select로 받아온 정보를 _result 포인트 구조체에 멤버로 저장함
        printf("%s\n", err_msg);

        file_column_free();
        return -1;
    }


    //Performance_number 지시번호
    strcat(Parameter_Insert, "\'");
    strcat(Parameter_Insert, *(_result->_string_data));
    strcat(Parameter_Insert, "\', ");

    // name_item
    strcat(Parameter_Insert, "\'");
    strcat(Parameter_Insert, *(_result->next->next->_string_data));
    strcat(Parameter_Insert, "\', ");

    //num_item
    strcat(Parameter_Insert, "\'");
    strcat(Parameter_Insert, *(_result->next->_string_data));
    strcat(Parameter_Insert, "\', ");

    //지시수량
    strcat(Parameter_Insert, "\'");
    strcat(Parameter_Insert, *(_result->next->next->next->_string_data));
    strcat(Parameter_Insert, "\', ");

    //LOT번호
    strcat(Parameter_Insert, "\'");
    strcat(Parameter_Insert, *(_result->next->next->next->next->_string_data));
    strcat(Parameter_Insert, "\', ");

    //result_free(_result, result_count);         // 결과값 저장 노드(동적할당)헤제
    file_column_free();


    //물품테이블 오픈
    if (initalizing("ITEM") == -1) {
        printf("%s\n", err_msg);

        file_column_free();
        return -1;
    }
    print_data();            // 물품 목록출력
    printf("\n");

    printf("\n===============================================================================================\n");
    printf("\n                                  물품이름을 입력해주세요.");
    scanf("%s", Num_item);

    char num_item[100] = "item_NAME=";      //문자열 변수선언
    strcat(num_item, Num_item);

    if (_select(num_item, " item_NAME, item_NUMBER, item_LOT", &select_result_str) == -1) {   // 만든 양식을 토대로 창고목록에서 내부 칼럼정보를 선택해 받아옴
        printf("%s\n", err_msg);

        file_column_free();
        return -1;
    } // 물품명, 물품번호, 물품lot번호 받아옴
    if ((result_count = recv_result(&_result, select_result_str)) == -1) {      // select로 받아온 정보를 _result 포인트 구조체에 멤버로 저장함
        printf("%s\n", err_msg);

        file_column_free();
        return -1;
    } //구조체 저장

    file_column_free();
    //물품명


    strcat(Parameter_Insert, "\'");
    strcat(Parameter_Insert, *(_result->_string_data));
    strcat(Parameter_Insert, "\', ");

    //물품번호
    strcat(Parameter_Insert, "\'");
    strcat(Parameter_Insert, *(_result->next->_string_data));
    strcat(Parameter_Insert, "\', ");

    //물품lot넘버
    strcat(Parameter_Insert, "\'");
    strcat(Parameter_Insert, *(_result->next->next->_string_data));
    strcat(Parameter_Insert, "\', ");


    //사용수량
    //Amountused 사용수량
    int use = 0;
    printf("\n사용수량를 입력해주세요.");
    scanf("%d", &use);

    itoa(use, temp_int, 10);
    strcat(Parameter_Insert, temp_int);

    printf("\n%s를 입력하셨습니다.\n", Parameter_Insert);
    printf("\n===============================================================================================\n");
    printf("계속하려면 엔터를 눌러주세요~\n");
    printf("\n");
    _getch();

    //제품별 오픈
    if (initalizing("Product_usage_status") == -1)
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
    printf("\n\n");
    file_column_free();

}

void Print_use(void)
{
    int two_menu = 0;
    printf("\n ==== < 원하는 메뉴선택 > ====\n\n");
    printf("\t1. 자재사용현황 작업별\n\t2. 자재사용현황 제품별\n\t3. 뒤로가기 \n");
    scanf("%d", &two_menu);

    if (two_menu == 1)
    {
        if (initalizing("Work_Use") == -1)
        {
            printf("%s\n", err_msg);

            file_column_free();
            return -1;
        }
        print_data();
        printf("계속하려면 엔터를 눌러주세요~\n");
        printf("\n");
        _getch();
        file_column_free();

    }
    else if (two_menu == 2)
    {
        if (initalizing("Product_usage_status") == -1)
        {
            printf("%s\n", err_msg);

            file_column_free();
            return -1;
        }
        print_data();
        printf("계속하려면 엔터를 눌러주세요~\n");
        printf("\n");
        _getch();
        file_column_free();

    }

    return;
}

void Del(void)
{
    int submenu = 0;
    printf("\n ==== < 원하는 메뉴선택 > ====\n\n");
    printf("\t1. 작업별 자재사용\n\t2. 제품별 자재사용\n\t3. 뒤로가기 \n");
    scanf("%d", &submenu);

    //자재사용 삭제
    if (submenu == 1)
    {
        char delnum[20] = { '\0' };

        if (initalizing("Work_Use") == -1)      //자재사용 테이블 오픈
        {
            printf("%s\n", err_msg);

            file_column_free();
            return -1;
        }
        print_data();
        printf("삭제 할 작업지시번호를 입력해주세요");
        scanf("%s", delnum);

        char conditional[100];
        sprintf(conditional, "Work_Instruction_Number='%s'", delnum);      // 조건문

        if (_delete(conditional) == -1)
        {
            printf("%s\n", err_msg);

            file_column_free();
            return -1;
        }
        print_data();

        printf("\n");

        file_column_free();

    }

    else if (submenu == 2)
    {
        char delnum[20] = { '\0' };

        if (initalizing("Product_usage_status") == -1)
        {
            printf("%s\n", err_msg);

            file_column_free();
            return -1;
        }
        print_data();

        printf("삭제 할 작업지시번호를 입력해주세요");
        scanf("%s", delnum);

        char conditional[100];
        sprintf(conditional, "Work_Instruction_Number='%s'", delnum);      // 조건문

        if (_delete(conditional) == -1)
        {
            printf("%s\n", err_msg);

            file_column_free();
            return -1;
        }

        print_data();
        printf("\n");
        file_column_free();

    }

}