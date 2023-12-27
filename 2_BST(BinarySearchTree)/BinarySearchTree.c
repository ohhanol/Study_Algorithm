#include <stdio.h>
#include <stdlib.h>

// ���� �˻�Ʈ�� �ҽ� �����ϱ�

/*
Ž���� ���� Ʈ���̴�. �θ��带 �������� ���� �ڽ��� �θ𺸴� ���� ��,
������ �ڽ��� �θ𺸴� ū ���� ������. �ѹ��� ���ϸ鼭 Ž�� ������ �ݾ� ���δ�.
Ž��, ����, ���� ����� �ִµ� ������ �� ������
1. �ڽĳ�尡 ���� ��� -> �׳� ����
2. �ڽĳ�尡 �ϳ� �ִ� ��� -> �����Ϸ��� ����� �θ�� �ڽĳ�带 �̾���
3. �ڽĳ�尡 �ΰ� �ִ� ��� -> �����Ϸ��� ����� ������ ����Ʈ������ �ּڰ� ã��. (���Ŀ���)
                           -> ���Ŀ��ҿ� �����Ϸ��� ��� �ٲٱ�
                              (���Ŀ��Ұ� �����Ϸ��� ��庸�� ū �͵� �߿� ���� ������ ���� ����Ʈ������ ũ�� ������ ����Ʈ������ �۰� �ȴ�.
�� �Լ����� �ڽ��� ����Ʈ���� ���� ����Ѵ�.
��, Ʈ���� �������� ����ִ� ���, list�� ȿ���� ���� �ٸ��� �ʴ�.
*/

typedef int element;

typedef struct BSTNode // BST��� ����ü ����
{
    struct BSTNode* left;
    struct BSTNode* right;

    element data;
} BSTNode;

BSTNode* createNode(element newData) // ���� �� �ʱ�ȭ
{
    //���� �޸� �Ҵ�޾� ��带 ����
    BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));   
    newNode->left = NULL;   //�ʱⰪ NULL
    newNode->right = NULL;  //�ʱⰪ NULL
    newNode->data = newData;

    return newNode; //��� �ʱ�ȭ �Ϸ�
}

void deleteNode(BSTNode* node) // ��� �޸� ����
{
    free(node);
}
void deletetree(BSTNode* tree) // Ʈ�� ���� �Լ�
{
    if (tree->right != NULL)
    {
        deletetree(tree->right); // ����� ������ �ڽ� ������ ������ �ڽ� ����
    }
    if (tree->left != NULL)
    {
        deletetree(tree->left); // ����� ���� �ڽ� ������ ���� �ڽ� ����
    }

    tree->left = NULL;  // �� ���ָ� NULL�� ����
    tree->right = NULL; // �� ���ָ� NULL�� ����

    deleteNode(tree); // �������� Ʈ�� ���ο� ���� �޸� ����
}

BSTNode* searchNode(BSTNode* tree, element target) // ã������ �� target
{
    if (tree == NULL)   //���� ��� Tree�� NULL�̸� NULL ��ȯ
        return NULL;
    if (target < tree->data) // ���� ����� �����Ͱ� target���� ũ�� ���� ���� ���� Ž��
    {
        return searchNode(tree->left, target);
    }
    else if (target > tree->data) //���� ����� �����Ͱ� target���� ������ ������ ���� ���� Ž��
    {
        return searchNode(tree->right, target);
    }
    else // �ΰ����� �ƴ� ��� Tree�� �����Ϳ� target�� ��ġ
    {
        return tree;    
    }
}

BSTNode* searchMinNode(BSTNode* tree) // �ּڰ� ��� ã��(��, ���� ���� �Ʒ�, ���� �ڽ� ���� ���)
{
    if (tree == NULL)
        return NULL;

    if (tree->left == NULL) // ���̻� ���� �ڽ��� ���� �� tree�� �ּڰ��̴�
    {
        return tree;
    }
    else // �ڽ��� �����ϸ� searchMinNode �Լ� ���ȣ��
    {
        return searchMinNode(tree->left);
    }
}

void insertNode(BSTNode* tree, BSTNode* child) // ��� ����
{
    if (tree->data < child->data) // ���� ��尪�� �ڽ� ��尪���� ������
    {
        if (tree->right == NULL) // ������ �ڽ� ������ ������ �ڽ� child ����
        {
            tree->right = child;
        }
        else // ������ �ڽ��� ������ ������ �ڽ��� ���������� �̵�
        {
            insertNode(tree->right, child);
        }
    }

    else if (tree->data > child->data) // �����ϰ��� �ϴ� ���� ũ�ٸ�
    {
        if (tree->left == NULL) // ���� �ڽ��� ������ ���ʿ� ����
        {
            tree->left = child;
        }
        else // ���� �ڽ��� ������ ���� �ڽĳ�忡 ���� ���ȣ��
        {
            insertNode(tree->left, child); 
        }
    }
}

BSTNode* removeNode(BSTNode* tree, BSTNode* parent, element target)
{   //������ ����� �Ʒ��� �ִ� ���� �߿��� �ּڰ��� ������ ��带 ������ ����� ��ġ�� ��ġ��Ŵ
    BSTNode* removed = NULL; // ������ ����

    if (tree == NULL) // tree�� ��������� �׳� ��ȯ�Ѵ�
        return NULL;

    if (tree->data > target) // target�� ���� ��尪���� ������ ���� Ž��
    {
        removed = removeNode(tree->left, tree, target);
    }
    else if (tree->data < target) // target�� ���� ����� ������ ũ�ٸ� ������ Ž��
    {
        removed = removeNode(tree->right, tree, target);
    }
    else // �Ѵ� �ƴ϶�� ��ǥ���� �̹� ã�� ����. ��͸� �ݺ��ϸ鼭 target�� ����� Ű���� ��ġ�ϴ� ��찡 ����
    {
        removed = tree;

        if (tree->left == NULL && tree->right == NULL) // ��������� ��� �ٷ� ����
        {
            if (parent->left == tree)
                parent->left = NULL;
            else
                parent->right = NULL;
        }
        else 
        {
            if (tree->left != NULL && tree->right != NULL) // �ڽ��� ���� �� �ִ� ���
            {
                // �ּڰ� ��带 ã�� ������ �� ������ ��忡 ��ġ��Ŵ
                BSTNode* minNode = searchMinNode(tree->right);
                minNode = removeNode(tree, NULL, minNode->data);
                tree->data = minNode->data;
            }
            else // �ڽ��� �ϳ��� �ִ°��
            {
                // temp�� �����Ͽ� ���� �����ϱ� ���� �ڽ� ������ ���ڸ��� ��ġ��Ŵ
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
    //����� �����͸� ����ϴ� �Լ�
    if (node == NULL)
    {
        return;
    }

    inorderPrintTree(node->left); // ���� ����Ʈ�� ���ȣ��
    printf("%d ", node->data);

    inorderPrintTree(node->right); // ������ ����Ʈ�� ���ȣ��
}

int main()
{
    //��� ����
    BSTNode* tree = createNode(123);
    BSTNode* node = NULL;

    //Ʈ���� ��� �߰�
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

    //Ʈ�� ���
    printf("BST :  ");
    inorderPrintTree(tree);
    printf(" \n\n");

    //Ư�� ��� ����
    printf("98 ���� �� . . . \n");

    node = removeNode(tree, NULL, 98);
    deleteNode(node);

    printf("���� �� BST :  ");

    inorderPrintTree(tree);
    printf("\n\n");

    //�� ��� ����
    printf("111 ���� ��. . . \n");

    insertNode(tree, createNode(111));
    printf("���� �� BST :  ");
    inorderPrintTree(tree);
    printf("\n");

    //Ʈ�� �Ҹ�
    deletetree(tree);

    return 0;
}
