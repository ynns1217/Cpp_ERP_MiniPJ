#include "local.h"
#include"MiniProject_ERP_1struct.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#pragma warning(disable : 4098)


int main(void)
{
	system("mode con cols=200 lines=50");
	time_t timer;
	struct tm* t;
	timer = time(NULL);
	t = localtime(&timer);

	int today_date = 0; 
	today_date = ((t->tm_year + 1900)*10000) + ((t->tm_mon + 1) * 100) + (t->tm_mday);	// 오늘 날짜( 20220304 꼴 )

	// printf("%d", today_date);

	//테이블생성 및 초기데이터 삽입
	Create_File();												// 파일생성함수 ( MiniProject_ERP_initSampleData 에 정의 - 선언은 헤더파일 )
	Init_SampleData();				// 파일내부에 샘플정보(초기정보)를 insert하는 함수 ( MiniProject_ERP_initSampleData 에 정의 - 선언은 헤더파일 )
	
	//========================================= 실행부 ===========================================



	while (1)
	{
		int Select_main_menu = 0;
		system("cls");
		printf("\n ==== < 원하는 메뉴선택 > ====\n\n");
		printf("\t1. 생산\n\t2. 입고/발주\n\t3. 자재\n\t4. 영업\n\t5. 프로그램 종료\n");
		scanf("%d", &Select_main_menu);

		if (Select_main_menu == 1)
		{
			while (1)
			{
				system("cls");
				int Select_make_menu = 0;
				printf("\n ==== < 원하는 메뉴선택 > ====\n\n");
				printf("\t1. 자재사용관리\n\t2. 작업실적 및 생산품입고\n\t3. 생산계획 및 작업지시등록 \n\t4. 뒤로가기\n");
				scanf("%d", &Select_make_menu);

				if (Select_make_menu == 1)
				{
					while (1)
					{
						system("cls");
						int memunum, menu = 0;

						printf("\n ==== < 원하는 메뉴선택 > ====\n\n");
						printf("\t1. 자재사용현황조회\n\t2. 자재사용현황등록\n\t3. 삭제\n\t4. 뒤로가기\n");
						scanf("%d", &menu);

						if (menu == 1)
						{
							system("cls");
							Print_use();
						}
						else if (menu == 2)
						{
							system("cls");
							printf("\n ==== < 원하는 메뉴선택 > ====\n\n");
							printf("\t1. 작업별자재사용현황\n\t2. 제품별자재사용현황\n\t3. 뒤로가기\n");
							scanf("%d", &memunum);

							if (memunum == 1)	// 작업지시부분 오픈
							{
								system("cls");
								By_work();
								//choijong_jaego_print_all();
								choijong_jokup_print();
							
							}

							else if (memunum == 2)
							{
								system("cls");
								Product();
								choijong_jaego_print_all();
								system("pause");

							}
						}
						else if (menu == 3)
						{
							system("cls");
							Del();
							system("pause");
						}
						else if (menu == 4)
						{
							break;
						}

					}
				}
				else if (Select_make_menu == 2)
				{
					int select;
					while (1) {
						printf("\n ==== < 원하는 메뉴선택 > ====\n\n");
						printf("\t1. 작업실적등록\n\t2. 생산품 입고처리\n\t3. 뒤로가기\n");
						scanf("%d", &select);
						switch (select) {
						case 1:
							system("cls");
							Registration_work_performance();
							break;
						case 2:
							system("cls");
							Production_warehousing();
							break;
						default:
							break;
						}
						break;
					}
				}

				else if (Select_make_menu == 3)	// 생산계획테이블 값 삽입
				{
					while (1)
					{
						printf("\n ==== < 원하는 메뉴선택 > ====\n\n");
						printf("\t1. 생산계획 \n\t2. 작업지시등록\n\t3. 뒤로가기\n");
						int Select_plan = 0;
						scanf("%d", &Select_plan);

						if (Select_plan == 1)
						{
							printf("\n ==== < 원하는 메뉴선택 > ====\n\n");
							printf("\t1. 생산계획등록 \n\t2. BOM\n\t3. BOM출력\n\t4. 뒤로가기\n");
							int Select_manufature_plan = 0;
							scanf("%d", &Select_manufature_plan);

							if (Select_manufature_plan == 1)
							{
								int num = 0;
								num = Insert_Production_Plan_File();
								int a = chulgo_jaego_print();
								if (a > 0)
								{
									printf("======================================\n");
									printf("생산하러가자이\n");
									printf("======================================\n");
									//Update_jago(num);
									system("pause");

								}

								else
								{
									printf("======================================\n");
									printf("발주하러가자이\n");
									printf("======================================\n");
									insertOrderData();
									system("pause");
								}

							}
							else if (Select_manufature_plan == 2)
							{
								Make_BOM();
							}
							else if (Select_manufature_plan == 3)
							{
								Print_Select_BOM();
							}
							else if (Select_manufature_plan == 4)
							{
								break;
							}
							
						}
						else if (Select_plan == 2)
						{
							Insert_Work_order_File();
						}
						else if (Select_plan == 3)
						{
							break;
						}
					}
				}

				else if (Select_make_menu == 4)
				{
					break;
				}
			}

		}

		else if (Select_main_menu == 2)
		{
			while (1)
			{
				int Select = 0;
				printf("\n ==== < 원하는 메뉴선택 > ====\n\n");
				printf("\t1. 발주 \n\t2. 입고\n\t3. 뒤로가기\n");
				scanf("%d", &Select);

				if (Select == 1) // 발주
				{
					while (1)
					{
						system("cls");
						int Select_balju = 0;
						printf("\n ==== < 원하는 메뉴선택 > ====\n\n");
						printf("\t1. 발주등록\n\t2. 발주조회\n\t3. 발주삭제\n\t4. 뒤로가기\n");
						scanf("%d", &Select_balju);

						if (Select_balju == 1) // 1-1.발주등록
						{
							system("cls");
							insertOrderData();
							system("pause");
						}
						else if (Select_balju == 2)// 1-2.발주조회
						{
							system("cls");
							orderList();
							system("pause");

						}
						else if (Select_balju == 3) // 1-3. 발주삭제
						{
							system("cls");
							deleteOrderData();
							system("pause");
						}
						else if (Select_balju == 4) // 1-4. 뒤로가기
						{
							system("cls");
							break;
						}
						else
						{
							printf(" 잘못된 입력값입니다.\n");
							while (getchar() != '\n');
						}
					}
				}

				else if (Select == 2)	// 입고
				{

					while (1)
					{
						system("cls");
						int Select_ibgo = 0;
						printf("\n ==== < 원하는 메뉴선택 > ====\n\n");
						printf("\t1. 예외입고 \n\t2. 발주입고\n\t3. 입고현황\n\t4. 뒤로가기\n");
						//printf(" 1. 예외입고\t2. 발주입고\t3. 입고현황\t4. 입고삭제\t5. 뒤로가기\n");
						scanf("%d", &Select_ibgo);

						if (Select_ibgo == 1)	// 2-1.예외입고
						{
							system("cls");
							Insert_WarehousingData();
							system("pause");
						}

						else if (Select_ibgo == 2)	// 2-2.발주입고
						{
							system("cls");
							Insert_WarehousingData_from_BuyingList();
							system("pause");
						}

						else if (Select_ibgo == 3)	// 2-3.입고현황
						{
							system("cls");
							print_Warehousing_state();
							system("pause");

						}

						else if (Select_ibgo == 4)	// 2-4.뒤로가기
						{
							system("cls");
							break;
						}
						/*
						else if (Select_ibgo == 4)	// 2-4.입고삭제
						{
							system("cls");
							delete_Warehousing();
						}

						else if (Select_ibgo == 5)	// 2-5.뒤로가기
						{
							system("cls");
							break;
						}
						*/
						else
						{
							printf(" 잘못된 값입니다.\n");
							while (getchar() != '\n');
						}
					}
				}
				else if (Select == 3)	// 뒤로가기
				{
					break;
				}

				else
				{
					printf(" 잘못된 입력값 입니다\n");
					while (getchar() != '\n');
				}
			}
		}

		else if (Select_main_menu == 3)	// 자재
		{
			while (1)
			{
				int switch_escape = 0;
				int option1;

				system("cls");

				printf("\n ==== < 원하는 메뉴선택 > ====\n\n");
				printf("\t1. 현재고현황 \n\t2. 재고이동\n\t3. 뒤로가기\n");

				scanf("%d", &option1);

				system("cls");

				switch (option1)
				{

				case 1:
					printf("\t현 재고 현황\n");
					printf("======================================\n");
					jaego_print();
					break;

				case 2:
					printf("\t재고 사용하기 \n");
					printf("======================================\n");
					// 사용할 재고 입력 
					// (모든 조건 검색해서 하나라도 있으면 생산하러가고 갯수 하나씩 줄이기)
					// 재고 0 이면 발주로 보내고 입고 받은 재고번호 받아서 update




					 //jogun();

					//if (jaego_item <= 0)
					//{
					//	printf("발주하러 가자이\n");
					//	printf("\n");

					//ibgo_jaego_print();

					//	printf("\n");
					//	printf("\n");
					//	break;
					//}

					int a = chulgo_jaego_print();
					if (a > 0)
					{
						printf("======================================\n");
						printf("생산하러가자이\n");
						printf("======================================\n");
						system("pause");

					}

					else
					{
						printf("======================================\n");
						printf("발주하러가자이\n");
						printf("======================================\n");
						insertOrderData();
						system("pause");
					}
					//else
					//{
					//	printf("\n");
					//	printf("생산하러 가자이\n");
					//	printf("\n");

					break;



				case 3:
					switch_escape = 1;
					break;

				default:
					printf("잘못된 입력입니다!\n");
				}

				if (switch_escape == 1) break;
			}
		}

		else if (Select_main_menu == 4)	// 수주
		{
		while (1) {
			int main_choice = 0, produc_choice = 0, material_choice = 0, marketing_choice = 0;

			marketing_choice = marketing_menu();
			if (marketing_choice == 1) {
				system("cls");
				con_regi_choice();
			}
			else if (marketing_choice == 2) {
				system("cls");
				con_view();
			}
			else if (marketing_choice == 0) { //뒤로가기
				system("cls");
				break;
			}
			else { //이상한 값 입력
				printf("# 잘못된 입력입니다!\n");
				system("pause");
				system("cls");
			}
		}
		}
		else if (Select_main_menu == 5)	// 종료
		{
		exit(-1);
		}

 
		
	}

	file_column_free();
	return 0;
}