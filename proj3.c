/*main.cpp*/

//
// Auto-complete using a binary search tree.
//
// <<Jakub >>
// U. of Illinois, Chicago
// CS251, Spring 2017
// Project 03
//

// ignore stdlib warnings if working in Visual Studio:
#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "bst.h"





//
// skipRestOfInput:
//
// Inputs and discards the remainder of the current line for the 
// given input stream, including the EOL character(s).
//
void skipRestOfInput(FILE *stream)
{
	char restOfLine[256];
	int rolLength = sizeof(restOfLine) / sizeof(restOfLine[0]);

	fgets(restOfLine, rolLength, stream);
}

//
// getFileName: inputs a filename from the keyboard, make sure the file can be
// opened, and returns the filename if so.  If the file cannot be opened, an
// error message is output and the program is exited.
//
char *getFileName()
{
	char filename[512];
	int  fnsize = sizeof(filename) / sizeof(filename[0]);

	// input filename from the keyboard:
	fgets(filename, fnsize, stdin);
	filename[strcspn(filename, "\r\n")] = '\0';  // strip EOL char(s):

												 // make sure filename exists and can be opened:
	FILE *infile = fopen(filename, "r");
	if (infile == NULL)
	{
		printf("**Error: unable to open '%s'\n\n", filename);
		exit(-1);
	}

	fclose(infile);

	// duplicate and return filename:
	char *s = (char *)malloc((strlen(filename) + 1) * sizeof(char));
	strcpy(s, filename);

	return s;
}

int main()
{
	char *filename1;
	char  cmd[64];
	char  text[512];
	//int   textsize = sizeof(text) / sizeof(text[0]);

	printf("** Starting Autocomplete **\n");

	//Reading in file 
	filename1 = getFileName();
	BST *tree; //Creating pointer
	tree = BuildTree(filename1); // calling funtion to create tree

	//
	// now interact with user:
	//
	printf("** Ready **\n");

	scanf("%s", cmd);

	

	while (strcmp(cmd, "exit") != 0)
	{
		if (strcmp(cmd, "stats") == 0)
		{
			int nodes = BSTCount(tree);  //Store number of nodes into variable and print that variable
			printf("**Tree count:  %d\n", nodes);
			int height = BSTHeight(tree); //Store the height into variable and print that variable
			printf("**Tree Height: %d\n", height);

		}
		else if (strcmp(cmd, "add") == 0)
		{
			long long weight; //Creating long long weight
			char      part2[512];
			int       part2size = sizeof(part2) / sizeof(part2[0]);
			int returnValueInsert;
			BSTValue tempvalue; //Creating temporary struct to store info into
			BSTKey key1 = (BSTKey*)malloc(sizeof(char)* strlen(text)+1);  //Allcoating memory for key
			tempvalue.X = (char*)malloc(sizeof(char) * strlen(text) + 1);  //Allocating memory for char
			//
			// add weight text
			//
			scanf("%lld %s", &weight, text);
			fgets(part2, part2size, stdin);
			part2[strcspn(part2, "\r\n")] = '\0';  // strip EOL char(s):
			strcat(text, part2);

			tempvalue.Y = weight;  //Storing weight into struct
			strcpy (tempvalue.X, text);  //String copying text into struct

			strcpy(key1, text);  //stringcopying text into key
			returnValueInsert = BSTInsert(tree, key1, tempvalue); //Storing return value into variable 
			if (returnValueInsert == 0) {//Return a 0 if not-added
				printf("**Not added...\n");
			}
			else {
				printf("**Added\n"); //if non 0 value, means it has been added
				
			}
		}
		else if (strcmp(cmd, "find") == 0)
		{
			char part2[512];
			int  part2size = sizeof(part2) / sizeof(part2[0]);
			
			//
			// find text
			//
			scanf("%s", text);
			fgets(part2, part2size, stdin);
			part2[strcspn(part2, "\r\n")] = '\0';  // strip EOL char(s):
			strcat(text, part2);

			BSTNode *returnFrom = BSTSearch(tree, text); //creating pointer to BST search function

			if (returnFrom == NULL) { //If NULL then not found
				printf("**Not found...\n");
			}
			else {
				printf("%s: %lld\n", returnFrom->Key, returnFrom->Value.Y);  //Otherwise print out what we are looking for
			}
			//
			// TODO
			//
		}
		else if (strcmp(cmd, "suggest") == 0)
		{
			int  k;
			char part2[512];
			int  part2size = sizeof(part2) / sizeof(part2[0]);
			int count = 0;
			//
			// suggest k text
			//
			scanf("%d %s", &k, text);
			fgets(part2, part2size, stdin);
			part2[strcspn(part2, "\r\n")] = '\0';  // strip EOL char(s):
			strcat(text, part2);

			//printf("Text: %s\n", text);
			BSTNode *pointer; //Creating pointer of BSTNode
			pointer = BSTSearch2(tree, text);  //Setting pointer equal to return of function(smaller tree now)
			
			if (pointer == NULL) { //If it is NULL that means no suggestions exist
					printf("**No suggestions...\n");
			}
			else { //Otherwise print out information
				printf("** [Sub-tree root:  (%s,%lld)]\n", pointer->Key, pointer->Value.Y); //Print out key and value
				int nodes = BSTSubTreeCount(pointer);
				printf("** [Sub-tree count: %d]\n", nodes);  //Print out the sub-tree count

				NumberOfMatches(pointer, text, &count);
				printf("** [Num matches:    %d]\n", count);//Print out the number of matches
			}
			storeSuggestions(pointer, k, text, count); //call this function which does the suggestion
			//
			// TODO
			//
		}
		else
		{
			printf("**unknown cmd, try again...\n");
		}

		scanf("%s", cmd);
	}

	printf("** Done **\n"); //Finished

	return 0; //end of main
}