#include "RegEx.h"
#include <stdio.h>
#include <string.h>

extern void Exit(const char*);
//void Exit(const char*){}

RegEx::RegEx()
{
	next = NULL;
	value = NULL;
	repeat = false;
	plainstring = true;
	valuelen = 0;
}

RegEx::RegEx(const char *s)
{
	RegEx::RegEx();
	Load(s);
}

RegEx::~RegEx()
{
	if (next != NULL) delete next;
	if (value != NULL) delete value;
}

void RegEx::Load(const char* s)
{
	int stringlen = strlen(s);
	if (!SetContains(s, '('))
	{
		//it's just a string
		value = new char[stringlen + 1];
		strcpy(value, s);
		value[stringlen] = 0;
		plainstring = true;
		repeat = false;
		valuelen = stringlen;
		//printf("string %s\n", value);
		next = NULL;
		#ifdef REGEX_DEBUG
		printf("loaded string %s, length=%i\n",value,valuelen);
		#endif
		return;
	}
	int setbegin = WhereInSet(s, '(');
	if (setbegin > 0)
	{
		//first build the string
		value = new char[setbegin+1];
		strncpy(value, s, setbegin);
		value[setbegin+1] = 0;
		plainstring = true;
		repeat = false;
		valuelen = strlen(value);
		#ifdef REGEX_DEBUG
		printf("begin string %s, length=%i\n", value,valuelen);
		#endif
		//then tack on the ending regex
		next = new RegEx();
		next->Load(&s[setbegin]);
	}
	else //setbegin == 0
	{
		//build the set from here
		int setend = WhereInSet(s, ')');
		if (setend == -1)
		{
			Exit("Error building regular expression set. No set close found. Ignoring.\n");
		}
		int beginrange=-1, endrange=-1;
		int index = 1;
		char tempset[256];
		memset(tempset, 0, 256);
		while(index < setend)
		{
			#ifdef REGEX_DEBUG
			printf("starting char range search\n");
			#endif
			if (s[index] != '\'')
			{
				Exit("Error building regular expression set. Invalid range definition. Ignoring.\n");
			}
			beginrange = ParseChar(s,index); //auto-increments index past char close
			#ifdef REGEX_DEBUG
			printf("beginrange=%c\n",beginrange);
			#endif
			if (s[index] == '-')
			{
				//find the end of the range
				index++;
				endrange = ParseChar(s,index);
			}
			else if(s[index] == ',' || index==setend)
			{
				//range is one character
				#ifdef REGEX_DEBUG
				printf("found comma: index=%i,  setend=%i\n",index, setend);
				#endif
				endrange = beginrange;
				index++;
			}
			else if(index < setend)
			{
				//oops! invalid
				Exit("Error building regular expression set. Invalid range definition. Ignoring.\n");
			}
			for(int i=beginrange; i<=endrange; i++)
				if(i>0)	tempset[strlen(tempset)] = i;
			if (s[index]==',') index++;
		}
		plainstring = false;
		valuelen = strlen(tempset);
		value = new char[valuelen+1];
		memset(value, 0, valuelen+1);
		strcpy(value, tempset);
		//check if it's a repeating set
		if (setend+1 < stringlen && s[setend+1]=='*')
			repeat = true;
		else
			repeat = false;
		#ifdef REGEX_DEBUG
		printf("set %s %s\n",value,(repeat?"repeats":"does not repeat"));
		#endif
		//next regex
		if (setend+(repeat ? 2 : 1) < stringlen)
		{
			next = new RegEx();
			next->Load(&s[setend+(repeat?2:1)]);
		}
		else
		{
			next = NULL;
			return;
		}
	}
}

int RegEx::Matches(const char* s) const
{
	int stringlen = strlen(s);
	if (plainstring)
	{
		#ifdef REGEX_DEBUG
		printf("searching for plainstring match %s\n",value);
		printf("stringlen=%i, valuelen=%i\n",stringlen,valuelen);
		#endif
		if (stringlen < valuelen) return -1;
		if (valuelen == stringlen) return (strcmp(s,value) ? -1 : valuelen);
		if (strncmp(s,value,valuelen)) return -1;
		if (!next) return valuelen;
		int rest = next->Matches(&s[valuelen]);
		return (rest==-1 ? -1 : rest + valuelen);
	}
	//else we've got a set
	if (!repeat)
	{
		#ifdef REGEX_DEBUG
		printf("searching non-repeating set %s\n",value);
		#endif
		if (stringlen <= 1) return -1;
		if (!SetContains(value, s[0])) return -1;
		if (next == NULL) return 1;
		int rest = next->Matches(&s[1]);
		return (rest==-1 ? -1 : rest + 1);
	}
	//else repeat it any number of times
	#ifdef REGEX_DEBUG
	printf("searching repeating set %s\n",value);
	#endif
	int index = 0;
	while(SetContains(value, s[index])) index++;
	if (next == NULL) return index;
	int rest = next->Matches(&s[index]);
	return (rest==-1 ? -1 : rest + index);
}


bool RegEx::SetContains(const char* set, char c) const
{
	int setlen = strlen(set);
	for(int i=0; i<setlen; i++)
		if (c==set[i]) return true;
	return false;
}

int RegEx::WhereInSet(const char* set, char c) const
{
	int setlen = strlen(set);
	for(int i=0; i<setlen; i++)
		if (c==set[i]) return i;
	return -1;
}

char RegEx::ParseChar(const char* s, int &i) const
{
	if(s[i] == '\'' && s[i+2] == '\'')
	{
		char c = s[i+1];
		i+=3;
		return c;
	}
	Exit("Error parsing character in regular expression\n");
	return -1;
}

/*
int main()
{
	//char expression[] = "$('0'-'9','a'-'f','A'-'F')('0'-'9','a'-'f','A'-'F')*";
	char expression[] = "//(' '-'~','\r')*\n";
	RegEx r;
	r.Load(expression);
	printf("%i\n",r.Matches("//hello123\nabcdefghijklmnop"));
	return 0;
}
*/
