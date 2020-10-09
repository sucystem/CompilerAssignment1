#include "Parser.hpp"

const char* tokenName[] = {
	"label", "integer", ";", ",", "%id", "eof"
};


void Parser::plabel()
{
	if (nextSymbol.number == tlabel)
	{
		prog.body.push_back(Statement(nextSymbol));
		getNextSymbol();
	}
	else parseError(1);
}

void Parser::pinteger()
{
	if (nextSymbol.number == tinteger)
	{
		prog.body.push_back(Statement(nextSymbol));
		getNextSymbol();
	}
	else parseError(2);
}

void Parser::psemicolon()
{
	if (nextSymbol.number == tsemicolon)
		getNextSymbol();
	else parseError(3);
}

void Parser::pcomma()
{
	if (nextSymbol.number == tcomma)
		getNextSymbol();
	else parseError(4);
}

void Parser::pid()
{
	if (nextSymbol.number == tid)
	{
		prog.body.back().id.push_back(nextSymbol);
		getNextSymbol();
	}
	else parseError(5);
}

void Parser::pD()
{
	if (nextSymbol.number == tlabel)
	{
		plabel();
		pL();
	}
	else if (nextSymbol.number == tinteger)
	{
		pinteger();
		pL();
	}
	else parseError(6);
}

void Parser::pL()
{
	if (nextSymbol.number == tid)
	{
		pid();
		pR();
	}
	else parseError(7);
}

void Parser::pR()
{
	if (nextSymbol.number == tsemicolon)
	{
		psemicolon();
	}
	else if (nextSymbol.number == tcomma)
	{
		pcomma();
		pL();
	}
	else parseError(8);
}

void Parser::getNextSymbol()
{
	nextSymbol = scanner(sourceFile);
}

Program Parser::parse()
{
	do
	{
		pD();
	} while (nextSymbol.number != teof);
	return prog;
}

Program parser(FILE* sourceFile)
{
	Parser parser(sourceFile);
	return parser.parse();
}

void printTree(Program prog, FILE* outputFile)
{
	for (Statement e : prog.body)
	{
		fprintf(outputFile, "%s:\n", tokenName[e.name.number]);
		for (struct tokenType t : e.id)
		{
			fprintf(outputFile, "\t%s\n", t.value.id);
		}
	}
}

void parseError(int n)
{
	printf("*** Parser Error ***\n");
	printf("error code: %d\n", n);
}
