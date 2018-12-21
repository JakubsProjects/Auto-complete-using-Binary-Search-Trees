/*bst.h*/
//*************************Given to us by professor****************************************
//
// Binary Search Tree ADT header file.
//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS251, Spring 2017
//

// make sure this header file is #include exactly once:
#pragma once


//
// BST type declarations:
//
typedef char*  BSTKey;
typedef struct BSTValue
{
	char *X;
	long long  Y;
} BSTValue;

typedef struct BSTNode
{
	BSTKey    Key;
	BSTValue  Value;
	struct BSTNode  *Left;
	struct BSTNode  *Right;
} BSTNode;

typedef struct BST
{
	BSTNode *Root;
	int      Count;
} BST;


//
// BST API: function prototypes
//
BST *BSTCreate();
BST *BuildTree(char *filename1);
int  BSTCompareKeys(BSTKey key1, BSTKey key2);
BSTNode *BSTSearch(BST *tree, BSTKey key);
int  BSTSearchDepth(BST *tree, BSTKey key);
int  BSTInsert(BST *tree, BSTKey key, BSTValue value);
void NumberOfMatches(BSTNode *root, char *inputline, int *count);
void NumberOfMatches(BSTNode *root, char *inputline, int *count);
int       BSTCount(BST *tree);
int       BSTHeight(BST *tree);
//BSTValue  BSTDelete(BST *tree, BSTKey key);
