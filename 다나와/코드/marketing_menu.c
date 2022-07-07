#pragma warning(disable:4996)


int marketing_menu() {
	int choice = 0;
	printf("\n ==== < 원하는 메뉴선택 > ====\n\n");
	printf("\t1. 수주등록 \n\t2. 수주현황\n\t0. 뒤로가기\n");
	scanf("%d", &choice);
	getchar();

	return choice;
}