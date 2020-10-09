#ifndef SCANNER_H
#define SCANNER_H 1

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>

#define NO_KEYWORD 2
#define ID_LENGTH 12

	struct tokenType {
		int number;
		union {
			char id[ID_LENGTH];
			int num;
		} value;
	};

	enum tsymbol {
		tnull = -1,
		tlabel, tinteger, tsemicolon, tcomma, tid, teof
	};

	int superLetter(char ch);
	int superLetterOrDigit(char ch);
	void lexicalError(int n);
	struct tokenType scanner(FILE* sourceFile);
	void writeToken(struct tokenType token, FILE* outputFile);
#ifdef __cplusplus
};
#endif
#endif