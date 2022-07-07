#include "local.h"
#include"MiniProject_ERP_1struct.h"

#define SIZE 20
#pragma warning(disable : 4996)

// BOM, BOM_F, BOM_R 테이블 생성
//void Create_BOMFile() { // BOM 테이블 생성
// 
	 //BOM 테이블 생성 : BOM_Num(순번), BOM_Code(품번코드), BOM_Name(품명), BOM_Amount(수량)
	//_create("BOM", "BOM_Num INT BOM_Code VARCHAR(10) BOM_Name VARCHAR(20) BOM_Amount FLOAT");
	 //BOM 정전개 테이블 생성 : BOM_F_Num(순번), BOM_F_Code(품번코드), BOM_F_Name(품명), BOM_F_Material(계정), BOM_F_Amount(수량)
	//_create("BOM_F", "BOM_F_Num INT BOM_F_Code VARCHAR(10) BOM_F_Name VARCHAR(20) BOM_F_Material VARCHAR(20) BOM_F_Amount FLOAT");
	 //BOM 역전개 테이블 생성 : BOM_R_Num(순번), BOM_R_Code(품번코드), BOM_R_Name(품명), BOM_R_Material(계정), BOM_R_Amount(수량)
	//_create("BOM_R", "BOM_R_Num INT BOM_R_Code VARCHAR(10) BOM_R_Name VARCHAR(20) BOM_R_Material VARCHAR(20) BOM_R_Amount FLOAT");
//
//}

// Sample 품목 테이블 생성

// 모품목마다 테이블을 만들어줌.
void Cre_BOM_Table(char Parent_Item[SIZE]) {

	Print_ITEM_File();

	_create(Parent_Item, "BOM_Num INT BOM_Code VARCHAR(10) BOM_Name VARCHAR(20) BOM_Amount FLOAT");

}
// BOM 테이블 생성, 품번코드를 조건으로 물품데이터에서 품번코드, 품명을 받아오고 수량을 입력해줌.
void Make_BOM() {
	system("cls");

	getchar();

	result* _result;
	result* find;
	int result_count;

	//BOMFNode* Root = BOM_Create_Root_Node();
	//BOMFNode* Parent_Node;

	char Select_ITEM[10];
	char Parameter_Insert[1000] = { NULL };
	char temp_int[20] = { 0 };
	char temp_float[20] = { 0 };
	char Select_Parent[SIZE] = { NULL };
	float BOM_AMOUNT = 0; // BOM 수량을 입력하기 위한 변수
	int BOM_NUM = 0; // BOM 순번을 입력하기 위한 변수
	char Select_Cre_Table; // 테이블을 생성하기 위해 CMD창에서 입력받는 변수

	printf("새 모품목을 등록합니까? (Y) : ");     // 모품목을 받아서 새 테이블 만들때, 또는 기존의 테이블을 초기화 할 때 
	scanf("%c", &Select_Cre_Table);
	getchar();

	if (Select_Cre_Table == 'Y') {            // Y를 입력하면 새 테이블을 만들고 다른 입력은 생성 X

		char Parent_Item[SIZE] = { NULL };

		printf("\n");
		Print_ITEM_File();

		printf("새로 만들 테이블을 입력하세요 : ");
		scanf("%s", Parent_Item);

		Cre_BOM_Table(Parent_Item);

		//BOM_AddClidNode(Root, Parent_Item);

	}

	if (initalizing("ITEM") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	system("cls");

	printf("\n======================================= 품목 목록 ===========================================\n");
	print_ITEM();
	printf("\n");

	printf("모품목을 선택해주세요 : ");
	scanf("%s", Select_Parent);
	getchar();

	//Parent_Node = BOMF_FoundNode(Root, Select_Parent);
	//if (Parent_Node == NULL) {
	//   printf("품목이 없습니다.\n");
	//   getch();
	//   continue;
	//}


	file_column_free();

	while (1) {

		if (initalizing(Select_Parent) == -1) {
			printf("%s\n", err_msg);

			file_column_free();

			return -1;
		}

		printf("\n");
		float Total = print_BOM_Total();
		printf("=========================================================\n");
		printf("                                 수량합계 : %.3f\n", Total);
		printf("\n");

		file_column_free();

		if (initalizing("ITEM") == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}

		// BOM_NUM

		while (1) {

			printf("추가할 순번을 입력하세요(1 ~ 99) : ");
			scanf("%d", &BOM_NUM);

			if (BOM_NUM > 0 && BOM_NUM < 99) break;

			else {

				printf("올바른 값을 입력해주세요.\n");
			}
		}

		itoa(BOM_NUM, temp_int, 10);
		strcat(Parameter_Insert, temp_int);
		strcat(Parameter_Insert, ", ");

		printf("추가할 자품목을 입력하세요 : ");
		scanf("%s", Select_ITEM);
		getchar();

		//BOM_AddClidNode(Parent_Node, Select_ITEM);

		char Select_Item_Name[100] = "item_NUMBER =";
		strcat(Select_Item_Name, Select_ITEM);

		if (_select(Select_Item_Name, "item_NUMBER, item_NAME", &select_result_str) == -1) {
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

		// Item_Number
		strcat(Parameter_Insert, "\'");
		strcat(Parameter_Insert, *(_result->_string_data));
		strcat(Parameter_Insert, "\', ");

		// Item_Name
		strcat(Parameter_Insert, "\'");
		strcat(Parameter_Insert, *(_result->next->_string_data));
		strcat(Parameter_Insert, "\', ");

		// BOM_Amount
		printf("자품목의 수량을 입력하세요 : ");
		scanf("%f", &BOM_AMOUNT);
		getchar();

		sprintf(temp_float, "%f", BOM_AMOUNT);
		strcat(Parameter_Insert, temp_float);

		file_column_free();

		if (initalizing(Select_Parent) == -1) {
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

		file_column_free();

		int Stop;

		while (1) {


			printf("\n1. 계속 등록  2. 등록 완료 : ");
			scanf("%d", &Stop);
			getchar();

			if (Stop == 1) break;

			else if (Stop == 2) {
				return;
			}

			else {

				printf("올바른 항목을 입력해주세요.\n");
				continue;
			}
		}
	}
}
// BOM 정전개 테이블 생성
void Make_BOM_F(BOMFNode* Node, int Level) {

	if ((Node->LeftChild != NULL) && (Level > 0))
		Make_BOM_F(Node->LeftChild, Level- 1);

	if ((Node->RightSibling != NULL) && (Level >= 0))
		Make_BOM_F(Node->RightSibling, Level);

	if (Level == 0) {

		int i = 0;
		result* _result;
		result* find;
		int result_count;

		char Parameter_Insert[1000] = { NULL };
		char temp_int[20] = { 0 };
		char temp_float[20] = { 0 };

		char Select_Item_Name[100] = "item_NUMBER = ";
		strcat(Select_Item_Name, Node->Data);

		if (initalizing("ITEM") == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}

		if (_select(Select_Item_Name, "item_NUMBER, item_NAME, item_TYPE", &select_result_str) == -1) {
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

		// BOM_Num
		//BOM_F_NUM++;

		//itoa(BOM_F_NUM, temp_int, 10);
		strcat(Parameter_Insert, temp_int);
		strcat(Parameter_Insert, ", ");

		// Item_Number
		strcat(Parameter_Insert, "\'");
		strcat(Parameter_Insert, *(_result->_string_data));
		strcat(Parameter_Insert, "\', ");

		// Item_Name
		strcat(Parameter_Insert, "\'");
		strcat(Parameter_Insert, *(_result->next->_string_data));
		strcat(Parameter_Insert, "\', ");

		// Item_Type
		strcat(Parameter_Insert, "\'");
		strcat(Parameter_Insert, *(_result->next->next->_string_data));
		strcat(Parameter_Insert, "\'");

		file_column_free();

		if (initalizing("BOM") == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}

		char Select_BOM_CODE[100] = "BOM_Code ="; // BOM_Code = PC01
		strcat(Select_BOM_CODE, Node->Data);

		if (_select(Select_BOM_CODE, "BOM_Amount", &select_result_str) == -1) {
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

		// BOM_Amount
		strcat(Parameter_Insert, ", ");
		sprintf(temp_float,"%f", *(_result->_float_data));
		strcat(Parameter_Insert, temp_float);						
		
		file_column_free();

		if (initalizing("BOM_F") == -1) {
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


		file_column_free();
	}
}
// BOM 역전개 테이블 생성(구현 X)
void Make_BOM_R(BOMFNode* Node, int Level) {


}
// BOM 정전개를 위한 Tree 구조 생성
BOMFNode* BOM_Tree() {

	int i = 0;
	result* _result;
	result* find;
	int result_count;

	char Input_Child_data[SIZE] = { NULL };
	char Find_Parent_data[SIZE] = { NULL };

	int Node_Num = 0;
	int Select = 0;

	
	BOMFNode* Root = BOM_Create_Node("A");

	while (1) {

		system("cls");
		printf("1. 새 항목 등록   2. 기존 항목에 연결\n");
		printf("항목을 선택하세요 : ");
		scanf("%d", &Select);

		if (Select == 1) {

			if (initalizing("ITEM") == -1) {
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}

			if (_select("*", "item_NUMBER", &select_result_str) == -1) {
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

			file_column_free();

			printf("\n");
			result_print(_result, result_count);
			printf("\n");

			printf("루트에 등록할 품번을 입력하세요 : ");
			scanf("%s", Input_Child_data);
			BOM_AddClidNode(Root, Input_Child_data);

			continue;
		}

		else if (Select == 2) {

			BOMFNode* Fine_Node;

			if (initalizing("ITEM") == -1) {
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}

			if (_select("*", "item_NUMBER", &select_result_str) == -1) {
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

			file_column_free();

			printf("\n");
			result_print(_result, result_count);
			printf("\n");

			printf("연결시킬 기존 품번을 검색하세요 : ");
			scanf("%s", Find_Parent_data);

			Fine_Node = BOMF_FoundNode(Root, Find_Parent_data);

			printf("연결하려는 노드의 개수를 입력하세요 : ");
			scanf("%d", &Node_Num);

			for (int i = 0; i < Node_Num; i++) {

				printf("등록할 품번을 입력하세요 : ");
				scanf("%s", Input_Child_data);
				BOM_AddClidNode(Fine_Node, Input_Child_data);
			}

			continue;
		}

		else if (Select == 3)
			break;
		
		else {

			printf("잘못된 입력입니다.\n");
			getch();

			continue;
		}

	}
	
	system("cls");

	return Root;
}
// Root 노드 생성
BOMFNode* BOM_Create_Node(element Sdata[50]) {

	BOMFNode* NewNode = (BOMFNode*)malloc(sizeof(BOMFNode));
	if (NewNode == NULL) {
		printf("Memory Allocation Failed\n");

		return 0;
	}

	NewNode->LeftChild = NULL;
	NewNode->RightSibling = NULL;
	strcpy(NewNode->Data, Sdata);

	return NewNode;
}
// NewNode를 생성 후 NewData[50]의 데이터를 받아 값을 넣어줌. 
void BOM_AddClidNode(BOMFNode* Parent, BOMFNode* Child) {

	if (Parent->LeftChild == NULL)
		Parent->LeftChild = Child;
	else {
		BOMFNode* TempNode = Parent->LeftChild;
		while (TempNode->RightSibling != NULL)
			TempNode = TempNode->RightSibling;
		TempNode->RightSibling = Child;
	}

}
BOMFNode* BOMF_FoundNode(BOMFNode* Node, element S_Data) {
	BOMFNode* tmp = 0;
	if (Node->Data == S_Data)
		return Node;
	if (Node->LeftChild != NULL)
		tmp = BOMF_FoundNode(Node->LeftChild, S_Data);
	if (Node->RightSibling != NULL)
		tmp = BOMF_FoundNode(Node->RightSibling, S_Data);
	return tmp;
}
// 특정 레벨의 노드들을 출력해주는 함수
void BOM_PrintNodesAtLevel(BOMFNode* Root, int Level) {

	if ((Root->LeftChild != NULL) && (Level >= 0))
		BOM_PrintNodesAtLevel(Root->LeftChild, Level - 1);

	if ((Root->RightSibling != NULL) && (Level >= 0))
		BOM_PrintNodesAtLevel(Root->RightSibling, Level);

	if (Level == 0)
	{
		printf("%s\n", Root->Data);
		return;
	}
}
// 선택한 모품목의 항목들을 출력해주는 함수
void Print_Select_BOM(){

	int i = 0;
	result* _result;
	result* find;
	int result_count;

	char Print_Parent_BOM[SIZE] = { NULL };

	if (initalizing("ITEM") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_select("*", "item_NUMBER", &select_result_str) == -1) {
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

	file_column_free();

	result_print(_result, result_count);
	printf("\n");

	printf("모품목을 입력해주세요 : ");
	scanf("%s", Print_Parent_BOM);

	if (initalizing(Print_Parent_BOM) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	printf("\n");
	float Total = print_BOM_Total();

	printf("=========================================================\n");
	printf("                                 수량합계 : %.3f\n", Total);
	printf("\n");
	getch();

	file_column_free();

}
// ITEM 테이블 출력
void Print_ITEM_File() {

	if (initalizing("ITEM") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	printf("======================================= 품목 목록 ===========================================\n");
	print_ITEM();
	printf("\n");
	file_column_free();

}
