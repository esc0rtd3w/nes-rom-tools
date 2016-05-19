#include "nbasic.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//function to alert nbasic instance of tokens
void AddRegExes(NBasic &n)
{
	n.AddRegEx("absolute",	ABSOLUTE);
	n.AddRegEx("array",		ARRAY);
	n.AddRegEx("asm",		ASM);
	n.AddRegEx("branchto",	BRANCHTO);
	n.AddRegEx("dec",		DEC);
	n.AddRegEx("endasm",	ENDASM);
	n.AddRegEx("endif",		ENDIF);
	//n.AddRegEx("end",		ENDPROG); //deprecated
	n.AddRegEx("for",		FOR);
	n.AddRegEx("goto",		GOTO);
	n.AddRegEx("gosub",		GOSUB);
	n.AddRegEx("if",		IF);
	n.AddRegEx("inc",		INC);
	n.AddRegEx("push",		PUSH);
	n.AddRegEx("pop",		POP);
	n.AddRegEx("resume",	RESUME);
	n.AddRegEx("return",	RETURN);
	n.AddRegEx("set",		SET);
	n.AddRegEx("then",		THEN);
	n.AddRegEx("to",		TO);
	n.AddRegEx("zeropage",	ZEROPAGE);
	n.AddRegEx("next",		NEXT);
	n.AddRegEx("&",			BITAND,			false);
	n.AddRegEx("|",			BITOR,			false);
	n.AddRegEx("^",			BITEOR,			false);
	n.AddRegEx("[",			BRACKETOPEN,	false);
	n.AddRegEx("]",			BRACKETCLOSE,	false);
	n.AddRegEx("<<",		SHIFTLEFT,		false);
	n.AddRegEx(">>",		SHIFTRIGHT,		false);
	n.AddRegEx("+",			PLUS,			false);
	n.AddRegEx("-",			MINUS,			false);
	n.AddRegEx("=",			ISEQUAL,		false);
	n.AddRegEx("<>",		NOTEQUAL,		false);
	n.AddRegEx("<=",		LESSEQ,			false);
	n.AddRegEx(">=",		GREATEREQ,		false);
	n.AddRegEx("<",			ISLESS,			false);
	n.AddRegEx(">",			ISGREATER,		false);
	n.SetNewlineRegEx(n.NumRegExes()); //next regex is the newline
	n.AddRegEx("\n",		NEWLINE,		false);

	//non-plainstring regular expressions
	//n.AddRegEx("('.')('i')('n')('c')('b')('i')('n')(' '-'~')*",		INCBIN,	false);
	n.AddRegEx("data (' '-'~','\r')*\n",	DATA, false);
	n.AddRegEx("('a'-'z','A'-'Z')('0'-'9','a'-'z','A'-'Z','_')*:", LABEL);
	n.AddRegEx("//(' '-'~','\r')*\n",	COMMENT, false);
	n.AddRegEx(";(' '-'~','\r')*\n",	COMMENT, false);
	n.AddRegEx("#(' '-'~','\r')*\n",	COMMENT, false);
	n.AddRegEx("('0'-'9')('0'-'9')*",	NUMBER, false); //decimal
	n.AddRegEx("%('0','1')('0','1')*",	NUMBER, false); //binary
	n.AddRegEx("$('0'-'9','a'-'f','A'-'F')('0'-'9','a'-'f','A'-'F')*",NUMBER, false); //hex

	//vars that start with the letter x, y, or a);
	n.AddRegEx("('x','y','a')('0'-'9','a'-'z','A'-'Z','_')('0'-'9','a'-'z','A'-'Z','_')*",VAR, false);
	n.AddRegEx("('x','X')", X,	false); //X register
	n.AddRegEx("('y','Y')", Y, false); //Y register
	n.AddRegEx("('a','A')", A, false); //accumulator
	//vars that start with another letter
	n.AddRegEx("('a'-'z','A'-'Z')('0'-'9','a'-'z','A'-'Z','_')*", VAR, false);
	n.SetWhitespaceRegEx(n.NumRegExes()); //next regex is whitespace
	n.AddRegEx("(' ','\r','\t',',','.','\"')(' ','\r','\t',',','.','\"')*",WHITESPACE, false);
	n.AddRegEx("'(',')','\\','/'",ASMACCEPTABLE,false);
}

void Exit(const char* errstring)
{
	fprintf(stderr,"%s\n",errstring);
	exit(0);
}


int main(int argn, char **argv)
{

	if (argn < 2)
	{
		printf("Usage: %s infile.bas [outfile.asm]\n",argv[0]);
		exit(0);
	}

	NBasic nbasic;
	AddRegExes(nbasic);
	nbasic.SetMaxFiles(argn);
	int outfilename = -1;

	//determine verbosity
	for(int i=1; i< argn; i++)
	{
		if (!strcmp(argv[i],"-verbose"))
			nbasic.SetVerbosity(true);
		else if (!strcmp(argv[i],"-quiet"))
			nbasic.SetVerbosity(false);
	}

	for(int i=1;i < argn;)
	{
		if (!strcmp(argv[i],"-o"))
		{
			outfilename = i+1;
			i+=2;
		}
		else if (!strcmp(argv[i],"-stdout"))
		{
			outfilename = 0;
			i++;
		}
		else if (!strcmp(argv[i],"-verbose") || (!strcmp(argv[i],"-quiet")))
		{
			i++; //ignore these commands here
		}
		else
		{
			nbasic.AddFile(argv[i]);
			i++;
		}	
	}
	nbasic.Compile();
	if(outfilename == 0)
		nbasic.Output(stdout);
	else if (outfilename > 0)
		nbasic.Output(argv[outfilename]);
	else
		nbasic.Output("nbasic_output.asm");
	return 0;
}

