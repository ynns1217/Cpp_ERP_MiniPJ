#include "local.h"
#include"MiniProject_ERP_1struct.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

void Create_File(void)
{
	// [수주등록]
	_create("contract_regi", "con_num VARCHAR(10) con_date INT client VARCHAR(20) VAT INT in_charge VARCHAR(20)");

	// [수주등록-물품등록]
	_create("contract_item_regi", "con_num VARCHAR(10) NO INT item_num VARCHAR(50) item_name VARCHAR(50) due_date INT date_shipment INT amount INT unit_price INT supply_price INT tax INT total_price INT");

	// 손님테이블 생성
	_create("CUSTOMER", "customer VARCHAR(20)");
	
	// 입고테이블 서버에 생성
	_create("In_WareHouse", "num_In_WareHouse INT name_warehouse VARCHAR(20) num_warehouse INT name_item VARCHAR(20) num_item VARCHAR(20) LOT_number VARCHAR(20)  date INT name_responsible VARCHAR(20) num_responsible INT num_in INT bill INT pay_in INT tax INT pay_sum INT");
							// 입고순번				창고이름						창고번호			품목명					품번			품목로트넘버				날짜		담당자명							담당자번호		입고수량		단가		공급가		세금		합계액
	
	// 발주테이블 서버에 생성
	_create("Buy_item", "num_BuyList INT item_NAME VARCHAR(20) item_NUMBER VARCHAR(20) item_LOT VARCHAR(20) date INT name_responsible VARCHAR(20) num_responsible INT num_buy INT bill INT pay_in INT tax INT pay_sum INT rest_num_in INT");
	//						발주번호			품목명				품번					품목로트넘버				날짜			담당자명						담당자번호		발주수량		단가		공급가액		세금			합계액			남은발주수량
	
	// 거래처테이블 서버에 생성
	_create("Buy_company", "name_buy_company VARCHAR(20) num_buy_company INT");
	//							거래처명						거래처번호
	
	// 담당자테이블 서버에 생성
	_create("Person_responsibe", "name_responsible VARCHAR(20) num_responsible INT");
	//								담당자명							담당자번호
	
	// 품목테이블 서버에 생성
	_create("ITEM", "item_NAME VARCHAR(20) item_NUMBER VARCHAR(20) item_TYPE VARCHAR(20) item_GOAL INT item_LOT VARCHAR(20) item_SirealNUMBER VARCHAR(20)");
	//				품목명					품번						계정상태				일일생산량		폼목로트넘버				시리얼넘버
	
	// 창고고테이블 서버에 생성
	_create("WareHouse", "name_warehouse VARCHAR(30) num_warehouse INT");
	//						창고이름						창고번호

	// <생산계획등록>

	_create("Production_Plan_Registration", "Item_Number VARCHAR(20) Name VARCHAR(20) Daily_Capacity INT Order VARCHAR(20) ETC INT Quantity INT");
	//Item_Number(품번) INT Name(품명) Daily_Capacity(일 생산량) Order(순서) ETC(작업예정일) Quantity(수량)


	//<작업지시등록>

	_create("Work_Order_Registration", "Due_Date INT Quantity INT Work_Instruction_Number VARCHAR(20) LOT VARCHAR(20) Item_Number VARCHAR(20) Name VARCHAR(20) Customer VARCHAR(20)");
	//Work Instruction Number에 (제품구분+(공정)+날짜+번호) 들어감
	//Due_Date(납기일) Quantity(지시수량) Work_Instruction_Number(작업지시번호) LOT(LOT) Item_Number(품번) Name(품명) Customer(고객)
	
	// 자제사용현황(작업별) 테이블 생성
	_create("Work_Use", "Work_Instruction_Number VARCHAR(20) Item_Number VARCHAR(20) Name VARCHAR(20) Amountused INT Performanced_number INT LOT_NO VARCHAR(20)");
	//                   작업지시번호		        ,품번 INT				,품명       CHAR       ,사용수량 INT , 실적번호           INT, LOT NO

	_create("performance", "Work_Instruction_Number VARCHAR(20) Item_Number VARCHAR(20) Name VARCHAR(20) Customer VARCHAR(20) Quantity INT performance_quantity INT performance_num VARCHAR(20) LOT VARCHAR(20)");
	//work_order_num(작업지시번호) Item_Number(품번) Name(품명) Customer(고객) Quantity(지시수량) performance_quantity(실적수량) performance_num(실적번호) LOT(LOT)


	//자재사용현황(제품별) 테이블 생성
	_create("Product_usage_status", "Work_Instruction_Number VARCHAR(20) Name VARCHAR(20) Item_Number VARCHAR(20) Quantity INT LOT_NO VARCHAR(20) item_NAME VARCHAR(20) item_NUMBER VARCHAR(20) item_LOT VARCHAR(20) Amountused INT");
	//								, 작업지시번호             , 품번               ,품명				          ,지시수량    ,lot번호   ,         제품사용품번 INT    ,   제품 사용품명       , 아이템 lot번호     ,사용수량              

	// 재고테이블 서버에 생성
	_create("Jaego", "num_jaego INT name_item VARCHAR(20) num_item VARCHAR(20) name_warehouse VARCHAR(20) num_warehouse INT LOT_number VARCHAR(20)  date INT  chogi_item INT ibgo_item INT chulgo_item INT jaego_item INT");

	_create("product_warehous", "Work_Instruction_Number VARCHAR(20) performance_num VARCHAR(20) Item_Number VARCHAR(20) Name VARCHAR(20) performance_quantity INT Customer VARCHAR(20) LOT VARCHAR(20) stock_num VARCHAR(20) stock_date INT stock_warehouse VARCHAR(20) stock_location VARCHAR(20) stock_count INT");
	//Work_Instruction_Number(작업지시번호) performance_num(실적번호) Product_num(품번) Name(품명) performance_quantity(실적수량) Customer(고객) LOT stock_num(입고번호) stock_date(입고일자) stock_warehouse(입고창고) stock_location(입고장소) stock_count(입고수량) 
}

int Init_SampleData(void)
{
	// 입고테이블 샘플데이터 삽입
	if (initalizing("In_WareHouse") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	//if (_insert("1, 'Warehouse1', 1999, 'CPU','CP10', 'CP20220308', 20220305, 'SamplePerson1', 199, 100, 990, 99000, 9900, 108900") == -1)
	//{
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	//if (_insert("2, 'Warehouse2', 2999, 'HARD', 'HR10', 'HR20220308', 20220307,  'SamplePerson1', 199, 20, 1000, 20000, 2000, 22000") == -1)
	//{
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	//if (_insert("3, 'Warehouse1', 1999, 'MAINBORAD', 'MB10', 'MB20220308', 20220301, 'SamplePerson1', 199, 100, 100, 10000, 1000, 11000") == -1)
	//{
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	int num_Warehousing_List = 0;
	//print_data();
	//printf("\n");
	
	file_column_free();


	// 발주테이블 샘플데이터 삽입
	if (initalizing("Buy_item") == -1) 
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	/*if (_insert("1, 'CPU','CP10','CP20220308', 20220304, 'SamplePerson1', 199, 100, 1000, 10000, 1000, 11000, 100") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	if (_insert("2, 'MONITOR', 'MO10', 'MO20220308', 20220304, 'SamplePerson2', 299, 200, 2000, 40000, 4000, 44000, 100") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("3, 'CASE', 'CA10','CA20220308', 20220304, 'SamplePerson1', 199, 300, 3000, 90000, 9000, 99000, 100") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}*/

	//print_data();
	//printf("\n");
	
	
	file_column_free();


	// 거래처테이블 샘플데이터 삽입
	if (initalizing("Buy_company") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'Buyer1', 199999") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	//print_data();
	//printf("\n");
	file_column_free();



	// 담당자테이블 샘플데이터 삽입
	if (initalizing("Person_responsibe") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'SamplePerson1', 199") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'SamplePerson2', 299") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	//print_data();
	//printf("\n");
	
	file_column_free();

	// 수주등록테이블 샘플데이터 삽입
	if (initalizing("contract_regi") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'001', 20220101, '(주)다나와', 1, '최윤진'") == -1) {
		//1.물품명 cpu 2.물품번호 cp10 3.물품계정구분 meterial 4.일생산량 100 5.LOT번호 cp20220308 6.시리얼 번호 c19999p19
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	
	file_column_free();

	//수주-물품
	if (initalizing("contract_item_regi") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	
	if (_insert("'001', 1, 'PC10', 'PC1', 20220331, 20220329, 10, 10000, 200000, 20000, 180000") == -1) {
		//1.물품명 cpu 2.물품번호 cp10 3.물품계정구분 meterial 4.일생산량 100 5.LOT번호 cp20220308 6.시리얼 번호 c19999p19
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	file_column_free();

	// 품목테이블 샘플데이터 삽입
	if (initalizing("ITEM") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	if (_insert("'PC1','PC10','product',100,'PC20220301','P19999P11'") == -1) {
		//1.물품명 cpu 2.물품번호 cp10 3.물품계정구분 meterial 4.일생산량 100 5.LOT번호 cp20220308 6.시리얼 번호 c19999p19
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'CPU','CP10','meterial',0,'CP20220308','C19999P19'") == -1) {
		//1.물품명 cpu 2.물품번호 cp10 3.물품계정구분 meterial 4.일생산량 100 5.LOT번호 cp20220308 6.시리얼 번호 c19999p19
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'HARD','HR10','meterial',0,'HR20220308','H1999R19'") == -1) {
		//1.물품명 hard 2.물품번호 hr10 3.물품계정구분 meterial 4.일생산량 100 5.LOT번호 hr20220308 6.시리얼 번호 h1999r19
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'KEYBORAD','KE10','submeterial',0,'KE20220308','K1999E19'") == -1) {
		//1.물품명 keyborad 2.물품번호 ke10 3.물품계정구분 submeterial 4.일생산량 100 5.LOT번호 ke20220308 6.시리얼 번호 k1999e19
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'MAINBORAD','MB10','meterial',0,'MB20220308','M1999B19'") == -1) {
		//1.물품명 mainborad 2.물품번호 mb10 3.물품계정구분 meterial 4.일생산량 100 5.LOT번호 mb20220308 6.시리얼 번호 m1999b19
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'MONITOR','MO10','submeterial',0,'MO20220308','M1999O19'") == -1) {
		//1.물품명 monitor 2.물품번호 mo10 3.물품계정구분 submeterial 4.일생산량 100 5.LOT번호 mo20220308 6.시리얼 번호 m1999o19
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'CASE','CA10','meterial',100,'CA20220308','C1999A19'") == -1) {
		//1.물품명 case 2.물품번호 ca10 3.물품계정구분 meterial 4.일생산량 100 5.LOT번호 ca20220308 6.시리얼 번호 c1999a19
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	//print_data();
	//printf("\n");
	
	file_column_free();

	// 창고테이블 샘플데이터 삽입
	if (initalizing("WareHouse") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'Warehouse1', 1999 ") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}


	//print_data();
	//printf("\n");
	file_column_free();

	//자재사용현황 샘플데이터 입력
	if (initalizing("Work_Use") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	file_column_free();

	//작업지시 샘플데이터 입력
	if (initalizing("performance") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	/*if (_insert("'1000', 'CA10', '미들형본체', '김철수', 5 , 5, 101, '9'") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'2000', 'PR10', '레이저프린터', '김똥개', 10, 10, 102, '7'") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("'3000', 'PC10', '데스크탑PC', '강산들', 18, 10, 103, '8'") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}*/
	file_column_free();

	//자재사용 제품별 샘플입력
	if (initalizing("Product_usage_status") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	file_column_free();

	// 재고테이블 샘플데이터 삽입
	if (initalizing("Jaego") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("1, 'CPU', 'CP10', 'Warehouse1', 1999, 'CP20220308', 20220305, 10, 0, 0, 0") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert("2, 'HARD', 'HR10', 'Warehouse1', 1999, 'CP20220308', 20220305, 10, 0, 0, 0") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	if (_insert("3, 'KEYBOARD', 'KE10', 'Warehouse1', 1999, 'CP20220308', 20220305, 10, 0, 0, 0") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	if (_insert("4, 'MAINBOARD', 'MB10', 'Warehouse1', 1999, 'CP20220308', 20220305, 10, 0, 0, 0") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	if (_insert("5, 'MONITOR', 'MO10', 'Warehouse1', 1999, 'CP20220308', 20220305, 10, 0, 0, 0") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	if (_insert("6, 'CASE', 'CA10', 'Warehouse1', 1999, 'CP20220308', 20220305, 0, 0, 0, 0") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	//print_data();
	//printf("\n");

	file_column_free();

	char* values1 = "20210910, 15, 'W02109000002', NULL, 'PC02', '데스크탑PC', '사는회사'";
	char* values2 = "20210325, 10, 'W02109000007', NULL, 'PC04', '데스크탑PC2', '우리회사'";

	if (initalizing("Work_Order_Registration") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	//if (_insert(values1) == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	//if (_insert(values2) == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}
	file_column_free();

	// 손님넣기
	if (initalizing("CUSTOMER") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	//if (_insert("'유세준'") == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	//if (_insert("'박세준'") == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	//if (_insert("'여세준'") == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	//if (_insert("'참세준'") == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	//if (_insert("'오세준'") == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	//if (_insert("'김세준'") == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	// 파일을 닫기
	file_column_free();
	
}