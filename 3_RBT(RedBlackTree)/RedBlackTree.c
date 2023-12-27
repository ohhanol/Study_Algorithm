#define _CRT_SECURE_NO_WARNINGS
#include "RedBlackTree.h"

extern RBTNode* Nil;

/* 노드 생성 함수
: 동적할당으로 NewNode 생성. 부모 노드부터 데이터 값을 NULL로 초기화하고 Color은 BLACK으로 설정.
그리고 NewNode를 리턴.
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



//노드 삭제 함수: 동적할당 받은 노드를 해제한다
void RBT_DestroyNode(RBTNode* Node) {
	free(Node);
}


/* 트리 삭제 함수
: 오른쪽 자식 노드가 있을 땐 재귀호출하여 맨 아래의 오른쪽 자식 노드로 이동하고,
왼쪽 자식 노드가 있을 땐 마찬가지로 재귀호출하여 맨 아래의 왼쪽 자식 노드로 이동.
마지막 리프 노드까지 가면 왼쪽 자식 노드 값과 오른쪽 자식 노드 값을 삭제.
모든 자식 노드가 없을 경우 마지막 루트에 남은 루트 노드를 반환.*/
void RBT_DestroyTree(RBTNode* Tree) {
	if (Tree->Right != Nil)				// 오른쪽 자식 노드가 있는 경우
		RBT_DestroyTree(Tree->Right);

	if (Tree->Left != Nil)				// 왼쪽 자식 노드가 있는 경우
		RBT_DestroyTree(Tree->Left);

	Tree->Left = Nil;			// 왼쪽 자식 노드 삭제
	Tree->Right = Nil;			// 오른쪽 자식 노드 삭제

	RBT_DestroyNode(Tree);
}




/* 노드 검색 함수
: 레드블랙트리에서 키가 Target인 노드를 검색하고자 한다.
트리에 키가 Target인 노드가 존재하면(성공적인 탐색) 해당 노드를 리턴,
존재하지 않으면(실패한 탐색) NULL을 리턴
*/
RBTNode* RBT_SearchNode(RBTNode* Tree, ElementType Target) {
	if (Tree == Nil)	// 찾고자 하는 노드가 없을 때
		return NULL;

	if (Tree->Data > Target)	// 왼쪽 노드에 값이 없으면
		return RBT_SearchNode(Tree->Left, Target);

	else if (Tree->Data < Target)
		return RBT_SearchNode(Tree->Right, Target);

	else
		return Tree;
}



/* 최소 노드 검색 함수
: 찾고자 하는 노드가 없으면 NULL을 리턴. 트리에 왼쪽 노드 값이 없으면 현재 노드를 리턴.
왼쪽에 자식 노드 값이 있으면 왼쪽으로 내려감
*/
RBTNode* RBT_SearchMinNode(RBTNode* Tree) {
	if (Tree == Nil)
		return Nil;

	if (Tree->Left == Nil)
		return Tree;

	else
		return RBT_SearchMinNode(Tree->Left);
}



/* 노드 삽입함수
: NewNode를 삽입. 삽입할 노드 색은 RED이고 왼쪽 노드, 오른쪽 노드의 값은 Nil로 초기화.
NewNode의 부모가 RED이면 레드와 레드이므로 블랙트리 특성이 깨지기 때문에 재정비
*/
void RBT_InsertNode(RBTNode** Tree, RBTNode* NewNode) {
	RBT_InsertNodeHelper(Tree, NewNode);

	NewNode->Color = RED;
	NewNode->Left = Nil;
	NewNode->Right = Nil;

	RBT_RebuildAfterInsert(Tree, NewNode);
}




// 노드 삽입 위치를 찾는 함수
void RBT_InsertNodeHelper(RBTNode** Tree, RBTNode* NewNode) {
	// 트리 노드가 NULL일 경우
	if ((*Tree) == NULL)	
		(*Tree) = NewNode;

	// 현재 노드보다 삽입노드 데이터값이 더 클 경우
	if ((*Tree)->Data < NewNode->Data) {	
		/* 트리 노드의 오른쪽 자식이 없을 경우
		그 위치에 NewNode를 삽입. NewNode의 부모 노드는 Tree 노드
		*/
		if ((*Tree)->Right == Nil) {
			(*Tree)->Right = NewNode;
			NewNode->Parent = (*Tree);
		}
		//트리 노드에 오른쪽 자식이 있을 경우 오른쪽으로 재귀 호출하여 이동
		else
			RBT_InsertNodeHelper(&(*Tree)->Right, NewNode);
	}


	//현재 노드보다 삽입할 노드 데이터의 값이 더 작을 경우
	else if ((*Tree)->Data > NewNode->Data) {
		if ((*Tree)->Left == Nil) {		//트리 노드의 왼쪽 자식이 없을 경우
			(*Tree)->Left = NewNode;
			NewNode->Parent = (*Tree);
		}
		else   //트리 노드의 왼쪽 자식이 있을 경우
			RBT_InsertNodeHelper(&(*Tree)->Left, NewNode);
	}
}



/* 우회전하는 함수
: LeftChild노드의 오른쪽 자식 노드가 없을 경우 부모 노드를 LeftChild 오른쪽의 부모 노드에 삽입. Parent 노드의 부모와 LeftChild를 연결. 
Parent의 부모 노드가 없을 경우(루트 노드 없음)		LeftChild를 루트 노드에 넣는다. 

Parent가 루트 노드가 아닐 경우
부모 노드의 부모의 오른쪽 자식이 부모일 경우 RightChild 값을 부모 노드의 부모의 왼쪽 자식
의 노드의 값에 삽입. 아니라면 RightChild 값을 부모 노드의 부모의 오른쪽 자식 노드의 값 에 삽입. 

부모 노드를 Right Child의 왼쪽 자식 노드의 값으로 넣는다.
RightChild를 부모 노드의 부모가 된다
*/
void RBT_RotateRight(RBTNode** Root, RBTNode* Parent) {
	RBTNode* LeftChild = Parent->Left;

	Parent->Left = LeftChild->Right;

	if (LeftChild->Right != Nil)	// LeftChild노드의 오른쪽 자식 노드가 없을 경우
		LeftChild->Right->Parent = Parent;

	LeftChild->Parent = Parent->Parent;

	if (Parent->Parent == NULL)		//Parent의 부모 노드가 없을 경우(루트 노드 없음)
		(*Root) = LeftChild;
	else {
		if (Parent == Parent->Parent->Left)		//부모 노드의 부모의 왼쪽 자식이 부모일 경우
			Parent->Parent->Left = LeftChild;
		else
			Parent->Parent->Right = LeftChild;
	}

	LeftChild->Right = Parent;
	Parent->Parent = LeftChild;
}


// 좌회전하는 함수: 우회전하는 함수의 반대
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



/*노드 삽입 후 트리 재정비 함수
 : X노드가 루트 노드가 아니고 X노드의 부모 노드의 색이 빨간색일 경우 반복문을 수행한다.
 */
void RBT_RebuildAfterInsert(RBTNode** Root, RBTNode* X) {
	while (X != (*Root) && X->Parent->Color == RED) {	// X노드가 루트 노드가 아니고 X노드 부모 노드의 색이 빨간색일 경우 반복문을 수행.
		// 1. X노드의 부모 노드가 X노드 부모의 부모 노드의 왼쪽 자식 노드일 경우
		if (X->Parent == X->Parent->Parent->Left) {
			RBTNode* Uncle = X->Parent->Parent->Right;
			if (Uncle->Color == RED) {	// 1-1. Uncle노드의 색이 RED일 경우
				X->Parent->Color = BLACK;
				Uncle->Color = BLACK;
				X->Parent->Parent->Color = RED;

				X = X->Parent->Parent;
			}
			else {						// 1-2. Uncle 노드의 색이 BLACK일 경우
				if (X == X->Parent->Right) {	//1-2-1. X노드가 X노드 부모 노드의 오른쪽 자식 노드일 경우
					X = X->Parent;
					RBT_RotateLeft(Root, X);
				}
				//1-2-2. X노드가 X노드 부모 노드의 왼쪽 자식 노드일 경우
				X->Parent->Color = BLACK;
				X->Parent->Parent->Color = RED;

				RBT_RotateRight(Root, X->Parent->Parent);
			}
		}

		// 2. X노드의 부모 노드가 X노드 부모의 부모 노드의 오른쪽 자식 노드일 경우
		else {							
			RBTNode* Uncle = X->Parent->Parent->Left;
			if (Uncle->Color == RED) {		//2-1. Uncle 노드의 색이 RED일 경우
				X->Parent->Color = BLACK;
				Uncle->Color = BLACK;
				X->Parent->Parent->Color = RED;
				X = X->Parent->Parent;
			}
			else {		//2-2. Uncle 노드의 색이 BLACK일 경우
				if (X == X->Parent->Left) {		//2-2-1. X노드가 X노드 부모의 왼쪽 자식 노드일 경우
					X = X->Parent;
					RBT_RotateRight(Root, X);
				}
				// 2-2-2. X노드가 X노드 부모의 오른쪽 자식 노드일 경우
				X->Parent->Color = BLACK;
				X->Parent->Parent->Color = RED;
				RBT_RotateLeft(Root, X->Parent->Parent);
			}
		}
	}

	(*Root)->Color = BLACK;
}



// 노드 삭제 함수: Target이 NULL일 경우 NULL을 리턴
RBTNode* RBT_RemoveNode(RBTNode** Root, ElementType Data) {
	RBTNode* Removed = NULL;
	RBTNode* Successor = NULL;
	RBTNode* Target = RBT_SearchNode((*Root), Data);

	if (Target == NULL)		//Target이 NULL일 경우
		return NULL;

	if (Target->Left == Nil || Target->Right == Nil) { //Target의 왼쪽 노드가 Nil이거나 Target의 오른쪽 노드가 Nil일 경우
		Removed = Target;
	}
	else {	// Target의 오른쪽 자식 노드, 왼쪽 자식 노드 모두 있을 경우
		Removed = RBT_SearchMinNode(Target->Right);
		Target->Data = Removed->Data;
	}

	if (Removed->Left != Nil)	//삭제하고자 하는 노드의 왼쪽 노드에 값이 없을 경우
		Successor = Removed->Left;
	else    //삭제하고자 하는 노드의 오른쪽 노드에 값이 있을 경우
		Successor = Removed->Right;

	Successor->Parent = Removed->Parent;

	if (Removed->Parent == NULL)		//삭제하고자 하는 노드의 부모 노드의 값이 NULL일 경우
		(*Root) = Successor;
	else {   //삭제하고자 하는 노드가 루트 노드가 아닐 경우
		if (Removed == Removed->Parent->Left)	 // 삭제하고자 하는 노드가 부모 노드의 왼쪽 노드 값일 경우
			Removed->Parent->Left = Successor;
		else    // 삭제하고자 하는 노드가 부모 노드의 오른쪽 노드 값일 경우
			Removed->Parent->Right = Successor;
	}

	if (Removed->Color == BLACK)	//삭제하고자 하는 노드의 색이 BLACK일 경우
		RBT_RebuildAfterRemove(Root, Successor);

	return Removed;
}


/* 노드 삭제 후 트리 재정비 함수
: Sibling을 NULL로 초기화. Successor의 부모 노드가 NULL이 아니고 Successor의 색이 BLACK일 경우 반복문 수행*/
void RBT_RebuildAfterRemove(RBTNode** Root, RBTNode* Successor) {
	RBTNode* Sibling = NULL;

	// Successor의 부모 노드가 NULL이 아니고 Successor의 색이 BLACK일 경우 반복문 수행.
	while (Successor->Parent != NULL && Successor->Color == BLACK) {
		//1. Successor값이 Successor의 부모 노드의 왼쪽 노드일 경우
		if (Successor == Successor->Parent->Left) {
			Sibling = Successor->Parent->Right;
			//1-1. Sibling의 색이 RED일 경우
			if (Sibling->Color == RED) {
				Sibling->Color = BLACK;
				Successor->Parent->Color = RED;
				RBT_RotateLeft(Root, Successor->Parent);
				Sibling = Successor->Parent->Right;
			}
			//1-2 Sibling의 색이 BLACK일 경우
			else {
				//1-2-1. Sibling의 왼쪽 노드와 오른쪽 노드의 색이 모두 BLACK일 경우
				if (Sibling->Left->Color == BLACK && Sibling->Right->Color == BLACK) {
					Sibling->Color = RED;
					Successor = Successor->Parent;
				}
				//1-2-2 Sibling의 왼쪽 노드와 오른쪽 노드의 색이 모두 BLACK이 아닐 경우
				else {
					//1-2-2-1. Sibling의 왼쪽 노드의 색이 RED일 경우
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
		//2. Successor가 부모 노드의 오른쪽 노드일 경우
		else {
			Sibling = Successor->Parent->Left;
			//2-1. Sibling의 색이 RED일 경우
			if (Sibling->Color == RED) {
				Sibling->Color = BLACK;
				Successor->Parent->Color = RED;
				RBT_RotateRight(Root, Successor->Parent);
				Sibling = Successor->Parent->Left;
			}
			//2-2. Sibling의 색이 BLACK일 경우
			else {
				//2-2-1. Sibling의 오른쪽 노드와 왼쪽 노드의 색이 모두 BLACK일 경우
				if (Sibling->Right->Color == BLACK && Sibling->Left->Color == BLACK) {
					Sibling->Color = RED;
					Successor = Successor->Parent;
				}
				//2-2-2.Sibling의 왼쪽 노드와 오른쪽 노드의 색이 모두 BLACK이 아닐 경우
				else {
					//2-2-2-1. Sibling의 오른쪽 노드의 색이 RED일 경우
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



/* 트리 출력 함수
: 노드가 NULL이거나 Nil인 경우 리턴. 노드의 색이 BLACK인 경우 BlackCount++를 해준다
*/
void RBT_PrintTree(RBTNode* Node, int Depth, int BlackCount) {
	int i = 0;
	char c = 'X';
	int v = -1;
	char cnt[100];

	if (Node == NULL || Node == Nil)	//노드가 NULL이거나 Nil인 경우
		return;

	if (Node->Color == BLACK)			//노드의 색이 BLACK인 경우
		BlackCount++;

	if (Node->Parent != NULL) {			//노드의 부모 노드가 NULL이 아닌 경우
		v = Node->Parent->Data;
		if (Node->Parent->Left == Node) //노드가 노드의 부모 노드의 왼쪽 노드일 경우
			c = 'L';
		else  // 노드가 노드의 부모 노드의 왼쪽 노드이 아닐 경우
			c = 'R';
	}

	// 노드의 왼쪽 노드와 오른쪽 노드가 모두 Nil일 경우
	if (Node->Left == Nil && Node->Right == Nil)
		sprintf(cnt, "------ %d", BlackCount);
	
	//노드의 왼쪽 노드와 오른쪽 노드가 Nil이 하나라도 아닐 경우
	else
		sprintf(cnt, "");
	for (i = 0; i < Depth; i++)
		printf("  ");

	printf("%d %s [%c, %d] %s\n", Node->Data, (Node->Color == RED) ? "RED" : "BLACK", c, v, cnt);

	RBT_PrintTree(Node->Left, Depth + 1, BlackCount);
	RBT_PrintTree(Node->Right, Depth + 1, BlackCount);
}