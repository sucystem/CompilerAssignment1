#include "Parser.hpp"

const char* tokenName[] = {
	"label", "integer", ";", ",", "%id", "eof"
};


void Parser::pD()
{
	if (nextSymbol.number == tlabel || nextSymbol.number == tinteger)
	{
		prog.body.push_back(Statement(nextSymbol));
		getNextSymbol();
		if (nextSymbol.number == tid)
		{
			prog.body.back().id.push_back(nextSymbol);
			getNextSymbol();
			while (nextSymbol.number == tcomma)
			{
				getNextSymbol();
				if (nextSymbol.number == tid)
				{
					prog.body.back().id.push_back(nextSymbol);
					getNextSymbol();
				}
				else parseError(3);
			}
		}
		else parseError(2);
		if (nextSymbol.number == tsemicolon)
			getNextSymbol();
		else parseError(4);
	}
	else parseError(1);
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
