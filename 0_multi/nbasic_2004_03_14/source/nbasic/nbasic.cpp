#include "nbasic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIXTEENBIT 65536

//---------------------------------------

Token::Token(int num_, int type_, int line_, const char* val, int location_)
{
	index = num_;
	type = type_;
	line = line_;
	location = location_;
	next = prev = NULL;
	int len = strlen(val);
	if (len == 0)
	{
		value = NULL;
		return;
	}
	value = new char[len+1];
	memset(value,0,len+1);
	strcpy(value, val);
	valuelen = len;
	/*
	if (type == INCBIN)
	{
		printf("incbin\n");
		fflush(stdout);
	}
	*/
}

Token::~Token()
{
	if (value != NULL)
		delete value;
	if (next != NULL)
		delete next;
}


//---------------------------------------

TokenList::TokenList()
{
	num_tokens = 0;
	first = marker = last = NULL;
}

TokenList::~TokenList()
{
	last = NULL;
	marker = NULL;
	if (first != NULL) delete first; //blows away whole list safely
}

bool TokenList::Match(int start, int type)
{
	const Token *t = GetToken(start);
	return (t != NULL && t->type == type);
}

bool TokenList::Match(int start, int type0, int type1)
{
	return Match(start, type0) && Match(start+1, type1);
}

bool TokenList::Match(int start, int type0, int type1, int type2)
{
	return Match(start, type0, type1) && Match(start+2, type2);
}

bool TokenList::Match(int start, int type0, int type1, int type2, int type3)
{
	return Match(start, type0, type1, type2) && Match(start+3, type3);
}

void TokenList::AddToken(int type, const char *val, int len, int linenum, int loc)
{
	char str[len+1];
	memset(str,0,len+1);
	strncpy(str,val,len);
	Token *t = new Token(num_tokens, type, linenum, str, loc);
	num_tokens++;
	if(first == NULL)
	{
		first = t;
		last = t;
	}
	else
	{
		last->next = t;
		t->prev = last;
		last = last->next;
	}
}

void TokenList::RemoveToken(int n)
{
	//set marker to the target token, and get handles on surrounding tokens
	if (first == NULL || n < 0 || n >= num_tokens) return;
	if (marker == NULL) marker = first;
	while(marker->index < n) marker = marker->next;
	while(marker->index > n) marker = marker->prev;
	Token* tnext = marker->next;
	Token* tprev = marker->prev;
	
	//delete the token
	if (first == marker) first = tnext; //so we don't lose the whole stream
	marker->next = NULL;
	marker->prev = NULL;
	delete marker;
	num_tokens--;

	//re-point marker and hook up others
	if (tprev != NULL) marker = tprev;
		else marker = tnext;
	if (tprev !=NULL) tprev->next = tnext;
	if (tnext !=NULL) tnext->prev = tprev;
	
	//decrement downstream index nums
	Token* temp = tnext;
	while (temp != NULL)
	{
		temp->index--;
		temp = temp->next;
	}
}

const Token* TokenList::GetToken(int n)
{
	if (first == NULL || n < 0 || n >= num_tokens) return NULL;
	if (marker == NULL) marker = first;
	while(marker->index < n) marker = marker->next;
	while(marker->index > n) marker = marker->prev;
	return marker;
}

Token* TokenList::GetTokenPointer(int n)
{
	if (GetToken(n) == NULL) return NULL;
	return marker;
}

void TokenList::SetTokenLocation(int i, int loc)
{
	if (GetToken(i) != NULL)
		marker->location = loc;
}

bool TokenList::HasToken(const char *value)
{
	const Token *t = first;
	while(t!=NULL)
	{
		if (!strcmp(t->value, value)) return true;
		t = t->next;
	}
	return false;
}

int TokenList::NumTokens() const
{
	return num_tokens;
	/*
	int n = 0;
	const Token *t = first;
	while(t!=NULL)
	{
		n++;
		t = t->next;
	}
	return n;
	*/
}

//---------------------------------------

NBasic::NBasic()
{
	verbose = true;
	numfiles = 0;
	numlines = 0;
	num_regexes = 0;
	next_autolabel = 1;
}

NBasic::~NBasic()
{
	//empty
}

void NBasic::SetVerbosity(bool b)
{
	verbose = b;
}

void NBasic::SetMaxFiles(int n)
{
	filelines = new int[n];
	filenames = new const char*[n];
}

int NBasic::TokenType(int i)
{
	if (i<tokens.NumTokens())
		return tokens.GetToken(i)->type;
	return PAST_END_FILE;
}

const char* NBasic::TokenValue(int i)
{
	return tokens.GetToken(i)->value;
}

void NBasic::AddRegEx(const char *exp, int result, bool require_whitespace)
{
	if (num_regexes == MAX_REGEXES)
	{
		printf("ERROR: Max number of regular expressions. Change #define MAX_REGEXES\n");
		exit(0);
	}
	regex_returns[num_regexes] = result;
	regexes[num_regexes].Load(exp);
	regex_requirewhite[num_regexes] = require_whitespace;
	num_regexes++;
}

bool IsStartAsm(const char *s)
{
	int i=0;
	while(s[i]==' ' || s[i]=='\t') i++;
	if (strncmp(&s[i],"asm",3)!=0) return false;
	i+=3;
	while(s[i]==' ' || s[i]=='\t' || s[i]=='\r' || s[i]=='\n') i++;
	if (s[i]==0) return true;
	return false;
}

bool IsEndAsm(const char *s)
{
	int i=0;
	while(s[i]==' ' || s[i]=='\t') i++;
	if (strncmp(&s[i],"endasm",6)!=0) return false;
	i+=6;
	while(s[i]==' ' || s[i]=='\t' || s[i]=='\r' || s[i]=='\n') i++;
	if (s[i]==0) return true;
	return false;
}

bool IsAsmLine(const char *s, int &start)
{
	int i=0;
	while(s[i]==' ' || s[i]=='\t') i++;
	if (strncmp(&s[i],"asmline",7)!=0) return false;
	start = i+7;
	return true;
}

bool NBasic::TokenizeLine(const char *line, int linenum)
{
	static bool in_asm_block = false;

	int len = strlen(line);
	if (len == 0) return true; //sure, we can tokenize a blank line!

	//special case, single ASM line
	int asmstart = 0;
	if (IsAsmLine(line,asmstart))
	{
		tokens.AddToken(ASM, NULL, 0, linenum);
		tokens.AddToken(ASMTEXT, &line[asmstart], len-asmstart, linenum);
		tokens.AddToken(ENDASM, NULL, 0, linenum);
		return true;
	}
	
	//special case, entering ASM block
	if (IsStartAsm(line))
	{
		tokens.AddToken(ASM, NULL, 0, linenum);
		in_asm_block = true;
		return true;
	}

	//special case, within ASM block
	if (in_asm_block)
	{
		if (IsEndAsm(line))
		{
			tokens.AddToken(ENDASM, NULL, 0, linenum);
			in_asm_block = false;
			return true;
		}
		tokens.AddToken(ASMTEXT, line, len, linenum);
		return true;
	}

	//general case, parse normally
	for(int i = 0; i < num_regexes; i++) //try matching against each regex
	{
		int match = regexes[i].Matches(line);
		if (match > -1)
		{
			//token match! check whitespace requirements
			if ((!regex_requirewhite[i]) ||
				(regex_requirewhite[i] &&
					(
					match == len ||
					regexes[whitespace_regex].Matches(&line[match])>-1 ||
					regexes[newline_regex].Matches(&line[match])>-1
					)
				))
			{
				//we're good. add the token, check the rest of the line
				tokens.AddToken(regex_returns[i], line, match, linenum);
				return TokenizeLine(&line[match], linenum);
			}
		}
	}
	return false;
}

void NBasic::TrimWhitespace()
{
	//remove WHITESPACE, NEWLINE, and COMMENT tokens that aren't in an asm block
	int i = 0;
	bool asmblock = false;
	while(i < tokens.NumTokens())
	{
		int type = TokenType(i);
		if (asmblock)
		{
			if (type == ENDASM)
				asmblock = false;
			i++;
		}
		else
		{
			if (type == WHITESPACE || type == NEWLINE || type == COMMENT)
				tokens.RemoveToken(i);
			else i++;
			if (type == ASM)
				asmblock = true;
		}
	}
}

void NBasic::CompactMath()
{
	bool done = false;
	while(!done)
	{
		done = true; //set false when no longer true
		for(int i = 0; i < tokens.NumTokens();)
		{
			if (IsMath(i) && tokens.Match(i+1,NUMBER,NUMBER))
			{
				int type = TokenType(i);
				if (type==PLUS || type==MINUS || type==SHIFTLEFT || type==SHIFTRIGHT ||
					type == BITAND || type == BITOR || type == BITEOR)
				{
					done = false;
					Token *t = tokens.GetTokenPointer(i);
					int one = NumberValue(TokenValue(i+1), t->line);
					int two = NumberValue(TokenValue(i+2), t->line);
					t->type = NUMBER;
					if (t->value != NULL) delete t->value;
					t->value = new char[8];
					int result = (type==PLUS ? one+two : (type==MINUS ? one-two :
						(type==SHIFTLEFT ? one<<two : (type==SHIFTRIGHT ? one>>two :
						(type==BITAND?/*BITAND*/one&two:(type==BITOR?one | two:(one ^ 
						two)))))));
					sprintf(t->value,"%i\0", (result+SIXTEENBIT)%SIXTEENBIT);
					tokens.RemoveToken(i+1);
					tokens.RemoveToken(i+1);
					i++;
				}
				else i+=3;
			}
			else
			{
				i++;
			}
		}
	}
}


#define FBUFSIZE 1024
void NBasic::AddFile(const char *filename)
{
	FILE *f = fopen(filename,"r");
	if (!f)
	{
		fprintf(stderr,"Could not open file %s for reading. Aborting.\n",filename);
		exit(0);
	}
	char buf[FBUFSIZE];
	int line = 0;
	while(fgets(buf,FBUFSIZE,f) != NULL)
	{
		line++;
		TokenizeLine(buf,line+numlines);
	}
	fclose(f);
	filenames[numfiles] = filename;
	filelines[numfiles++] = line;
	numlines += line;
	if (verbose) printf("Read file %s (%i lines)\n",filename,line); fflush(stdout);
}

char* NBasic::MakeNumber(const char* n, int line)
{
	int number = NumberValue(n, line);
	char *s = new char[8]; //more than big enough
	sprintf(s,"%i\0",number);
	return s;
}

int NBasic::NumberValue(const char* n, int line)
{
	int number = 0;
	if (n[0] == '$')
	{
		for(int i = 1; i < strlen(n); i++)
			number = number*16 +
				(n[i]>='0'&&n[i]<='9' ? n[i]-'0' :
				(n[i]>='a'&&n[i]<='f' ? n[i]-'a'+10 :
				n[i]-'A'+10));
	}
	else if (n[0]=='%')
	{
		for(int i = 1; i < strlen(n); i++)
			number = number*2+(n[i]=='0' ? 0 : 1);
	}
	else if (n[0]>='0' && n[0]<='9')
	{
		for(int i = 0; i < strlen(n); i++)
			number = number*10+(n[i]-'0');
	}
	else CompileError("number",line);
	number = number % SIXTEENBIT; //we'll never need anything bigger than that (CPU limitation)
	return number;
}

void NBasic::CompileError(const char *s, int line)
{
	int whichline = line;
	int whichfile = 0;
	while (whichline > filelines[whichfile])
	{
		whichline -= filelines[whichfile];
		whichfile++;
	}
	fprintf(stderr,"\nERROR on line %i of file '%s' compiling %s statement.\n",
		whichline,filenames[whichfile],s);
	exit(0);
}

void NBasic::Compile()
{
	TrimWhitespace();
	CompactMath();
	AddVariable("nbasic_stack", 0x100, 2, 0x100);
	int numtokens = tokens.NumTokens();
	int i = 0;
	while (i < numtokens)
	{
		i += Compile(i);
	}
}

int NBasic::Compile(int i)
{
	const Token* t = tokens.GetToken(i);
	int type = t->type;
	int line = t->line;
	//printf("line %i: %s\n", line, t->value);fflush(stdout);
	switch(type)
	{
		case ENDPROG: //deprecated
			if (verbose) printf("Encountered program end at line %i\n",line);
			return tokens.NumTokens(); //past end of input. stop compile
		case ASM:
			return CompileAsm(i, type, line);
		case LABEL:
		case ENDASM:
		case ARRAY:
			return CompileIdentifiers(i, type, line);
		case PUSH:
		case POP:
			return CompilePush(i, type, line);
		case GOTO:
		case GOSUB:
		case RETURN:
		case RESUME:
			return CompileJump(i, type, line);
		case COMMENT:
		case WHITESPACE:
			return 1;
		case DATA:
			return CompileData(i, type, line);
		case SET:
			return CompileSet(i, type, line);
		case INC:
		case DEC:
			return CompileIncrement(i, type, line);
		case IF:
			return CompileConditional(i, type, line);
		default:
			break;
	}
	CompileError("",tokens.GetToken(i)->line);
	return -1;
}

void NBasic::CreateAutoVariables()
{
	int n = asmlist.NumTokens();
	for(int i = 0; i < n; i++)
	{
		const Token *t = asmlist.GetToken(i);
		if (t->type==STAp && (t->value[0]<'0' || t->value[0]>'9'))
			AddVariable(t->value);
	}
}

void NBasic::VarError(const char* name)
{
	fprintf(stderr, "Redefinition of variable %s. Aborting.\n", name);
	exit(0);
}

void NBasic::VarAllocError(const char* name)
{
	fprintf(stderr, "Error allocating memory for variable %s. Aborting.\n", name);
	exit(0);
}

void NBasic::OutputVariables(FILE *f)
{
	TokenList tempvars;
	int numtokens = variables.NumTokens();

	//add absolute location vars
	for(int i=0; i<numtokens; i++)
	{
		const Token *t = variables.GetToken(i);
		if (t->type == 2)
		{
			if(tempvars.HasToken(t->value)) VarError(t->value);
			tempvars.AddToken(t->type, t->value, t->valuelen, t->line, t->location);
		}
	}

	//add zeropage vars
	for(int i=0; i<numtokens; i++)
	{
		const Token *t = variables.GetToken(i);
		if (t->type == 1)
		{
			if(tempvars.HasToken(t->value)) VarError(t->value);
			tempvars.AddToken(t->type, t->value, t->valuelen, t->line, t->location);
		}
	}

	//add auto-allocated pre-sized vars
	for(int i=0; i<numtokens; i++)
	{
		const Token *t = variables.GetToken(i);
		if (t->type == 0 && t->line != -1)
		{
			if(tempvars.HasToken(t->value)) VarError(t->value);
			tempvars.AddToken(t->type, t->value, t->valuelen, t->line, t->location);
		}
	}

	//add auto-allocated default vars
	for(int i=0; i<numtokens; i++)
	{
		const Token *t = variables.GetToken(i);
		if (t->type == 0 && t->line == -1)
			if(!tempvars.HasToken(t->value))
				tempvars.AddToken(t->type, t->value, t->valuelen, 1, t->location);
	}

	//now try to allocate memory for each variable
	int numvars = tempvars.NumTokens();
	bool memory[SIXTEENBIT]; //true means filled
	for(int i=0; i<SIXTEENBIT; i++) memory[i] = (i < 2048 ? false : true);
	for(int i=0; i<numvars; i++)
	{
		const Token *t = tempvars.GetToken(i);
		int start = t->location;
		int len = t->line;
		if(t->type == 2 && len != 0) //absolute
		{
			for(int j = start; j < start+len; j++)
			{
				if(memory[j]) VarAllocError(t->value);
				memory[j] = true;
			}
		}
		else if (t->type == 1 && len != 0) //zeropage
		{
			start = 0;
			bool found = false;
			while(start < 0x100-len && !found)
			{
				if(!memory[start])
				{
					found = true;
					for(int j = 0; j < len; j++)
						if(memory[start+j]) found = false;
				}
				if (!found) start++;
			}
			if (!found) VarAllocError(t->value);
			for(int j = 0; j < len; j++) memory[start+j] = true;
			tempvars.SetTokenLocation(i, start);
		}
		else if(len != 0) //auto allocate
		{
			start = 0;
			bool found = false;
			while(start < 0xffff-len && !found)
			{
				if(!memory[start])
				{
					found = true;
					for(int j = 0; j < len; j++)
						if(memory[start+j]) found = false;
				}
				if (!found) start++;
			}
			if (!found) VarAllocError(t->value);
			for(int j = 0; j < len; j++) memory[start+j] = true;
			tempvars.SetTokenLocation(i, start);		
		}
	}
	
	//actually output them now
	for(int i=0; i<numvars; i++)
	{
		const Token *t = tempvars.GetToken(i);
		fprintf(f, "%s = %i\n", t->value, t->location);	
	}
}

bool NBasic::VariableExists(const char* name)
{
	for(int i = 0; i < variables.NumTokens(); i++)
		if (!strcmp(name, variables.GetToken(i)->value))
			return true;
	return false;
}

void NBasic::AddVariable(const char* name, int length, int vartype, int loc)
{
	if(vartype==2 && strcmp(name,"nbasic_stack")) //warn user if it conflicts with the stack
	{
		for(int i=loc; i < loc+length; i++)
			if (i>=256 && i<= 511)
			{
				fprintf(stderr,"Declaration of variable '%s' conflicts with NES stack ($100-$1FF)\n",name);
				fprintf(stderr,"Compile Aborted\n");fflush(stdout);
				exit(0);
			}
	}
	variables.AddToken(vartype, name, strlen(name), length, loc);
}

int NBasic::CompileIdentifiers(int i, int type, int line)
{
	const Token* t;
	switch(type)
	{
		case LABEL:
			t = tokens.GetToken(i);
			asmlist.AddToken(ASMLABEL, t->value, t->valuelen, line);
			return 1;
		case ARRAY:
			if(tokens.Match(i,ARRAY,VAR,NUMBER))
			{
				AddVariable(TokenValue(i+1),
					NumberValue(TokenValue(i+2),line));
				return 3;
			}
			else if(tokens.Match(i,ARRAY,ZEROPAGE,VAR,NUMBER))
			{
				AddVariable(TokenValue(i+2),
					NumberValue(TokenValue(i+3),line), 1);
				return 4;
			}
			else if(tokens.Match(i+1,/*ARRAY,*/ABSOLUTE,NUMBER,VAR,NUMBER))
			{
				AddVariable(TokenValue(i+3),
					NumberValue(TokenValue(i+4),line),2,
					NumberValue(TokenValue(i+2),line));
				return 5;
			}
			CompileError("array declaration",line); //invalid array declaration syntax			
		case ENDASM:
			CompileError("endasm",line); //should never see it here
	}
}

int NBasic::CompileAsm(int i, int type, int line)
{
	bool done = false;
	int added = 1;
	while (!done)
	{
		const Token* t = tokens.GetToken(i + added++);
		if (t!=NULL && t->type!=ENDASM)
			asmlist.AddToken(ASMTEXT, t->value, t->valuelen, t->line);
		else
			done = true;
	}
	return added;
}

int NBasic::CompileJump(int i, int type, int line)
{
	const Token* t;
	switch(type)
	{
		case RESUME:
			asmlist.AddToken(RTI, "", 0, line);
			return 1;
		case RETURN:
			asmlist.AddToken(RTS, "", 0, line);
			return 1;
		case GOTO:
		case GOSUB:
			if (tokens.Match(i+1, VAR))
			{
				t = tokens.GetToken(i+1);
				asmlist.AddToken((type==GOTO ? JMP : JSR),
					t->value, t->valuelen, line);
				return 2;
			}
			break;
	}
	CompileError(type==GOTO ? "goto" : "gosub", line);
}

bool IsHex(char c)
{
	if ('0'<=c && c<='9') return true;
	if ('a'<=c && c<='f') return true;
	if ('A'<=c && c<='F') return true;
	return false;
}

int HexValue(char c)
{
	if ('0'<=c && c<='9') return c-'0';
	if ('a'<=c && c<='f') return c-'a'+10;
	if ('A'<=c && c<='F') return c-'A'+10;
	return 0;
}

int NBasic::CompileData(int toknum, int type, int line)
{
	const Token *t = tokens.GetToken(toknum);
	if (t==NULL || t->value==NULL) CompileError("data", line);
	const char *s = t->value;
	int i = 4, len = strlen(s), numints=0;
	if (len > 80) CompileError("data (line too long)", line);
	int ints[len];
	while (s[i]==' ' || s[i]=='\t') i++; //skip initial whitespace

	//value line includes data keyword until (including) \n
	bool in_string = false;
	bool between_values = false;
	while (s[i]!='\n' && s[i]!=0)
	{
		if (between_values)
		{
			while (s[i]==' ' || s[i]=='\t') i++; //whitespace
			if (s[i++]!=',') CompileError("data",line);
			while (s[i]==' ' || s[i]=='\t') i++; //whitespace
			between_values = false;
		}
		else if (!in_string)
		{
			if (s[i]=='\"')
			{
				in_string = true;
				i++;
			}
			else if (s[i]=='$') //hexadecimal
			{
				int temp=0;
				i++;
				if (!IsHex(s[i])) CompileError("data (hexadecimal)", line);
				while (IsHex(s[i]))
					temp = temp*16+HexValue(s[i++]);
				ints[numints++] = temp;
				between_values = true;					
			}
			else if (s[i]=='%') //binary
			{
				int temp=0;
				i++;
				if (s[i]!='0' && s[i]!='1') CompileError("data (binary)", line);
				while (s[i]=='0' || s[i]=='1')
					temp = temp*2 + (s[i]-'0');
				ints[numints++] = temp;
				between_values = true;
			}
			else if ('0'<=s[i] && s[i]<='9') //decimal
			{
				int temp = 0;
				while ('0'<=s[i] && s[i]<='9')
					temp = temp*10 + s[i++]-'0';
				if (temp>255) CompileError("data (value too large)", line);
				ints[numints++] = temp;
				between_values = true;
			}
			else between_values = true;
		}
		else
		{
			if (s[i]=='\"') //quote
			{
				in_string = false;
				between_values = true;
				i++;
			}
			else if (s[i]=='\\') //backslash
			{
				ints[numints++] = s[i+1];
				i+=2;
			}
			else ints[numints++] = s[i++];
		}
	}

	//now create the ASM output
	int startint = 0;
	while (startint < numints)
	{
		int endint = startint+10;
		if (endint > numints) endint = numints;
		char outbuf[64];
		sprintf(outbuf, " .db ");
		for (int i = startint; i < endint; i++)
		{
			if (i!=startint) sprintf(&outbuf[strlen(outbuf)], ",%i", ints[i]);
			else sprintf(&outbuf[strlen(outbuf)], "%i", ints[i]);
		}
		sprintf(&outbuf[strlen(outbuf)], "\n");
		startint += 10;
		asmlist.AddToken(ASMTEXT, outbuf, strlen(outbuf), line);
	}
	return 1;
}

bool NBasic::IsConditional(int token_index)
{
	switch(TokenType(token_index))
	{
		case ISEQUAL:
		case NOTEQUAL:
		case ISLESS:
		case ISGREATER:
		case LESSEQ:
		case GREATEREQ:
			return true;
		default:
			break;
	}
	return false;
}

int NBasic::ConditionalOpposite(int cond)
{
	switch(cond)
	{
		case ISEQUAL:
			return ISEQUAL;
		case NOTEQUAL:
			return NOTEQUAL;
		case ISLESS:
			return ISGREATER;
		case ISGREATER:
			return ISLESS;
		case LESSEQ:
			return GREATEREQ;
		case GREATEREQ:
			return LESSEQ;
	}
	return -1;
}

int NBasic::CompileConditional(int i, int type, int line)
{
	int j = -1; //indicates start of second half of the conditional
	int cond = -1; //which conditional
	
	// A cond VAR
	// A cond NUM
	// X cond math
	// Y cond math
	if(
		(tokens.Match(i+1,X) || tokens.Match(i+1,Y) || tokens.Match(i+1,A)) &&
		IsConditional(i+2) &&
		IsMath(i+3))
	{
		int reg = TokenType(i+1); //which register
		cond = TokenType(i+2); //which conditional
		int type = TokenType(i+3); //which math type
		int len = 1;
		if (type == VAR)
		{
			asmlist.AddToken(reg==A?CMPp:(reg==X?CPXp:CPYp), TokenValue(i+3), strlen(TokenValue(i+3)), line);
		}
		else if (type == NUMBER)
		{
			char *num = MakeNumber(TokenValue(i+3), line);
			asmlist.AddToken(reg==A?CMPi:(reg==X?CPXi:CPYi), num, strlen(num), line);
			delete num;
		}
		else //other math
		{
			//if(reg==A) CompileError("conditional",line);
			len = CompileMath(i+3, type, line);
			asmlist.AddToken(STAp,"nbasic_temp",strlen("nbasic_temp"),line);
			asmlist.AddToken( reg==X ? CPXp : CPYp, "nbasic_temp", strlen("nbasic_temp"), line);
		}
		j = len + 3;
	}
	
	// VAR cond math (compile math, opposite cond)
	// NUM cond math (compile math, opposite cond)
	else if((tokens.Match(i+1,VAR) || tokens.Match(i+1,NUMBER)) && IsConditional(i+2) && IsMath(i+3))
	{
		cond = ConditionalOpposite(TokenType(i+2));
		j = CompileMath(i+3, TokenType(i+3), line) + 3;
		if (TokenType(i+1) == VAR)
			asmlist.AddToken(CMPp, TokenValue(i+1), strlen(TokenValue(i+1)), line);
		else
		{
			char *num = MakeNumber(TokenValue(i+1), line);
			asmlist.AddToken(CMPi, num, strlen(num), line);
			delete num;
		}
	}

	// math cond VAR (same cond)
	// math cond NUM (same cond)
	// math cond math
	else if (IsConditional(i+1+MathLength(i+1,line)) && IsMath(i+2+MathLength(i+1,line)))
	{
		int len = CompileMath(i+1, TokenType(i+1), line);
		cond = TokenType(i+1+len);
		if (TokenType(i+2+len) == VAR)
		{
			asmlist.AddToken(CMPp, TokenValue(i+2+len), strlen(TokenValue(i+2+len)), line);
			j = len + 3;
		}
		else if (TokenType(i+2+len) == NUMBER)
		{
			char *num = MakeNumber(TokenValue(i+2+len), line);
			asmlist.AddToken(CMPi, num, strlen(num), line);
			delete num;
			j = len + 3;
		}
		else
		{
			asmlist.AddToken(STAp, "nbasic_temp", strlen("nbasic_temp"), line);
			int two = CompileMath(i+2+len, TokenType(i+2+len), line);
			cond = ConditionalOpposite(cond);
			j = len + 2 + two;
		}
	}

	if (j==-1) CompileError("conditional", line);
	if (tokens.Match(i+j, BRANCHTO, VAR))
	{
		const char* label = TokenValue(i+j+1);
		int len = strlen(label);
		switch(cond) // branch on same case
		{
			case ISEQUAL:	asmlist.AddToken(BEQ, label, len, line); break;
			case NOTEQUAL:	asmlist.AddToken(BNE, label, len, line); break;
			case ISLESS:	asmlist.AddToken(BMI, label, len, line); break;
			case ISGREATER:	asmlist.AddToken(BCS, label, len, line); break;
			case LESSEQ:	asmlist.AddToken(BCC, label, len, line); break;
			case GREATEREQ:	asmlist.AddToken(BPL, label, len, line); break;
			default: CompileError("conditional branchto",line); break;
		}
		j+=2;
	}
	else
	{
		int my_autolabel = next_autolabel++;
		char autolabel[24];
		sprintf(autolabel,"nbasic_autolabel_%i\0",my_autolabel);
		int len = strlen(autolabel);
		switch(cond) // branch to autolabel on opposite case
		{
			case ISEQUAL:
				asmlist.AddToken(BNE, autolabel, len, line);
				break;
			case NOTEQUAL:
				asmlist.AddToken(BEQ, autolabel, len, line);
				break;
			case ISLESS:
				asmlist.AddToken(BCS, autolabel, len, line);
				break;
			case ISGREATER:
				asmlist.AddToken(BCC, autolabel, len, line);
				asmlist.AddToken(BEQ, autolabel, len, line);
				break;
			case LESSEQ:
				asmlist.AddToken(BCS, autolabel, len, line);
				asmlist.AddToken(BEQ, autolabel, len, line);
				break;
			case GREATEREQ:
				asmlist.AddToken(BCC, autolabel, len, line);
				break;
			default: CompileError("conditional branch",line); break;
		}
		// compile conditional code (check for THEN)
		if (TokenType(i+j)==THEN)
		{
			j++;
			int typeij = TokenType(i+j);
			while(typeij!=ENDIF && typeij!=PAST_END_FILE)
			{
				j += Compile(i+j);
				typeij = TokenType(i+j);
			}
			if (typeij == PAST_END_FILE)
				CompileError("if..then without corresponding endif",line);
			j++;
		}
		else
		{
			j += Compile(i+j);
		}
		// create autolabel
		sprintf(autolabel,"nbasic_autolabel_%i:\0",my_autolabel);
		asmlist.AddToken(ASMLABEL, autolabel, strlen(autolabel), line);
	}
	return j;
}

int NBasic::CompileSet(int i, int type, int line)
{
	//=============set basic memory location
	if (tokens.Match(i+1,VAR,A))
	{
		asmlist.AddToken(STAp, TokenValue(i+1), strlen(TokenValue(i+1)), line);
		return 3;
	}
	else if (tokens.Match(i+1,NUMBER,A))
	{
		char *num = MakeNumber(TokenValue(i+1), line);
		asmlist.AddToken(STAp, num, strlen(num), line);
		delete num;
		return 3;
	}
	if (tokens.Match(i+1,VAR,X))
	{
		asmlist.AddToken(TXA,"",0,line);
		asmlist.AddToken(STAp, TokenValue(i+1), strlen(TokenValue(i+1)), line);
		return 3;
	}
	else if (tokens.Match(i+1,NUMBER,X))
	{
		char *num = MakeNumber(TokenValue(i+1), line);
		asmlist.AddToken(TXA,"",0,line);
		asmlist.AddToken(STAp, num, strlen(num), line);
		delete num;
		return 3;
	}
	else if (tokens.Match(i,SET,VAR) && IsMath(i+2))
	{
		const Token *t = tokens.GetToken(i+2);
		int len = CompileMath(i+2, t->type, t->line);
		t = tokens.GetToken(i+1);
		asmlist.AddToken(STAp, t->value, t->valuelen, line);
		return len+2;
	}
	else if (tokens.Match(i,SET,NUMBER) && IsMath(i+2))
	{
		const Token *t = tokens.GetToken(i+2);
		int len = CompileMath(i+2, t->type, t->line);
		char *num = MakeNumber(TokenValue(i+1),line);
		asmlist.AddToken(STAp, num, strlen(num), line);
		delete num;
		return len+2;	
	}
	//================ set the accumulator register
	else if (tokens.Match(i,SET,A,X))
	{
		asmlist.AddToken(TXA, "", 0, line);
		return 3;
	}
	else if (tokens.Match(i,SET,A,Y))
	{
		asmlist.AddToken(TYA, "", 0, line);
		return 3;
	}
	else if (tokens.Match(i,SET,A) && IsMath(i+2))
	{
		const Token *t = tokens.GetToken(i+2);
		return 2 + CompileMath(i+2, t->type, t->line);
	}
	//================= set the X register
	else if (tokens.Match(i,SET,X,A))
	{
		asmlist.AddToken(TAX, "", 0, line);
		return 3;
	}
	else if (tokens.Match(i,SET,X,VAR))
	{
		const Token *t = tokens.GetToken(i+2);
		asmlist.AddToken(LDXp, t->value, t->valuelen, t->line);
		return 3;
	}
	else if (tokens.Match(i,SET,X,NUMBER))
	{
		char *num = MakeNumber(TokenValue(i+2),line);
		asmlist.AddToken(LDXi, num, strlen(num), line);
		delete num;
		return 3;
	}
	else if (tokens.Match(i,SET,X) && IsMath(i+2))
	{
		int len = CompileMath(i+2, TokenType(i+2), line);
		asmlist.AddToken(TAX, "", 0, line);
		return len + 2;
	}
	//=================== set the Y register
	else if (tokens.Match(i,SET,Y,A))
	{
		asmlist.AddToken(TAY, "", 0, line);
		return 3;
	}
	else if (tokens.Match(i,SET,Y,VAR))
	{
		const Token *t = tokens.GetToken(i+2);
		asmlist.AddToken(LDYp, t->value, t->valuelen, t->line);
		return 3;
	}
	else if (tokens.Match(i,SET,Y,NUMBER))
	{
		char *num = MakeNumber(TokenValue(i+2),line);
		asmlist.AddToken(LDYi, num, strlen(num), line);
		delete num;
		return 3;
	}
	else if (tokens.Match(i,SET,Y) && IsMath(i+2))
	{
		int len = CompileMath(i+2, TokenType(i+2), line);
		asmlist.AddToken(TAY, "", 0, line);
		return len + 2;
	}
	//=============set simple var array location
	else if (tokens.Match(i+1,BRACKETOPEN,VAR,X,BRACKETCLOSE) && IsMath(i+5))
	{
		int len = CompileMath(i+5, TokenType(i+5), line);
		asmlist.AddToken(STApx, TokenValue(i+2), strlen(TokenValue(i+2)), line);
		return len+5;
	}
	else if (tokens.Match(i+1,BRACKETOPEN,VAR,Y,BRACKETCLOSE) && IsMath(i+5))
	{
		int len = CompileMath(i+5, TokenType(i+5), line);
		asmlist.AddToken(STApy, TokenValue(i+2), strlen(TokenValue(i+2)), line);
		return len+5;
	}
	else if (tokens.Match(i+1,BRACKETOPEN,VAR,VAR,BRACKETCLOSE) && IsMath(i+5))
	{
		int len = CompileMath(i+5, TokenType(i+5), line);
		asmlist.AddToken(LDXp, TokenValue(i+3), strlen(TokenValue(i+3)), line);
		asmlist.AddToken(STApx, TokenValue(i+2), strlen(TokenValue(i+2)), line);
		return len+5;
	}
	else if (tokens.Match(i+1,BRACKETOPEN,VAR,NUMBER,BRACKETCLOSE) && IsMath(i+5))
	{
		int len = CompileMath(i+5, TokenType(i+5), line);
		asmlist.AddToken(LDXi, TokenValue(i+3), strlen(TokenValue(i+3)), line);
		asmlist.AddToken(STApx, TokenValue(i+2), strlen(TokenValue(i+2)), line);
		return len+5;
	}
	//=============set simple number array location
	else if (tokens.Match(i+1,BRACKETOPEN,NUMBER,X,BRACKETCLOSE) && IsMath(i+5))
	{
		int len = CompileMath(i+5, TokenType(i+5), line);
		char *num = MakeNumber(TokenValue(i+2),line);
		asmlist.AddToken(STApx, num, strlen(num), line);
		delete num;
		return len+5;
	}
	else if (tokens.Match(i+1,BRACKETOPEN,NUMBER,Y,BRACKETCLOSE) && IsMath(i+5))
	{
		int len = CompileMath(i+5, TokenType(i+5), line);
		char *num = MakeNumber(TokenValue(i+2),line);
		asmlist.AddToken(STApy, num, strlen(num), line);
		delete num;
		return len+5;
	}
	else if (tokens.Match(i+1,BRACKETOPEN,NUMBER,VAR,BRACKETCLOSE) && IsMath(i+5))
	{
		int len = CompileMath(i+5, TokenType(i+5), line);
		char *num = MakeNumber(TokenValue(i+2),line);
		asmlist.AddToken(LDXp, TokenValue(i+3), strlen(TokenValue(i+3)), line);
		asmlist.AddToken(STApx, num, strlen(num), line);
		delete num;
		return len+5;
	}
	else if (tokens.Match(i+1,BRACKETOPEN,NUMBER,NUMBER,BRACKETCLOSE) && IsMath(i+5))
	{
		int len = CompileMath(i+5, TokenType(i+5), line);
		char *num = MakeNumber(TokenValue(i+2),line);
		asmlist.AddToken(LDXi, TokenValue(i+3), strlen(TokenValue(i+3)), line);
		asmlist.AddToken(STApx, num, strlen(num), line);
		delete num;
		return len+5;
	}
	//=============set complex number array location
	// SET BRACKETOPEN VAR [math] BRACKETCLOSE [math]
	else if (tokens.Match(i+1,BRACKETOPEN,VAR) && tokens.Match(i+3+MathLength(i+3,line),BRACKETCLOSE))
	{
		int len1 = CompileMath(i+3, TokenType(i+3), line);
		asmlist.AddToken(PHA, "", 0, line);
		int len2 = CompileMath(i+4+len1, TokenType(i+4+len1), line);
		asmlist.AddToken(STAp, "nbasic_temp", strlen("nbasic_temp"), line);
		asmlist.AddToken(PLA, "", 0, line);
		asmlist.AddToken(TAX, "", 0, line);
		asmlist.AddToken(LDAp, "nbasic_temp", strlen("nbasic_temp"), line);
		asmlist.AddToken(STApx, TokenValue(i+2), strlen(TokenValue(i+2)), line);
		return 4 + len1 + len2;
	}
	// SET BRACKETOPEN NUMBER [math] BRACKETCLOSE [math]
	else if (tokens.Match(i+1,BRACKETOPEN,NUMBER) && tokens.Match(i+3+MathLength(i+3,line),BRACKETCLOSE))
	{
		int len1 = CompileMath(i+3, TokenType(i+3), line);
		asmlist.AddToken(PHA, "", 0, line);
		int len2 = CompileMath(i+4+len1, TokenType(i+4+len1), line);
		asmlist.AddToken(STAp, "nbasic_temp", strlen("nbasic_temp"), line);
		asmlist.AddToken(PLA, "", 0, line);
		asmlist.AddToken(TAX, "", 0, line);
		asmlist.AddToken(LDAp, "nbasic_temp", strlen("nbasic_temp"), line);
		char *num = MakeNumber(TokenValue(i+2),line);
		asmlist.AddToken(STApx, num, strlen(num), line);
		delete num;
		return 4 + len1 + len2;
	}
	else
		CompileError("'set'", line);
	return 0;
}

int NBasic::CompilePush(int i, int type, int line)
{
	if (tokens.Match(i,PUSH,A))
	{
		asmlist.AddToken(PHA, "", 0, line);
		return 2;
	}
	else if (tokens.Match(i,POP,A))
	{
		asmlist.AddToken(PLA, "", 0, line);
		return 2;
	}
	else if (tokens.Match(i,PUSH,X))
	{
		asmlist.AddToken(TXA, "", 0, line);
		asmlist.AddToken(PHA, "", 0, line);
		return 2;
	}
	else if (tokens.Match(i,POP,X))
	{
		asmlist.AddToken(PLA, "", 0, line);
		asmlist.AddToken(TAX, "", 0, line);
		return 2;
	}
	else if (tokens.Match(i,PUSH,Y))
	{
		asmlist.AddToken(TYA, "", 0, line);
		asmlist.AddToken(PHA, "", 0, line);
		return 2;
	}
	else if (tokens.Match(i,POP,Y))
	{
		asmlist.AddToken(PLA, "", 0, line);
		asmlist.AddToken(TAY, "", 0, line);
		return 2;
	}
	CompileError("Error compiling push/pop statement", line);
	return 0;
}

int NBasic::CompileIncrement(int i, int type, int line)
{
	if (tokens.Match(i,INC,X))
	{	
		asmlist.AddToken(INX, "", 0, line);
		return 2;
	}
	else if (tokens.Match(i,DEC,X))
	{	
		asmlist.AddToken(DEX, "", 0, line);
		return 2;
	}
	else if (tokens.Match(i,INC,Y))
	{
		asmlist.AddToken(INY, "", 0, line);
		return 2;
	}
	else if (tokens.Match(i,DEC,Y))
	{
		asmlist.AddToken(DEY, "", 0, line);
		return 2;
	}
	else if (tokens.Match(i,INC,VAR))
	{
		const Token *t = tokens.GetToken(i+1);
		asmlist.AddToken(INCp, t->value, t->valuelen, t->line);
		return 2;
	}
	else if (tokens.Match(i,DEC,VAR))
	{
		const Token *t = tokens.GetToken(i+1);
		asmlist.AddToken(DECp, t->value, t->valuelen, t->line);
		return 2;
	}
	CompileError("not fully implemented feature 'inc'", line); return 0;
}

bool NBasic::IsMath(int token_index)
{
	int type = TokenType(token_index);
	switch(type)
	{
		case VAR:
		case NUMBER:
		case PLUS:
		case MINUS:
		case SHIFTLEFT:
		case SHIFTRIGHT:
		case BRACKETOPEN:
		case BITAND:
		case BITOR:
		case BITEOR:
			return true;
		default:
			return false;
	}
	return false;
}

int NBasic::MathLength(int i, int line)
{
	int one,two;
	switch(TokenType(i))
	{
		case VAR:
		case NUMBER:
			return 1;
		case PLUS:
		case MINUS:
		case BITAND:
		case BITOR:
		case BITEOR:
			one = MathLength(i+1, line);
			two = MathLength(i+1+one, line);
			return 1 + one + two;
		case SHIFTLEFT:
		case SHIFTRIGHT:
			one = MathLength(i+1, line);
			return one+2;
		case BRACKETOPEN:
			one = MathLength(i+1, line);
			if (TokenType(i+1+one) == BRACKETCLOSE)
				return one + 2;
			two = MathLength(i+1+one, line);
			if (TokenType(i+two+one+1)!=BRACKETCLOSE)
				CompileError("Error calculating bracketed math string", line);
			return 2 + one + two;
		default:
			CompileError("Error calculating math string", line);
	}
	return -1; //should never get here
}

int NBasic::CompileMath(int i, int type, int line)
{
 	switch(type)
	{
		case VAR:
		{
			const Token *t = tokens.GetToken(i);
			asmlist.AddToken(LDAp, t->value, t->valuelen, t->line);
			return 1;
		}
		case NUMBER:
		{
			char *num = MakeNumber(TokenValue(i), line);
			asmlist.AddToken(LDAi, num, strlen(num), line);
			delete num;
			return 1;
		}
		case BRACKETOPEN:
		{
			if (tokens.Match(i+1,VAR,X,BRACKETCLOSE)) // [var x]
			{
				const Token *t = tokens.GetToken(i+1);
				asmlist.AddToken(LDApx, t->value, t->valuelen, t->line);
				return 4;
			}
			if (tokens.Match(i+1,VAR,VAR,BRACKETCLOSE)) // [var var]
			{
				const Token *t = tokens.GetToken(i+1);
				const Token *t2 = tokens.GetToken(i+2);
				asmlist.AddToken(LDXp, t2->value, t2->valuelen, t2->line);
				asmlist.AddToken(LDApx, t->value, t->valuelen, t->line);
				return 4;
			}
			if (tokens.Match(i+1,VAR,NUMBER,BRACKETCLOSE)) // [var num]
			{
				const Token *t = tokens.GetToken(i+1);
				char *num = MakeNumber(TokenValue(i+2),line);
				asmlist.AddToken(LDXi, num, strlen(num), line);
				asmlist.AddToken(LDApx, t->value, t->valuelen, t->line);
				delete num;
				return 4;
			}
			else if(tokens.Match(i+1,VAR) && tokens.Match(i+2+MathLength(i+2,line),BRACKETCLOSE)) //[var math]
			{
				const Token *t = tokens.GetToken(i+1);
				int len = CompileMath(i+2, TokenType(i+2), line);
				asmlist.AddToken(TAX, "", 0, line);
				asmlist.AddToken(LDApx, t->value, t->valuelen, t->line);
				return len + 3;
			}
			else if (tokens.Match(i+1,NUMBER,BRACKETCLOSE)) // [num]
			{
				char *num = MakeNumber(TokenValue(i+1),line);
				asmlist.AddToken(LDAp,num,strlen(num),line);
				delete num;
				return 3;
			}
			else if (tokens.Match(i+1,NUMBER,X,BRACKETCLOSE)) // [num x]
			{
				char *num = MakeNumber(TokenValue(i+1),line);
				asmlist.AddToken(LDApx, num, strlen(num), line);
				delete num;
				return 4;
			}
			else if (tokens.Match(i+1,NUMBER,VAR,BRACKETCLOSE)) // [num var]
			{
				char *num = MakeNumber(TokenValue(i+1),line);
				const Token *t = tokens.GetToken(i+2);
				asmlist.AddToken(LDXp, t->value, t->valuelen, t->line);
				asmlist.AddToken(LDApx, num, strlen(num), line);
				delete num;
				return 4;
			}
			else if (tokens.Match(i+1,NUMBER,NUMBER,BRACKETCLOSE)) // [num num]
			{
				// [$2000 3] is the same as [$2003]
				int val = (NumberValue(TokenValue(i+1),line) + NumberValue(TokenValue(i+2),line)) % SIXTEENBIT;
				char num[8];
				sprintf(num, "%i\0",val);
				asmlist.AddToken(LDAp, num, strlen(num), line);
				return 4;
			}
			else if(tokens.Match(i+1,NUMBER) && tokens.Match(i+2+MathLength(i+2,line),BRACKETCLOSE)) //[num math]
			{
				char *num = MakeNumber(TokenValue(i+1),line);
				int len = CompileMath(i+2, TokenType(i+2), line);
				asmlist.AddToken(TAX, "", 0, line);
				asmlist.AddToken(LDApx, num, strlen(num), line);
				delete num;
				return len + 3;
			}
			CompileError("array access", line);
		}
		case PLUS:
		{
			if (tokens.Match(i+1,VAR)) // + var math
			{
				int len = CompileMath(i+2, TokenType(i+2), line);
				/*if (len == 1)*/ asmlist.AddToken(CLC, "", 0, line);
				const Token *t = tokens.GetToken(i+1);
				asmlist.AddToken(ADCp, t->value, t->valuelen, t->line);
				return len + 2;
			}
			else if (tokens.Match(i+1,NUMBER)) // + num math
			{
				int len = CompileMath(i+2, TokenType(i+2), line);
				/*if (len == 1)*/ asmlist.AddToken(CLC, "", 0, line);
				char *num = MakeNumber(TokenValue(i+1), line);
				asmlist.AddToken(ADCi, num, strlen(num), line);
				delete num;
				return len + 2;
			}
			else if (tokens.Match(i+1+MathLength(i+1,line), VAR)) // + math var
			{
				int len = CompileMath(i+1, TokenType(i+1), line);
				/*if (len == 1)*/ asmlist.AddToken(CLC, "", 0, line);
				const Token *t = tokens.GetToken(i+1+len);
				asmlist.AddToken(ADCp, t->value, t->valuelen, t->line);
				return len + 2;
			}
			else if (tokens.Match(i+1+MathLength(i+1,line), NUMBER)) // + math num
			{
				int len = CompileMath(i+1, TokenType(i+1), line);
				/*if (len == 1)*/ asmlist.AddToken(CLC, "", 0, line);
				char *num = MakeNumber(TokenValue(i+1+len), line);
				asmlist.AddToken(ADCi, num, strlen(num), line);
				delete num;
				return len + 2;
			}
			else if (IsMath(i+1+MathLength(i+1,line)))// + math math
			{
				int len1 = CompileMath(i+1,TokenType(i+1),line);
				asmlist.AddToken(PHA,"",0,line);
				int len2 = CompileMath(i+1+len1,TokenType(i+1+len1),line);
				asmlist.AddToken(STAp, "nbasic_temp", strlen("nbasic_temp"), line);
				asmlist.AddToken(PLA,"",0,line);
				asmlist.AddToken(CLC,"",0,line);
				asmlist.AddToken(ADCp, "nbasic_temp", strlen("nbasic_temp"), line);
				return len1 + len2 + 1;
			}
			CompileError("addition", line);
		}
		case MINUS:
		{
			if (tokens.Match(i+1+MathLength(i+1,line), NUMBER)) // - math num
			{
				int len = CompileMath(i+1,TokenType(i+1),line);
				/*if (len == 1)*/ asmlist.AddToken(SEC,"",0,line);
				char *num = MakeNumber(TokenValue(i+1+len),line);
				asmlist.AddToken(SBCi,num,strlen(num),line);
				delete num;
				return 2+len;
			}
			else if (tokens.Match(i+1+MathLength(i+1,line), VAR)) // - math var
			{
				int len = CompileMath(i+1,TokenType(i+1),line);
				/*if (len == 1)*/ asmlist.AddToken(SEC,"",0,line);
				asmlist.AddToken(SBCp, TokenValue(i+1+len), strlen(TokenValue(i+1+len)), line);
				return 2+len;
			}
			else if (IsMath(i+1+MathLength(i+1,line))) // - math math
			{
				int len1 = CompileMath(i+1,TokenType(i+1),line);
				asmlist.AddToken(PHA,"",0,line);
				int len2 = CompileMath(i+1+len1,TokenType(i+1+len1),line);
				asmlist.AddToken(STAp, "nbasic_temp", strlen("nbasic_temp"), line);
				asmlist.AddToken(PLA,"",0,line);
				asmlist.AddToken(SEC,"",0,line);
				asmlist.AddToken(SBCp, "nbasic_temp", strlen("nbasic_temp"), line);
				return len1 + len2 + 1;
			}
			CompileError("subtraction", line);
		}
		case BITAND:
		{
			if (tokens.Match(i+1, VAR) && IsMath(i+2)) // & var math
			{
				int len = CompileMath(i+2, TokenType(i+2), line);
				asmlist.AddToken(ANDp, TokenValue(i+1), strlen(TokenValue(i+1)), line);
				return len + 2;
			}
			else if (tokens.Match(i+1, NUMBER) && IsMath(i+2)) // & num math
			{
				char *num = MakeNumber(TokenValue(i+1), line);
				int len = CompileMath(i+2, TokenType(i+2), line);
				asmlist.AddToken(ANDi, num, strlen(num), line);
				delete num;
				return len + 2;
			}
			else if (tokens.Match(i+1+MathLength(i+1, line), VAR)) // & math var
			{
				int len = CompileMath(i+1, TokenType(i+1), line);
				asmlist.AddToken(ANDp, TokenValue(i+1+len), strlen(TokenValue(i+1+len)), line);
				return len + 2;
			}
			else if (tokens.Match(i+1+MathLength(i+1, line), NUMBER)) // & math num
			{
				int len = CompileMath(i+1, TokenType(i+1), line);
				char *num = MakeNumber(TokenValue(i+1+len), line);
				asmlist.AddToken(ANDi, num, strlen(num), line);
				delete num;
				return len + 2;
			}
			else if (IsMath(i+1+MathLength(i+1,line)))// & math math
			{
				int len1 = CompileMath(i+1,TokenType(i+1),line);
				asmlist.AddToken(PHA,"",0,line);
				int len2 = CompileMath(i+1+len1,TokenType(i+1+len1),line);
				asmlist.AddToken(STAp, "nbasic_temp", strlen("nbasic_temp"), line);
				asmlist.AddToken(PLA,"",0,line);
				asmlist.AddToken(ANDp, "nbasic_temp", strlen("nbasic_temp"), line);
				return len1 + len2 + 1;
			}
			CompileError("bitwise-and",line);
		}
		case BITOR:
		{
			if (tokens.Match(i+1, VAR) && IsMath(i+2)) // | var math
			{
				int len = CompileMath(i+2, TokenType(i+2), line);
				asmlist.AddToken(ANDp, TokenValue(i+1), strlen(TokenValue(i+1)), line);
				return len + 2;
			}
			else if (tokens.Match(i+1, NUMBER) && IsMath(i+2)) // | num math
			{
				char *num = MakeNumber(TokenValue(i+1), line);
				int len = CompileMath(i+2, TokenType(i+2), line);
				asmlist.AddToken(ORi, num, strlen(num), line);
				delete num;
				return len + 2;
			}
			else if (tokens.Match(i+1+MathLength(i+1, line), VAR)) // | math var
			{
				int len = CompileMath(i+1, TokenType(i+1), line);
				asmlist.AddToken(ORp, TokenValue(i+1+len), strlen(TokenValue(i+1+len)), line);
				return len + 2;
			}
			else if (tokens.Match(i+1+MathLength(i+1, line), NUMBER)) // | math num
			{
				int len = CompileMath(i+1, TokenType(i+1), line);
				char *num = MakeNumber(TokenValue(i+1+len), line);
				asmlist.AddToken(ORi, num, strlen(num), line);
				delete num;
				return len + 2;
			}
			else if (IsMath(i+1+MathLength(i+1,line)))// | math math
			{
				int len1 = CompileMath(i+1,TokenType(i+1),line);
				asmlist.AddToken(PHA,"",0,line);
				int len2 = CompileMath(i+1+len1,TokenType(i+1+len1),line);
				asmlist.AddToken(STAp, "nbasic_temp", strlen("nbasic_temp"), line);
				asmlist.AddToken(PLA,"",0,line);
				asmlist.AddToken(ORp, "nbasic_temp", strlen("nbasic_temp"), line);
				return len1 + len2 + 1;
			}
			CompileError("bitwise-or",line);
		}
		case BITEOR:
		{
			if (tokens.Match(i+1, VAR) && IsMath(i+2)) // ^ var math
			{
				int len = CompileMath(i+2, TokenType(i+2), line);
				asmlist.AddToken(EORp, TokenValue(i+1), strlen(TokenValue(i+1)), line);
				return len + 2;
			}
			else if (tokens.Match(i+1, NUMBER) && IsMath(i+2)) // ^ num math
			{
				char *num = MakeNumber(TokenValue(i+1), line);
				int len = CompileMath(i+2, TokenType(i+2), line);
				asmlist.AddToken(EORi, num, strlen(num), line);
				delete num;
				return len + 2;
			}
			else if (tokens.Match(i+1+MathLength(i+1, line), VAR)) // ^ math var
			{
				int len = CompileMath(i+1, TokenType(i+1), line);
				asmlist.AddToken(EORp, TokenValue(i+1+len), strlen(TokenValue(i+1+len)), line);
				return len + 2;
			}
			else if (tokens.Match(i+1+MathLength(i+1, line), NUMBER)) // ^ math num
			{
				int len = CompileMath(i+1, TokenType(i+1), line);
				char *num = MakeNumber(TokenValue(i+1+len), line);
				asmlist.AddToken(EORi, num, strlen(num), line);
				delete num;
				return len + 2;
			}
			else if (IsMath(i+1+MathLength(i+1,line)))// ^ math math
			{
				int len1 = CompileMath(i+1,TokenType(i+1),line);
				asmlist.AddToken(PHA,"",0,line);
				int len2 = CompileMath(i+1+len1,TokenType(i+1+len1),line);
				asmlist.AddToken(STAp, "nbasic_temp", strlen("nbasic_temp"), line);
				asmlist.AddToken(PLA,"",0,line);
				asmlist.AddToken(EORp, "nbasic_temp", strlen("nbasic_temp"), line);
				return len1 + len2 + 1;
			}
			CompileError("bitwise-eor",line);
		}
		case SHIFTLEFT:
			if (tokens.Match(i+1+MathLength(i+1, line), NUMBER)) // << math num
			{
				int len = CompileMath(i+1, TokenType(i+1), line);
				int num = NumberValue(TokenValue(i+1+len), line);
				asmlist.AddToken(CLC,"",0,line);
				for(int j = 0; j < num; j++)
					asmlist.AddToken(ASLa,"",0,line);
				return len + 2;
			}
			CompileError("left shift", line);
		case SHIFTRIGHT:
			if (tokens.Match(i+1+MathLength(i+1, line), NUMBER)) // << math num
			{
				int len = CompileMath(i+1, TokenType(i+1), line);
				int num = NumberValue(TokenValue(i+1+len), line);
				asmlist.AddToken(CLC,"",0,line);
				for(int j = 0; j < num; j++)
					asmlist.AddToken(LSRa,"",0,line);
				return len + 2;
			}
			CompileError("right shift", line);
			break;
		defualt:
			CompileError("arithmetic",line);
	}
}

bool NBasic::Output(const char* filename)
{
	FILE *f = fopen(filename,"w");
	if (!f) return false;
	Output(f);
	fclose(f);
	return true;
}

void NBasic::Output(FILE *f)
{
	if (verbose) printf("Beginning compile\n");
	CreateAutoVariables();
	OutputVariables(f);
	int n = asmlist.NumTokens();
	const Token* t;
	for(int i = 0; i < n; i++)
	{
		t = asmlist.GetToken(i);
		switch(t->type)
		{
	//addition
			case ADCi:
				fprintf(f, " adc #%s\n",t->value);
				break;
			case ADCp:
				fprintf(f, " adc %s\n",t->value);
				break;
			case ADCpx:
				fprintf(f, " adc %s,x\n",t->value);
				break;
	//bitwise and
			case ANDi:
				fprintf(f, " and #%s\n", t->value);
				break;
			case ANDp:
				fprintf(f, " and %s\n", t->value);
				break;
  //bitwise or
			case ORi:
				fprintf(f, " or #%s\n", t->value);
				break;
			case ORp:
				fprintf(f, " or %s\n", t->value);
				break;
  //bitwise eor
      case EORi:
				fprintf(f, " eor #%s\n", t->value);
				break;
			case EORp:
				fprintf(f, " eor %s\n", t->value);
				break;
	//shift left
			case ASLa:
				fprintf(f, " asl a\n");
				break;
	//labels
			case ASMACCEPTABLE:
			case ASMTEXT:
				fprintf(f, "%s",t->value);
				break;
			case ASMLABEL:
				fprintf(f, "\n%s\n",t->value);
				break;
	//branches
			case BCC:
				fprintf(f, " bcc %s\n",t->value);
				break;
			case BCS:
				fprintf(f, " bcs %s\n",t->value);
				break;
			case BEQ:
				fprintf(f, " beq %s\n",t->value);
				break;
			case BMI:
				fprintf(f, " bmi %s\n",t->value);
				break;
			case BNE:
				fprintf(f, " bne %s\n",t->value);
				break;
			case BPL:
				fprintf(f, " bpl %s\n",t->value);
				break;
	//clear carry
			case CLC:
				fprintf(f, " clc\n");
				break;
	//comparisons
			case CMPi:
				fprintf(f, " cmp #%s\n",t->value);
				break;
			case CMPp:
				fprintf(f, " cmp %s\n",t->value);
				break;
			case CPXi:
				fprintf(f, " cpx #%s\n",t->value);
				break;
			case CPXp:
				fprintf(f, " cpx %s\n",t->value);
				break;
			case CPYi:
				fprintf(f, " cpy #%s\n",t->value);
				break;
			case CPYp:
				fprintf(f, " cpy %s\n",t->value);
				break;
	//decrements
			case DECp:
				fprintf(f, " dec %s\n",t->value);
				break;
			case DECpx:
				fprintf(f, " dec %s,x\n",t->value);
				break;
			case DEX:
				fprintf(f, " dex\n");
				break;
			case DEY:
				fprintf(f, " dey\n");
				break;
	//increments
			case INCp:
				fprintf(f, " inc %s\n",t->value);
				break;
			case INCpx:
				fprintf(f, " inc %s,x\n",t->value);
				break;
			case INX:
				fprintf(f, " inx\n");
				break;
			case INY:
				fprintf(f, " iny\n");
				break;
	//jumps
			case JMP:
				fprintf(f, " jmp %s\n",t->value);
				break;
			case JSR:
				fprintf(f, " jsr %s\n",t->value);
				break;
	//loads
			case LDAi:
				fprintf(f, " lda #%s\n",t->value);
				break;
			case LDAp:
				fprintf(f, " lda %s\n",t->value);
				break;
			case LDApx:
				fprintf(f, " lda %s,x\n",t->value);
				break;
			case LDApy:
				fprintf(f, " lda %s,y\n",t->value);
				break;
			case LDXi:
				fprintf(f, " ldx #%s\n",t->value);
				break;
			case LDXp:
				fprintf(f, " ldx %s\n",t->value);
				break;
			case LDXpy:
				fprintf(f, " ldx %s,y\n",t->value);
				break;
			case LDYi:
				fprintf(f, " ldy #%s\n",t->value);
				break;
			case LDYp:
				fprintf(f, " ldy %s\n",t->value);
				break;
			case LDYpx:
				fprintf(f, " ldy %s,x\n",t->value);
				break;
	//shift right
			case LSRa:
				fprintf(f, " lsr a\n");
				break;
	//stack ops
			case PHA:
				fprintf(f, " pha\n");
				break;
			case PLA:
				fprintf(f, " pla\n");
				break;
	//subtraction
			case SBCi:
				fprintf(f, " sbc #%s\n",t->value);
				break;
			case SBCp:
				fprintf(f, " sbc %s\n",t->value);
				break;
			case SBCpx:
				fprintf(f, " sbc %s,x\n",t->value);
				break;
			case SEC:
				fprintf(f, " sec\n");
				break;
	//stores
			case STAp:
				fprintf(f, " sta %s\n",t->value);
				break;
			case STApx:
				fprintf(f, " sta %s,x\n",t->value);
				break;
			case STApy:
				fprintf(f, " sta %s,y\n",t->value);
				break;

			case STXp:
				fprintf(f, " stx %s\n",t->value);
				break;
			case STXpy:
				fprintf(f, " stx %s,y\n",t->value);
				break;
			case STYp:
				fprintf(f, " sty %s\n",t->value);
				break;
			case STYpx:
				fprintf(f, " sty %s,x\n",t->value);
				break;

			case RTI:
				fprintf(f, " rti\n");
				break;
			case RTS:
				fprintf(f, " rts\n");
				break;
	//transfers
			case TAX:
				fprintf(f, " tax\n");
				break;
			case TAY:
				fprintf(f, " tay\n");
				break;
			case TXA:
				fprintf(f, " txa\n");
				break;
			case TYA:
				fprintf(f, " tya\n");
				break;
	//unhandled
			default:
				fprintf(stderr, "don't know how to handle ASM opcode type %i\n",t->type);
		}
	}
	fprintf(f,"\n");
	if (verbose) printf("Compile completed successfully.\n");
}
