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

		printf("Enter command number :\n");	//�޴� ���
		printf("(1) Create a node, (2) Remove a node, (3) Search a Node\n");
		printf("(4) Display Tree (5) quit\n");
		printf("command number: ");

		fgets(buffer, sizeof(buffer) - 1, stdin);
		sscanf_s(buffer, "%d", &cmd);

		//1~5 ���� ���� �ƴ� ���
		if (cmd < 1 || cmd>5) {
			printf("Invalid command number.\n");
			continue;
		}
		//4���� ���
		else if (cmd == 4) {
			RBT_PrintTree(Tree, 0, 0);	//Ʈ�� ���
			printf("\n");
			continue;	//�ٽ� ����
		}
		else if (cmd == 5)	//5���̸�
			break;	//�ݺ��� ����

		printf("Enter parameter (1~200) :\n");



		//�Է��� �� �ޱ�
		fgets(buffer, sizeof(buffer) - 1, stdin);
		sscanf_s(buffer, "%d", &param);

		if (param < 1 || param>200) {		//1~200 ���� ���� �ƴ� ���
			printf("Invalid parameter. %d\n", param);
			continue;	//�ٽ� ����
		}

		switch (cmd) {
		case 1:		//1���� ��
			RBT_InsertNode(&Tree, RBT_CreateNode(param));	//��� �߰�
			break;
		case 2:		//2���� ��
			Node = RBT_RemoveNode(&Tree, param);	
			if (Node == NULL)	//��� ���� ���� ���
				printf("Not found node to delete : %d\n", param);
			else    //��� ���� �ִ� ���
				RBT_DestroyNode(Node);	//�ش� ��� ����
			break;
		case 3:		//3���� ��
			Node = RBT_SearchNode(Tree, param);	//��� �˻�
			if (Node == NULL)	//��� ���� ������
				printf("Not found node : %d\n", param);
			else                //��� ���� ������
				printf("Found Node : %d(Color:%s)\n", Node->Data, (Node->Color == RED) ? "RED" : "BLACK"); //����� ���� ���
			break;
		}
		printf("\n");
	}
	
	//���α׷��� ����, Tree�� �����Ѵ�.
	RBT_DestroyNode(Tree);
	return 0;
}