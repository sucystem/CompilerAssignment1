#ifndef PARSER_H
#define PARSER_H 1

#include "Scanner.h"

#include <vector>
#include <string>
#include <memory>
#include <queue>

class Statement
{
public:
	struct tokenType name;
	std::vector<struct tokenType> id;

	Statement(struct tokenType name)
		: name(name)
	{}
};

class Program
{
public:
	std::vector<Statement> body;
};

class Parser
{
private:
	Program prog;
	FILE* sourceFile;

	struct tokenType nextSymbol;

	void pD();
	void getNextSymbol();
public:
	Parser(FILE* sourceFile)
		: sourceFile(sourceFile)
	{
		getNextSymbol();
	}

	Program parse();
};

Program parser(FILE* sourceFile);
void printTree(Program prog, FILE* outputfile);
void parseError(int n);

#endif