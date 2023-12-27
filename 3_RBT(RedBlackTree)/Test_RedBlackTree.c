#include "RedBlackTree.h"

RBTNode* Nil;

int main(void) {
	RBTNode* Tree = NULL;
	RBTNode* Node = NULL;

	Nil = RBT_CreateNode(0);
	Nil->Color = BLACK;

	while (1) {
		int cmd = 0;
		int param = 0;
		char buffer[10];

		printf("Enter command number :\n");	//메뉴 출력
		printf("(1) Create a node, (2) Remove a node, (3) Search a Node\n");
		printf("(4) Display Tree (5) quit\n");
		printf("command number: ");

		fgets(buffer, sizeof(buffer) - 1, stdin);
		sscanf_s(buffer, "%d", &cmd);

		//1~5 사이 값이 아닌 경우
		if (cmd < 1 || cmd>5) {
			printf("Invalid command number.\n");
			continue;
		}
		//4번인 경우
		else if (cmd == 4) {
			RBT_PrintTree(Tree, 0, 0);	//트리 출력
			printf("\n");
			continue;	//다시 실행
		}
		else if (cmd == 5)	//5번이면
			break;	//반복문 종료

		printf("Enter parameter (1~200) :\n");



		//입력할 값 받기
		fgets(buffer, sizeof(buffer) - 1, stdin);
		sscanf_s(buffer, "%d", &param);

		if (param < 1 || param>200) {		//1~200 사이 값이 아닌 경우
			printf("Invalid parameter. %d\n", param);
			continue;	//다시 실행
		}

		switch (cmd) {
		case 1:		//1번일 때
			RBT_InsertNode(&Tree, RBT_CreateNode(param));	//노드 추가
			break;
		case 2:		//2번일 때
			Node = RBT_RemoveNode(&Tree, param);	
			if (Node == NULL)	//노드 값이 없는 경우
				printf("Not found node to delete : %d\n", param);
			else    //노드 값이 있는 경우
				RBT_DestroyNode(Node);	//해당 노드 삭제
			break;
		case 3:		//3번일 때
			Node = RBT_SearchNode(Tree, param);	//노드 검색
			if (Node == NULL)	//노드 값이 없으면
				printf("Not found node : %d\n", param);
			else                //노드 값이 있으면
				printf("Found Node : %d(Color:%s)\n", Node->Data, (Node->Color == RED) ? "RED" : "BLACK"); //노드의 색을 출력
			break;
		}
		printf("\n");
	}
	
	//프로그램이 종료, Tree를 삭제한다.
	RBT_DestroyNode(Tree);
	return 0;
}