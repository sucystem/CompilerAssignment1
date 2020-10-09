
// MiniCScanner.c : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <ctime>

#include "Scanner.h"
#include "Parser.hpp"

FILE* sourceFile;						// miniC source program
FILE* outputFile;						// output file

extern char* tokenName[];

void icgError(int n);

int main(int argc, char *argv[])
{

	char fileName[30] = "", buffer[30] = "";
	struct tokenType token;
	Program root;
	int errorNo = 0;
	char *fileNamePtr = NULL, *context = NULL;

	clock_t start, end;
	double result;

	printf(" *** start of Mini C Compiler\n");
	if (argc != 2) {
		icgError(1);
		exit(1);
	}
	strncpy_s(fileName, sizeof(fileName), argv[1], sizeof(fileName)-1);
	printf("   * source file name: %30s\n", fileName);

	if (fopen_s(&sourceFile, fileName, "r") != 0) {
		icgError(2); 
		exit(1);
	}
	
	strncpy_s(buffer, sizeof(buffer), fileName, sizeof(fileName) - 1);
	fileNamePtr = strtok_s(buffer, ".", &context);
	strcat_s(buffer, sizeof(buffer), ".out");
	errorNo = fopen_s(&outputFile, buffer, "w");
	if (errorNo != 0) {

		fclose(sourceFile);

		icgError(2);
		exit(1);
	}


	// Test code for scanner
	//printf(" === start of Scanner\n");
	
	//do {
		//token = scanner(sourceFile);

		// write on console
		/*
		if (token.number == tident) {
			printf("Token %10s ( %3d, %12s )\n", tokenName[token.number], token.number, token.value.id);
		}
		else if (token.number == tnumber) {
			printf("Token %10s ( %3d, %12d )\n", tokenName[token.number], token.number, token.value.num);
		}
		else {
			printf("Token %10s ( %3d, %12s )\n", tokenName[token.number], token.number, "");
		}
		*/
		//writeToken(token, outputFile);
	//} while (token.number != teof);



	// Test code for Parser
	printf(" === start of Parser\n");
	start = clock();
	root = parser(sourceFile);
	end = clock();
	printTree(root, outputFile);
	/*
	printf(" === start of ICG\n");
	codeGen(root);
	*/
	printf(" *** end   of Mini C Compiler\n");
	result = (double)(end - start)/CLOCKS_PER_SEC;
	printf("running time: %lfs\n", result);

	fclose(sourceFile);
	fclose(outputFile);
}


void icgError(int n)
{
	printf("icg_error: %d\n", n);
	//3:printf("A Mini C Source file must be specified.!!!\n");
	//"error in DCL_SPEC"
	//"error in DCL_ITEM"
}
