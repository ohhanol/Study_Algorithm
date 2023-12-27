#include <stdio.h>
#include <stdlib.h>

// 이진 검색트리 소스 구현하기

/*
탐색을 위한 트리이다. 부모노드를 기준으로 왼쪽 자식은 부모보다 작은 값,
오른쪽 자식은 부모보다 큰 값을 가진다. 한번씩 비교하면서 탐색 범위를 반씩 줄인다.
탐색, 삭제, 삽입 기능이 있는데 삭제를 할 때에는
1. 자식노드가 없는 경우 -> 그냥 삭제
2. 자식노드가 하나 있는 경우 -> 삭제하려는 노드의 부모와 자식노드를 이어줌
3. 자식노드가 두개 있는 경우 -> 삭제하려는 노드의 오른쪽 하위트리에서 최솟값 찾기. (직후원소)
                           -> 직후원소와 삭제하려는 노드 바꾸기
                              (직후원소가 삭제하려는 노드보다 큰 것들 중에 제일 작으니 왼쪽 하위트리보단 크고 오른쪽 하위트리보단 작게 된다.
각 함수들은 자신의 하위트리에 대해 재귀한다.
단, 트리가 한쪽으로 쏠려있는 경우, list와 효율이 별반 다르지 않다.
*/

typedef int element;

typedef struct BSTNode // BST노드 구조체 정의
{
    struct BSTNode* left;
    struct BSTNode* right;

    element data;
} BSTNode;

BSTNode* createNode(element newData) // 생성 후 초기화
{
    //동적 메모리 할당받아 노드를 생성
    BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));   
    newNode->left = NULL;   //초기값 NULL
    newNode->right = NULL;  //초기값 NULL
    newNode->data = newData;

    return newNode; //노드 초기화 완료
}

void deleteNode(BSTNode* node) // 노드 메모리 해제
{
    free(node);
}
void deletetree(BSTNode* tree) // 트리 삭제 함수
{
    if (tree->right != NULL)
    {
        deletetree(tree->right); // 노드의 오른쪽 자식 있으면 오른쪽 자식 제거
    }
    if (tree->left != NULL)
    {
        deletetree(tree->left); // 노드의 왼쪽 자식 있으면 왼쪽 자식 제거
    }

    tree->left = NULL;  // 다 없애면 NULL로 설정
    tree->right = NULL; // 다 없애면 NULL로 설정

    deleteNode(tree); // 마지막에 트리 본인에 대한 메모리 해제
}

BSTNode* searchNode(BSTNode* tree, element target) // 찾으려는 값 target
{
    if (tree == NULL)   //현재 노드 Tree가 NULL이면 NULL 반환
        return NULL;
    if (target < tree->data) // 현재 노드의 데이터가 target보다 크면 왼쪽 노드로 가서 탐색
    {
        return searchNode(tree->left, target);
    }
    else if (target > tree->data) //현재 노드의 데이터가 target보다 작으면 오른쪽 노드로 가서 탐색
    {
        return searchNode(tree->right, target);
    }
    else // 두가지가 아닌 경우 Tree의 데이터와 target이 일치
    {
        return tree;    
    }
}

BSTNode* searchMinNode(BSTNode* tree) // 최솟값 노드 찾기(즉, 제일 왼쪽 아래, 왼쪽 자식 없는 노드)
{
    if (tree == NULL)
        return NULL;

    if (tree->left == NULL) // 더이상 왼쪽 자식이 없을 때 tree가 최솟값이다
    {
        return tree;
    }
    else // 자식이 존재하면 searchMinNode 함수 재귀호출
    {
        return searchMinNode(tree->left);
    }
}

void insertNode(BSTNode* tree, BSTNode* child) // 노드 삽입
{
    if (tree->data < child->data) // 현재 노드값이 자식 노드값보다 작으면
    {
        if (tree->right == NULL) // 오른쪽 자식 없으면 오른쪽 자식 child 대입
        {
            tree->right = child;
        }
        else // 오른쪽 자식이 있으면 오른쪽 자식의 오른쪽으로 이동
        {
            insertNode(tree->right, child);
        }
    }

    else if (tree->data > child->data) // 삽입하고자 하는 값이 크다면
    {
        if (tree->left == NULL) // 왼쪽 자식이 없으면 왼쪽에 대입
        {
            tree->left = child;
        }
        else // 왼쪽 자식이 있으면 왼쪽 자식노드에 대해 재귀호출
        {
            insertNode(tree->left, child); 
        }
    }
}

BSTNode* removeNode(BSTNode* tree, BSTNode* parent, element target)
{   //삭제할 노드의 아래에 있는 노드들 중에서 최솟값을 가지는 노드를 삭제할 노드의 위치에 위치시킴
    BSTNode* removed = NULL; // 삭제될 원소

    if (tree == NULL) // tree가 비어있으면 그냥 반환한다
        return NULL;

    if (tree->data > target) // target이 현재 노드값보다 작으면 왼쪽 탐색
    {
        removed = removeNode(tree->left, tree, target);
    }
    else if (tree->data < target) // target이 현재 노드의 값보다 크다면 오른쪽 탐색
    {
        removed = removeNode(tree->right, tree, target);
    }
    else // 둘다 아니라면 목표값을 이미 찾은 상태. 재귀를 반복하면서 target이 노드의 키값과 일치하는 경우가 나옴
    {
        removed = tree;

        if (tree->left == NULL && tree->right == NULL) // 리프노드인 경우 바로 삭제
        {
            if (parent->left == tree)
                parent->left = NULL;
            else
                parent->right = NULL;
        }
        else 
        {
            if (tree->left != NULL && tree->right != NULL) // 자식이 양쪽 다 있는 경우
            {
                // 최솟값 노드를 찾아 제거한 뒤 현재의 노드에 위치시킴
                BSTNode* minNode = searchMinNode(tree->right);
                minNode = removeNode(tree, NULL, minNode->data);
                tree->data = minNode->data;
            }
            else // 자식이 하나만 있는경우
            {
                // temp를 선언하여 값을 삭제하기 전에 자식 노드들을 제자리에 위치시킴
                BSTNode* temp = NULL;
                if (tree->left != NULL)
                    temp = tree->left;
                else
                    temp = tree->right;

                if (parent->left == tree)
                    parent->left = temp;
                else
                    parent->right = temp;
            }
        }
    }
    return removed;
}
void inorderPrintTree(BSTNode* node)
{
    //노드의 데이터를 출력하는 함수
    if (node == NULL)
    {
        return;
    }

    inorderPrintTree(node->left); // 왼쪽 하위트리 재귀호출
    printf("%d ", node->data);

    inorderPrintTree(node->right); // 오른쪽 하위트리 재귀호출
}

int main()
{
    //노드 생성
    BSTNode* tree = createNode(123);
    BSTNode* node = NULL;

    //트리에 노드 추가
    insertNode(tree, createNode(22));
    insertNode(tree, createNode(9918));
    insertNode(tree, createNode(424));
    insertNode(tree, createNode(17));
    insertNode(tree, createNode(3));
    insertNode(tree, createNode(98));
    insertNode(tree, createNode(34));
    insertNode(tree, createNode(760));
    insertNode(tree, createNode(317));
    insertNode(tree, createNode(1));

    //트리 출력
    printf("BST :  ");
    inorderPrintTree(tree);
    printf(" \n\n");

    //특정 노드 삭제
    printf("98 삭제 중 . . . \n");

    node = removeNode(tree, NULL, 98);
    deleteNode(node);

    printf("삭제 후 BST :  ");

    inorderPrintTree(tree);
    printf("\n\n");

    //새 노드 삽입
    printf("111 삽입 중. . . \n");

    insertNode(tree, createNode(111));
    printf("삽입 후 BST :  ");
    inorderPrintTree(tree);
    printf("\n");

    //트리 소멸
    deletetree(tree);

    return 0;
}
