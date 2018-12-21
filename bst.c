/*bst.c*/
//*************************Given to us by professor****************************************
//
// Binary Search Tree ADT implementation file.
//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS251, Spring 2017
//

// ignore stdlib warnings if working in Visual Studio:
#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "bst.h"


//
// BSTCreate: dynamically creates and returns an empty
// binary search tree:
//
BST *BSTCreate()
{
	BST *tree;

	tree = (BST *)malloc(sizeof(BST));
	tree->Root = NULL;
	tree->Count = 0;

	return tree;
}


//
// BSTCompareKeys: compares key1 and key2, returning
//   value < 0 if key1 <  key2
//   0         if key1 == key2
//   value > 0 if key1 >  key2
//
int BSTCompareKeys(BSTKey key1, BSTKey key2)
{
	if (strcmp(key1, key2) < 0)
		return -1;
	else if (strcmp(key1, key2) == 0)
		return 0;
	else
		return 1;
}

//Duplicate funtion but compares "n" number of chars we want to compare
int BSTCompareKeys2(BSTKey key1, BSTKey key2)
{
	if (strncmp(key1, key2, strlen(key1)) < 0)
		return -1;
	else if (strncmp(key1, key2, strlen(key1)) == 0)
		return 0;
	else
		return 1;
}

//Duplicate funtion that uses to compare a specific number of elements
BSTNode *BSTSearch2(BST *tree, BSTKey key)
{
	BSTNode *cur = tree->Root;

	//
	// search the tree to see if it contains a matching key:
	//
	while (cur != NULL)
	{
		
		if (BSTCompareKeys2(key, cur->Key) == 0)  // found!
			return cur;
		else if (BSTCompareKeys2(key, cur->Key) < 0)  // smaller, go left:
		{
			cur = cur->Left;
		}
		else  // larger, go right:
		{
			cur = cur->Right;
		}
	}

	// if we get here, we fell out of the tree, and didn't find it:
	return NULL;
}


//
// BSTSearch: searches the binary search tree for a node containing the
// same key.  If a match is found, a pointer to the node is returned, 
// otherwise NULL is returned.
//
BSTNode *BSTSearch(BST *tree, BSTKey key)
{
	BSTNode *cur = tree->Root;

	//
	// search the tree to see if it contains a matching key:
	//
	while (cur != NULL)
	{
		if (BSTCompareKeys(key, cur->Key) == 0)  // found!
			return cur;
		else if (BSTCompareKeys(key, cur->Key) < 0)  // smaller, go left:
		{
			cur = cur->Left;
		}
		else  // larger, go right:
		{
			cur = cur->Right;
		}
	}

	// if we get here, we fell out of the tree, and didn't find it:
	return NULL;
}



//
// BSTSearchDepth: searches the binary search tree for a node containing the
// same key, returning the depth of that node if found.  The root node is 
// considered depth 0, the next level down is a depth of 1, and so forth.
// If a matching key is not found, the function returns a depth of -1.
//
int BSTSearchDepth(BST *tree, BSTKey key)
{
	BSTNode *cur = tree->Root;
	int depth = 0;

	//
	// search the tree to see if it contains a matching key:
	//
	while (cur != NULL)
	{
		if (BSTCompareKeys(key, cur->Key) == 0)  // found!
			return depth;
		else if (BSTCompareKeys(key, cur->Key) < 0)  // smaller, go left:
		{
			cur = cur->Left;
		}
		else  // larger, go right:
		{
			cur = cur->Right;
		}

		depth++;
	}

	// if we get here, we fell out of the tree, and didn't find it:
	return -1;
}


//
// BSTInsert: inserts the given (key, value) pair into the binary search
// tree.  Returns true (non-zero) if the insert was successful, returns 
// false (0) if the given key is already in the tree -- in which case the
// given (key, value) pair is not inserted.
//
int BSTInsert(BST *tree, BSTKey key, BSTValue value)
{
	BSTNode *prev = NULL;
	BSTNode *cur = tree->Root;

	//
	// first we search the tree to see if it already contains key:
	//
	while (cur != NULL)
	{
		if (BSTCompareKeys(key, cur->Key) == 0)  // already in tree, failed:
			return 0;
		else if (BSTCompareKeys(key, cur->Key) < 0)  // smaller, go left:
		{
			prev = cur;
			cur = cur->Left;
		}
		else  // larger, go right:
		{
			prev = cur;
			cur = cur->Right;
		}
	}

	// 
	// If we get here, tree does not contain key, so insert new node
	// where we fell out of tree:
	//
	BSTNode *T = (BSTNode *)malloc(sizeof(BSTNode));
	T->Key = key;
	T->Value = value;
	T->Left = NULL;
	T->Right = NULL;

	//
	// link T where we fell out of tree -- after prev:
	//
	if (prev == NULL)  // tree is empty, insert @ root:
	{
		tree->Root = T;
	}
	else if (BSTCompareKeys(key, prev->Key) < 0)  // smaller, insert to left:
	{
		prev->Left = T;
	}
	else  // larger, insert to right:
	{
		prev->Right = T;
	}

	tree->Count++;

	return 1;  // success:
}

//Function Builds the tree by stripping the word and inputting it into tree
BST *BuildTree(char *filename1)
{//Declaration of variables, and opening file
	char anotherarray[512];
	FILE *file1 = fopen(filename1, "r");
	BSTValue  value;
	BST *tree = BSTCreate();
	char *token = NULL;
	char *token2 = NULL;
	long long weight;

	//int anotherarrayline = (sizeof(anotherarray)/ sizeof(anotherarray[0]));
	//fgets(anotherarray, 512, filename1);

	while (fgets(anotherarray, 512, file1) != NULL) {  //While we are not at end of line
		anotherarray[strcspn(anotherarray, "\r\n")] = '\0';
		token = strtok(anotherarray, "\t");  //Strip the input

		weight = atoll(token);  //Make it a number
		value.Y = weight;  //Store info
		// printf(" weight: %lld ", weight);

		token2 = strtok(NULL, "\n");  //Strip till end of line
		BSTKey key1 = (BSTKey)malloc((strlen(token2) + 1) * sizeof(char)); //allocate memory to store info
		strcpy(key1, token2);  //Store info

		// printf(" netid: %s\n ", key1);
		BSTInsert(tree, key1, value);  //Insert node into tree

	}
	//printf("Leaving\n");
	fclose(file1); //Close file
	return tree; //return the tree
}
//
// BSTPrintInorder: prints the nodes of the given binary search
// tree inorder to the console.
//
// NOTE: "pf" is a print function that must be declared like this
// (though the name "pf" doesn't really matter):
//
//  void pf(BSTNode *cur)
//  { ...}
//
// When you call, pass pf and then you'll be able to control 
// what gets printed when a node is "visited".
//


//
// BSTCount: returns # of nodes in the tree.
//
int BSTCount(BST *tree)
{
	return tree->Count;
}

//For our suggest function
int BSTSubTreeCount(BSTNode *root)
{//Sets count to 1 (to count the head node)
	int count = 1;
	BSTNode *cur = root;
	if (cur == NULL) { //If NULL return 0
		return 0;
	}
	else {//otherwise recurseively call itself and return the count(counts number of Subtrees exist)
		count = count + BSTSubTreeCount(cur->Left);
		count = count + BSTSubTreeCount(cur->Right);
		return count;
	}
}

//return the number of matches that there are
void NumberOfMatches(BSTNode *root, char *inputline, int *count) {
	if (root == NULL) {// if null reutrn 0
		return 0;
	}
	else {//otherwise recurseively call itself and return the count(counts number of matches that exist)
		NumberOfMatches(root->Left, inputline, count);
		NumberOfMatches(root->Right, inputline, count);
		if ((BSTCompareKeys2(inputline, root->Key)) == 0) {
			*count = 1 + *count; //no need for return because pass by reference
		}
	}
}

//Function to store the actual matches
void StoreNumberOfMatches(BSTNode *root, char *inputline, int *count, BSTValue *value) {
	if (root == NULL) {
		return;
	}

	else {
		//recurseively call itself
		StoreNumberOfMatches(root->Left, inputline, count, value);
		StoreNumberOfMatches(root->Right, inputline, count, value);
		if ((BSTCompareKeys2(inputline, root->Key)) == 0) {
			value[*count].X = root->Key;  //store the key
			value[*count].Y = root->Value.Y;  //store the value
			*count = 1 + *count; //Count gets updated due to pass by reference
		}
	}

}

//Sort function
void sort(BSTValue *value, int size, int userInputSize) {
	//Declaring variables
	int i = 0;
	int j = 0;
	//int k = 0;
	int indexSmallest = value[0].Y;
	BSTValue temp;

	//for loop going throught the whole thing
	for (i = 0; i < size- 1; ++i) {

		// Find index of smallest remaining element
		indexSmallest = i;
		for (j = i; j < size; ++j) {

			if ((value[j].Y == value[indexSmallest].Y) && (strcmp(value[j].X, value[indexSmallest].X) <= 0)) {
				indexSmallest = j;		//update to smaller value if found
			}
			else if (value[j].Y > value[indexSmallest].Y)
			{
				indexSmallest = j;
				//printf("Running2");
			}
		}
			// Swap numbers[i] and numbers[indexSmallest]
			temp = value[i];
			value[i] = value[indexSmallest];
			value[indexSmallest] = temp;
		

	}//print out how amny elements user wants
	for (int l = 0; l < userInputSize; l++) {
		if(size > l)
		printf("%s: %lld\n", value[l].X, value[l].Y );
	}
}

//function to store suggestions
void storeSuggestions(BSTNode *Node, int k, char *inputline, int counter) {
	if (counter == 0) {
		return;
	}
	//allocate memory for struct
	BSTValue *value = ((BSTValue*)malloc(counter * sizeof(BSTValue)));
	int count = 0;
	
	StoreNumberOfMatches(Node, inputline, &count, value);  //Helper function
	
	sort(value, counter, k);  //funtion to sort the data
}

//
// BSTHeight: returns the height of the tree.
//
int _max2(int x, int y)
{
	return (x > y) ? x : y;
}

//helper function that returns the height number for tree
int _BSTHeight(BSTNode *root)
{
	if (root == NULL)
		return -1;
	else
		return 1 + _max2(_BSTHeight(root->Left), _BSTHeight(root->Right));
}

//functiont that calls helper function for height
int BSTHeight(BST *tree)
{
	return _BSTHeight(tree->Root);
}

