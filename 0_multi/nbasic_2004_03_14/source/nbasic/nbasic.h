  #ifndef _NBASIC_H_
#define _NBASIC_H_

#include <stdio.h>
#include "RegEx.h"
#define MAX_REGEXES 100

enum
{
	//recognized nbasic tokens
	NULL_START_TOKEN = 0,
	X, Y, A, ARRAY, ZEROPAGE, ABSOLUTE, //1-6
	GOTO, GOSUB, BRANCHTO, RETURN, RESUME, //7-11
	SET, BRACKETOPEN, BRACKETCLOSE, INC, DEC, //12-16
	PLUS, MINUS, SHIFTLEFT, SHIFTRIGHT, BITAND, //17-21
	BITOR, BITEOR, ISEQUAL, NOTEQUAL, ISLESS, ISGREATER, LESSEQ, GREATEREQ,
	IF, THEN, ENDIF,
	TO, NEXT, FOR,
	ASM, ENDASM, DATA, PUSH, POP,
	ENDPROG,PAST_END_FILE,
	LABEL, NUMBER, VAR, NEWLINE, COMMENT, WHITESPACE, INCBIN,

	//6502 assembly commands
	ASMTEXT,
	ASMLABEL,
	ASMACCEPTABLE,
	//math
	//ADC->   A + M + C -> A
	//ASL->   C <- |7|6|5|4|3|2|1|0| <- 0
	//LSR->   0 -> |7|6|5|4|3|2|1|0| -> C
	//SBC->   A - M - ~C -> A
	ADCi, ADCp, ADCpx, CLC,
	ASLa, ASLp, ASLpx,
	LSRa, LSRp, LSRpx,
	SBCi, SBCp, SBCpx, SEC, //SBC has more modes. check these
	
	//ADC, SBC, CLC, SEC, ASL, LSR,
	//AND, EOR, ORA, /*CLV, ROL, ROR,*/
	ANDi, ANDp, ANDpx,
	ORi,  ORp,  ORpx,
  EORi, EORp, EORpx,
	//conditionals
	BCC, BCS, BEQ, BIT, BMI, BNE, BPL, BRA, BVC, BVS,
	CMPi, CMPp, CPXi, CPXp, CPYi, CPYp,
	//dec, inc, lda, sta
	DECp, DECpx, DEX, DEY,
	INCp, INCpx, INX, INY,
	LDAi, LDAp, LDApx, LDApy, //other store modes
	LDXi, LDXp, LDXpy, LDYi, LDYp, LDYpx,
	PHA, PLA,
	STAp, STApx, STApy, //other store modes
	STXp, STXpy, STYp, STYpx,
	TAX, TAY, TXA, TYA, /*TXS, TSX,*/
	//jumps
	JMP, JSR, RTS, RTI,
	
	NULL_END_TOKEN
};


extern void Exit(const char*);

class Token
{
	friend class TokenList;
	public:
		Token(int num_, int type_, int line_, const char* val_, int location_=-1);
		~Token();
		int index, type, line, valuelen, location;
		char* value;
		Token *next, *prev;
};

class TokenList
{
	public:
		TokenList();
		~TokenList();
		int NumTokens() const;
		void AddToken(int type, const char* val, int len, int linenum, int loc=-1);
		bool Match(int start, int type);
		bool Match(int start, int type0, int type1);
		bool Match(int start, int type0, int type1, int type2);
		bool Match(int start, int type0, int type1, int type2, int type3);
		const Token* GetToken(int n);
		Token* GetTokenPointer(int n);
		bool HasToken(const char* value);
		void SetTokenLocation(int i, int loc);
		void RemoveToken(int n);
	private:
		int num_tokens;
		Token *first, *last, *marker;
};

class NBasic
{
	public:
		NBasic();
		~NBasic();
		void SetVerbosity(bool);
		void AddRegEx(const char *exp, int result, bool require_whitespace=true);
		void SetMaxFiles(int n);
		void AddFile(const char* filename);
		void SetWhitespaceRegEx(int n){whitespace_regex=n;}
		void SetNewlineRegEx(int n){newline_regex=n;}
		int NumRegExes() const {return num_regexes;}
		void Compile();
		bool Output(const char*);
		void Output(FILE*);
		bool TokenizeLine(const char*, int linenum); //returns true if successful, else false
	private:
		int numfiles;
		int *filelines;
		const char **filenames;
		int numlines;
		bool verbose;

		int Compile(int token_index);
		void CreateAutoVariables();
		void VarError(const char* name);
		void VarAllocError(const char* name);
		void AddVariable(const char* name, int length=-1, int vartype=0, int loc=-1);
		bool VariableExists(const char* name);
		void OutputVariables(FILE*);
		int next_autolabel;
		
		int TokenType(int);
		const char* TokenValue(int);
		char* MakeNumber(const char*,int line);
		int NumberValue(const char*, int line);
		int ConditionalOpposite(int cond);
		bool IsConditional(int token_index);
		bool IsMath(int token_index);
		int MathLength(int token_index, int line);
		void CompileError(const char*, int);
		void TrimWhitespace(); //remove needless whitespace (except in asm blocks)
		void CompactMath(); //compact number/number math ops
		RegEx regexes[MAX_REGEXES];
		int regex_returns[MAX_REGEXES];
		bool regex_requirewhite[MAX_REGEXES];
		int num_regexes;
		int whitespace_regex, newline_regex;
		TokenList tokens;
		TokenList asmlist;
		TokenList variables;

		//compile functions
		int CompileAsm(int,int,int);
		int CompileConditional(int,int,int);
		int CompileIdentifiers(int,int,int);
		int CompileIncrement(int,int,int);
		int CompileJump(int,int,int);
		int CompileSet(int,int,int);
		int CompileMath(int,int,int);
		int CompileData(int,int,int);
		int CompilePush(int,int,int);
};

#endif
