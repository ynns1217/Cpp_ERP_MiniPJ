#ifndef __STRUCT_H__
#define __STRUCT_H__

// ERP 시스템 입고처리에 사용될 구조체와 입고구조 원리

void Create_File(void);
int Init_SampleData(void);
void Insert_WarehousingData(void);
void Insert_WarehousingData_from_BuyingList(void);
void print_Warehousing_state(void);
void delete_Warehousing(void);
void Insert(void);
void edit_minus_table(void);		////생산 넘겨주며 수량 하나씩 빼고 넘겨주기
void edit_plus_table(void);			////입고한 수량만큼 더해주기
void jaego_print1(void);			////최종 재고 수량 출력해서 조회
int Insert_Production_Plan_File(void);
int marketing_menu();
int con_view();
void con_regi_choice();
void Del(void);
void Print_use(void);
void Product(void);
void By_work(void);
void Update_jago(viod);

typedef struct In_WareHouse					// 입고구조체
{
	int num_In_WareHouse;			// 입고순번
	char name_warehouse[20];		// 창고이름
	int num_warehouse;				// 창고번호
	char name_item[20];				// 품목이름
	char num_item[20];					// 품목번호
	char LOT_number[20];			// 품목 루트넘버
	int date;						// 입고날짜
	char name_responsible[20];		// 담당자이름
	int num_responsible;			// 담당자번호
	int num_in;						// 입고수량
	int bill;						// 단가
	int pay_in;						// 공급가액 = 입고수량 * 단가
	int tax;						// 부가세 = 공급가액 * 0.1
	int pay_sum;					// 합계액 = 공급가액 + 부가세;
}warehouse;

typedef struct jaego					// 재고 조회 구조체
{
	int num_Jaego;					// 재고순번
	char name_item[20];				// 품목이름
	char num_item[20];				// 품목번호
	char name_warehouse[20];		// 창고이름
	int num_warehouse;				// 창고번호
	char LOT_number[20];			// 품목 루트넘버
	int date;						// 입고날짜
	int num_chogi_item;				// 초기수량
	int num_in;						// 입고수량
	int num_chulgo_item;			// 출고수량
	int num_jaego_item;				// 최종 재고 수량


}Jaego;

struct Buy_item						// 발주 구조체
{
	int num_buyList;				// 발주번호
	char name_item[20];				// 발주품명
	int num_item;					// 발주품번
	int date;						// 발주날짜
	char name_responsible[20];		// 담당자이름
	int num_responsible;			// 담당자번호
	int num_buy;					// 발주수량
	int bill;						// 단가
	int pay_in;						// 공급가액 = 발주수량 * 단가
	int tax;						// 부가세 = 공급가액 * 0.1
	int pay_sum;					// 합계액 = 공급가액 + 부가세;
	int rest_num_in;				// 남은발주수량(분할 입고될시 남은 입고수량계산을 위함)
};

struct Buy_company					// 거래처구조체
{
	char name_buy_company[20];		// 거래처 이름
	int num_buy_company;			// 거래처 번호
};

struct Person_responsibe			// 담당자구조체
{
	char name_responsible[20];		// 담당자이름
	int num_responsible;			// 담당자번호
};

struct item							// 품목구조체
{
	char name_item[20];				// 품목 품명
	int num_item;					// 품목 품번
	char State[20];					// 계정구분  - 원자재)RawMaterial, 부제품Subsidiary, 상품Product
	int Daily_Output;				// 일일 생산량
	char LOT_number[20];			// RA = 원자재, SU =	부제품, PR = 상품
									// ex) 
};

typedef struct Work_Use			// 자재 사용(작업별) 구조체
{
	char work_order_num[20];	//작업지시번호
	char Product_num[20];		// 품목번호
	char Product_name[20];		// 품목이름
	int Amountused;				//사용수량
	int Performanced_number;	//실적번호
	char LOT[20];				//lot넘버

}workuse;


typedef struct Work_process			// 작업지시 부분 
{
	char work_order_num[20];	//작업지시번호
	char Product_name[20];		//품명
	char Product_num;			//품번
	char client[10];			//이름
	int indicated_quantity;		//지시수량
	int performance_quantity;	//실적수량
	int performance_num;		//실적번호
	char LOT[20];				//실적lot넘버

} Work_process;

typedef struct Work_Productwork		// 자재사용현황(제품별)
{
	int work_order_num;	//작업지시번호(작업지시부분)
	int Product_num;		//품목번호(작업지시부분)
	char Product_name[20];	//품목이름(작업지시부분)
	int LOT;				//lot번호(작업지시부분)
	int indicated_quantity;	//지시수량=실적수량(작업지시부분)
	char item_NUMBER[20];	//물품번호(제품등록부분)
	char item_NAME[20];		//물품명
	char item_LOT[20];		//물품 lot번호
	int Amountused;			//사용수량(입력)

}Work_Productwork;

typedef struct ITEM			// 물품등록
{
	char item_NAME[20];		//물품명
	char item_NUMBER[20];	//물품번호
	char item_TYPE[20];
	int item_GOAL;
	char item_LOT[20];
	char tem_SirealNUMBER[20];
}ITEM;


typedef char element;

typedef struct BOMF_Node {    // BOM 트리 생성을 위한 노드

	struct BOMFNode* LeftChild;
	struct BOMFNode* RightSibling;
	element Data[50];

}BOMFNode;

typedef struct bom            // BOM 등록
{
	int BOM_Num;              // BOM 순번 INT
	char BOM_Code;            // BOM 품번코드 VARCHAR(10)
	char BOM_Name;            // BOM 품명 VARCHAR(20)
	double BOM_Amount;        // BOM 수량 DOUBLE

}BOM;

typedef struct BOM_Foward            // BOM 정전개
{

	int BOM_F_Num;                   // BOM 정전개 순번 INT
	char BOM_F_Code;                 // BOM 정전개 품번코드 VARCHAR(10)
	char BOM_F_Name;                 // BOM 정전개 품명 VARCHAR(20)
	char BOM_F_Material;             // BOM 정전개 계정 VARCHAR(10) 

}BOM_F;

typedef struct BOM_Reverse           // BOM 역전개
{

	int BOM_R_Num;                   // BOM 역전개 순번 INT
	char BOM_R_Code;                 // BOM 역전개 품번코드 VARCHAR(10)
	char BOM_R_Name;                 // BOM 역전개 품명 VARCHAR(20)
	char BOM_R_Material;             // BOM 역전개 계정 VARCHAR(10)

}BOM_R;


typedef struct _con {
	char con_num[10];
	int con_date;
	char client[30];
	int VAT;
	char in_charge[30];

}con;

typedef struct _con_item {
	char con_num[10];
	int NO;
	char item_num[20];
	char item_name[20];
	int due_date;
	int date_shipment;
	int amount;
	int unit_price;
	int supply_price;
	int tax;
	int total_price;
}con_item;

void createTable();
void Create_BOMFile();
void Cre_BOM_Table();
void Cre_Sampleitem();
void Make_BOM();
void Make_BOM_F(BOMFNode*, int);
void Make_BOM_R(BOMFNode*, int);
BOMFNode* BOM_Tree();
BOMFNode* BOM_Create_Node();
void BOM_AddClidNode(BOMFNode*, element);
void BOM_PrintNodesAtLevel(BOMFNode*, int);
BOMFNode* BOMF_FoundNode(BOMFNode*, element);
void Print_ITEM_File();
float print_BOM_Total();
void Print_Select_BOM();

#endif