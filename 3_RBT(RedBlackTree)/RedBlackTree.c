#define _CRT_SECURE_NO_WARNINGS
#include "RedBlackTree.h"

extern RBTNode* Nil;

/* ��� ���� �Լ�
: �����Ҵ����� NewNode ����. �θ� ������ ������ ���� NULL�� �ʱ�ȭ�ϰ� Color�� BLACK���� ����.
�׸��� NewNode�� ����.
*/
RBTNode* RBT_CreateNode(ElementType NewData) {
	RBTNode* NewNode = (RBTNode*)malloc(sizeof(RBTNode));
	NewNode->Parent = NULL;
	NewNode->Left = NULL;
	NewNode->Right = NULL;
	NewNode->Data = NewData;
	NewNode->Color = BLACK;

	return NewNode;
}



//��� ���� �Լ�: �����Ҵ� ���� ��带 �����Ѵ�
void RBT_DestroyNode(RBTNode* Node) {
	free(Node);
}


/* Ʈ�� ���� �Լ�
: ������ �ڽ� ��尡 ���� �� ���ȣ���Ͽ� �� �Ʒ��� ������ �ڽ� ���� �̵��ϰ�,
���� �ڽ� ��尡 ���� �� ���������� ���ȣ���Ͽ� �� �Ʒ��� ���� �ڽ� ���� �̵�.
������ ���� ������ ���� ���� �ڽ� ��� ���� ������ �ڽ� ��� ���� ����.
��� �ڽ� ��尡 ���� ��� ������ ��Ʈ�� ���� ��Ʈ ��带 ��ȯ.*/
void RBT_DestroyTree(RBTNode* Tree) {
	if (Tree->Right != Nil)				// ������ �ڽ� ��尡 �ִ� ���
		RBT_DestroyTree(Tree->Right);

	if (Tree->Left != Nil)				// ���� �ڽ� ��尡 �ִ� ���
		RBT_DestroyTree(Tree->Left);

	Tree->Left = Nil;			// ���� �ڽ� ��� ����
	Tree->Right = Nil;			// ������ �ڽ� ��� ����

	RBT_DestroyNode(Tree);
}




/* ��� �˻� �Լ�
: �����Ʈ������ Ű�� Target�� ��带 �˻��ϰ��� �Ѵ�.
Ʈ���� Ű�� Target�� ��尡 �����ϸ�(�������� Ž��) �ش� ��带 ����,
�������� ������(������ Ž��) NULL�� ����
*/
RBTNode* RBT_SearchNode(RBTNode* Tree, ElementType Target) {
	if (Tree == Nil)	// ã���� �ϴ� ��尡 ���� ��
		return NULL;

	if (Tree->Data > Target)	// ���� ��忡 ���� ������
		return RBT_SearchNode(Tree->Left, Target);

	else if (Tree->Data < Target)
		return RBT_SearchNode(Tree->Right, Target);

	else
		return Tree;
}



/* �ּ� ��� �˻� �Լ�
: ã���� �ϴ� ��尡 ������ NULL�� ����. Ʈ���� ���� ��� ���� ������ ���� ��带 ����.
���ʿ� �ڽ� ��� ���� ������ �������� ������
*/
RBTNode* RBT_SearchMinNode(RBTNode* Tree) {
	if (Tree == Nil)
		return Nil;

	if (Tree->Left == Nil)
		return Tree;

	else
		return RBT_SearchMinNode(Tree->Left);
}



/* ��� �����Լ�
: NewNode�� ����. ������ ��� ���� RED�̰� ���� ���, ������ ����� ���� Nil�� �ʱ�ȭ.
NewNode�� �θ� RED�̸� ����� �����̹Ƿ� ��Ʈ�� Ư���� ������ ������ ������
*/
void RBT_InsertNode(RBTNode** Tree, RBTNode* NewNode) {
	RBT_InsertNodeHelper(Tree, NewNode);

	NewNode->Color = RED;
	NewNode->Left = Nil;
	NewNode->Right = Nil;

	RBT_RebuildAfterInsert(Tree, NewNode);
}




// ��� ���� ��ġ�� ã�� �Լ�
void RBT_InsertNodeHelper(RBTNode** Tree, RBTNode* NewNode) {
	// Ʈ�� ��尡 NULL�� ���
	if ((*Tree) == NULL)	
		(*Tree) = NewNode;

	// ���� ��庸�� ���Գ�� �����Ͱ��� �� Ŭ ���
	if ((*Tree)->Data < NewNode->Data) {	
		/* Ʈ�� ����� ������ �ڽ��� ���� ���
		�� ��ġ�� NewNode�� ����. NewNode�� �θ� ���� Tree ���
		*/
		if ((*Tree)->Right == Nil) {
			(*Tree)->Right = NewNode;
			NewNode->Parent = (*Tree);
		}
		//Ʈ�� ��忡 ������ �ڽ��� ���� ��� ���������� ��� ȣ���Ͽ� �̵�
		else
			RBT_InsertNodeHelper(&(*Tree)->Right, NewNode);
	}


	//���� ��庸�� ������ ��� �������� ���� �� ���� ���
	else if ((*Tree)->Data > NewNode->Data) {
		if ((*Tree)->Left == Nil) {		//Ʈ�� ����� ���� �ڽ��� ���� ���
			(*Tree)->Left = NewNode;
			NewNode->Parent = (*Tree);
		}
		else   //Ʈ�� ����� ���� �ڽ��� ���� ���
			RBT_InsertNodeHelper(&(*Tree)->Left, NewNode);
	}
}



/* ��ȸ���ϴ� �Լ�
: LeftChild����� ������ �ڽ� ��尡 ���� ��� �θ� ��带 LeftChild �������� �θ� ��忡 ����. Parent ����� �θ�� LeftChild�� ����. 
Parent�� �θ� ��尡 ���� ���(��Ʈ ��� ����)		LeftChild�� ��Ʈ ��忡 �ִ´�. 

Parent�� ��Ʈ ��尡 �ƴ� ���
�θ� ����� �θ��� ������ �ڽ��� �θ��� ��� RightChild ���� �θ� ����� �θ��� ���� �ڽ�
�� ����� ���� ����. �ƴ϶�� RightChild ���� �θ� ����� �θ��� ������ �ڽ� ����� �� �� ����. 

�θ� ��带 Right Child�� ���� �ڽ� ����� ������ �ִ´�.
RightChild�� �θ� ����� �θ� �ȴ�
*/
void RBT_RotateRight(RBTNode** Root, RBTNode* Parent) {
	RBTNode* LeftChild = Parent->Left;

	Parent->Left = LeftChild->Right;

	if (LeftChild->Right != Nil)	// LeftChild����� ������ �ڽ� ��尡 ���� ���
		LeftChild->Right->Parent = Parent;

	LeftChild->Parent = Parent->Parent;

	if (Parent->Parent == NULL)		//Parent�� �θ� ��尡 ���� ���(��Ʈ ��� ����)
		(*Root) = LeftChild;
	else {
		if (Parent == Parent->Parent->Left)		//�θ� ����� �θ��� ���� �ڽ��� �θ��� ���
			Parent->Parent->Left = LeftChild;
		else
			Parent->Parent->Right = LeftChild;
	}

	LeftChild->Right = Parent;
	Parent->Parent = LeftChild;
}


// ��ȸ���ϴ� �Լ�: ��ȸ���ϴ� �Լ��� �ݴ�
void RBT_RotateLeft(RBTNode** Root, RBTNode* Parent) {
	RBTNode* RightChild = Parent->Right;

	Parent->Right = RightChild->Left;

	if (RightChild->Left != Nil)
		RightChild->Left->Parent = Parent;

	RightChild->Parent = Parent->Parent;

	if (Parent->Parent == NULL)
		(*Root) = RightChild;
	else {
		if (Parent == Parent->Parent->Left)
			Parent->Parent->Left = RightChild;
		else
			Parent->Parent->Right = RightChild;
	}

	RightChild->Left = Parent;
	Parent->Parent = RightChild;
}



/*��� ���� �� Ʈ�� ������ �Լ�
 : X��尡 ��Ʈ ��尡 �ƴϰ� X����� �θ� ����� ���� �������� ��� �ݺ����� �����Ѵ�.
 */
void RBT_RebuildAfterInsert(RBTNode** Root, RBTNode* X) {
	while (X != (*Root) && X->Parent->Color == RED) {	// X��尡 ��Ʈ ��尡 �ƴϰ� X��� �θ� ����� ���� �������� ��� �ݺ����� ����.
		// 1. X����� �θ� ��尡 X��� �θ��� �θ� ����� ���� �ڽ� ����� ���
		if (X->Parent == X->Parent->Parent->Left) {
			RBTNode* Uncle = X->Parent->Parent->Right;
			if (Uncle->Color == RED) {	// 1-1. Uncle����� ���� RED�� ���
				X->Parent->Color = BLACK;
				Uncle->Color = BLACK;
				X->Parent->Parent->Color = RED;

				X = X->Parent->Parent;
			}
			else {						// 1-2. Uncle ����� ���� BLACK�� ���
				if (X == X->Parent->Right) {	//1-2-1. X��尡 X��� �θ� ����� ������ �ڽ� ����� ���
					X = X->Parent;
					RBT_RotateLeft(Root, X);
				}
				//1-2-2. X��尡 X��� �θ� ����� ���� �ڽ� ����� ���
				X->Parent->Color = BLACK;
				X->Parent->Parent->Color = RED;

				RBT_RotateRight(Root, X->Parent->Parent);
			}
		}

		// 2. X����� �θ� ��尡 X��� �θ��� �θ� ����� ������ �ڽ� ����� ���
		else {							
			RBTNode* Uncle = X->Parent->Parent->Left;
			if (Uncle->Color == RED) {		//2-1. Uncle ����� ���� RED�� ���
				X->Parent->Color = BLACK;
				Uncle->Color = BLACK;
				X->Parent->Parent->Color = RED;
				X = X->Parent->Parent;
			}
			else {		//2-2. Uncle ����� ���� BLACK�� ���
				if (X == X->Parent->Left) {		//2-2-1. X��尡 X��� �θ��� ���� �ڽ� ����� ���
					X = X->Parent;
					RBT_RotateRight(Root, X);
				}
				// 2-2-2. X��尡 X��� �θ��� ������ �ڽ� ����� ���
				X->Parent->Color = BLACK;
				X->Parent->Parent->Color = RED;
				RBT_RotateLeft(Root, X->Parent->Parent);
			}
		}
	}

	(*Root)->Color = BLACK;
}



// ��� ���� �Լ�: Target�� NULL�� ��� NULL�� ����
RBTNode* RBT_RemoveNode(RBTNode** Root, ElementType Data) {
	RBTNode* Removed = NULL;
	RBTNode* Successor = NULL;
	RBTNode* Target = RBT_SearchNode((*Root), Data);

	if (Target == NULL)		//Target�� NULL�� ���
		return NULL;

	if (Target->Left == Nil || Target->Right == Nil) { //Target�� ���� ��尡 Nil�̰ų� Target�� ������ ��尡 Nil�� ���
		Removed = Target;
	}
	else {	// Target�� ������ �ڽ� ���, ���� �ڽ� ��� ��� ���� ���
		Removed = RBT_SearchMinNode(Target->Right);
		Target->Data = Removed->Data;
	}

	if (Removed->Left != Nil)	//�����ϰ��� �ϴ� ����� ���� ��忡 ���� ���� ���
		Successor = Removed->Left;
	else    //�����ϰ��� �ϴ� ����� ������ ��忡 ���� ���� ���
		Successor = Removed->Right;

	Successor->Parent = Removed->Parent;

	if (Removed->Parent == NULL)		//�����ϰ��� �ϴ� ����� �θ� ����� ���� NULL�� ���
		(*Root) = Successor;
	else {   //�����ϰ��� �ϴ� ��尡 ��Ʈ ��尡 �ƴ� ���
		if (Removed == Removed->Parent->Left)	 // �����ϰ��� �ϴ� ��尡 �θ� ����� ���� ��� ���� ���
			Removed->Parent->Left = Successor;
		else    // �����ϰ��� �ϴ� ��尡 �θ� ����� ������ ��� ���� ���
			Removed->Parent->Right = Successor;
	}

	if (Removed->Color == BLACK)	//�����ϰ��� �ϴ� ����� ���� BLACK�� ���
		RBT_RebuildAfterRemove(Root, Successor);

	return Removed;
}


/* ��� ���� �� Ʈ�� ������ �Լ�
: Sibling�� NULL�� �ʱ�ȭ. Successor�� �θ� ��尡 NULL�� �ƴϰ� Successor�� ���� BLACK�� ��� �ݺ��� ����*/
void RBT_RebuildAfterRemove(RBTNode** Root, RBTNode* Successor) {
	RBTNode* Sibling = NULL;

	// Successor�� �θ� ��尡 NULL�� �ƴϰ� Successor�� ���� BLACK�� ��� �ݺ��� ����.
	while (Successor->Parent != NULL && Successor->Color == BLACK) {
		//1. Successor���� Successor�� �θ� ����� ���� ����� ���
		if (Successor == Successor->Parent->Left) {
			Sibling = Successor->Parent->Right;
			//1-1. Sibling�� ���� RED�� ���
			if (Sibling->Color == RED) {
				Sibling->Color = BLACK;
				Successor->Parent->Color = RED;
				RBT_RotateLeft(Root, Successor->Parent);
				Sibling = Successor->Parent->Right;
			}
			//1-2 Sibling�� ���� BLACK�� ���
			else {
				//1-2-1. Sibling�� ���� ���� ������ ����� ���� ��� BLACK�� ���
				if (Sibling->Left->Color == BLACK && Sibling->Right->Color == BLACK) {
					Sibling->Color = RED;
					Successor = Successor->Parent;
				}
				//1-2-2 Sibling�� ���� ���� ������ ����� ���� ��� BLACK�� �ƴ� ���
				else {
					//1-2-2-1. Sibling�� ���� ����� ���� RED�� ���
					if (Sibling->Left->Color == RED) {
						Sibling->Left->Color = BLACK;
						Sibling->Color = RED;

						RBT_RotateRight(Root, Sibling);
						Sibling = Successor->Parent->Right;
					}
					Sibling->Color = Successor->Parent->Color;
					Successor->Parent->Color = BLACK;
					Sibling->Right->Color = BLACK;
					RBT_RotateLeft(Root, Successor->Parent);
					Successor = (*Root);
				}
			}
		}
		//2. Successor�� �θ� ����� ������ ����� ���
		else {
			Sibling = Successor->Parent->Left;
			//2-1. Sibling�� ���� RED�� ���
			if (Sibling->Color == RED) {
				Sibling->Color = BLACK;
				Successor->Parent->Color = RED;
				RBT_RotateRight(Root, Successor->Parent);
				Sibling = Successor->Parent->Left;
			}
			//2-2. Sibling�� ���� BLACK�� ���
			else {
				//2-2-1. Sibling�� ������ ���� ���� ����� ���� ��� BLACK�� ���
				if (Sibling->Right->Color == BLACK && Sibling->Left->Color == BLACK) {
					Sibling->Color = RED;
					Successor = Successor->Parent;
				}
				//2-2-2.Sibling�� ���� ���� ������ ����� ���� ��� BLACK�� �ƴ� ���
				else {
					//2-2-2-1. Sibling�� ������ ����� ���� RED�� ���
					if (Sibling->Right->Color == RED) {
						Sibling->Right->Color = BLACK;
						Sibling->Color = RED;
						RBT_RotateLeft(Root, Sibling);
						Sibling = Successor->Parent->Left;
					}
					Sibling->Color = Successor->Parent->Color;
					Successor->Parent->Color = BLACK;
					Sibling->Left->Color = BLACK;
					RBT_RotateRight(Root, Successor->Parent);
					Successor = (*Root);
				}
			}
		}
	}
	Successor->Color = BLACK;
}



/* Ʈ�� ��� �Լ�
: ��尡 NULL�̰ų� Nil�� ��� ����. ����� ���� BLACK�� ��� BlackCount++�� ���ش�
*/
void RBT_PrintTree(RBTNode* Node, int Depth, int BlackCount) {
	int i = 0;
	char c = 'X';
	int v = -1;
	char cnt[100];

	if (Node == NULL || Node == Nil)	//��尡 NULL�̰ų� Nil�� ���
		return;

	if (Node->Color == BLACK)			//����� ���� BLACK�� ���
		BlackCount++;

	if (Node->Parent != NULL) {			//����� �θ� ��尡 NULL�� �ƴ� ���
		v = Node->Parent->Data;
		if (Node->Parent->Left == Node) //��尡 ����� �θ� ����� ���� ����� ���
			c = 'L';
		else  // ��尡 ����� �θ� ����� ���� ����� �ƴ� ���
			c = 'R';
	}

	// ����� ���� ���� ������ ��尡 ��� Nil�� ���
	if (Node->Left == Nil && Node->Right == Nil)
		sprintf(cnt, "------ %d", BlackCount);
	
	//����� ���� ���� ������ ��尡 Nil�� �ϳ��� �ƴ� ���
	else
		sprintf(cnt, "");
	for (i = 0; i < Depth; i++)
		printf("  ");

	printf("%d %s [%c, %d] %s\n", Node->Data, (Node->Color == RED) ? "RED" : "BLACK", c, v, cnt);

	RBT_PrintTree(Node->Left, Depth + 1, BlackCount);
	RBT_PrintTree(Node->Right, Depth + 1, BlackCount);
}