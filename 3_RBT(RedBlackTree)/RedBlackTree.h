#pragma once
#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include<stdio.h>
#include<stdlib.h>

typedef int ElementType;

typedef struct tagRBTNode {
	struct tagRBTNode* Parent;	//부모노드
	struct tagRBTNode* Left		//왼쪽 노드
	struct tagRBTNode* Right;	//오른쪽 노드

	enum { RED, BLACK }Color;

	ElementType Data;
} RBTNode;


//RedBlackTree에서 사용될 함수 정의
void RBT_DestroyTree(RBTNode* Tree);

RBTNode* RBT_CreateNode(ElementType NewData);
void RBT_DestroyNode(RBTNode* Node);

RBTNode* RBT_SearchNode(RBTNode* Tree, ElementType Target);
RBTNode* RBT_SearchMinNode(RBTNode* Tree);
void RBT_InsertNode(RBTNode** Tree, RBTNode* NewNode);
void RBT_InsertNodeHelper(RBTNode** Tree, RBTNode* NewNode);
RBTNode* RBT_RemoveNode(RBTNode** Root, ElementType Target);
void RBT_RebuildAfterInsert(RBTNode** Tree, RBTNode* NewNode);
void RBT_RebuildAfterRemove(RBTNode** Root, RBTNode* X);

void RBT_PrintTree(RBTNode* Node, int Depth, int BlackCount);
void RBT_RotateLeft(RBTNode** Root, RBTNode* Parent);
void RBT_RotateRight(RBTNode** Root, RBTNode* Parent);

#endif