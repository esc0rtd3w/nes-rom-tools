#ifndef _REG_EX_H_
#define _REG_EX_H_

//#define REGEX_DEBUG

class RegEx
{
	public:
		RegEx();
		RegEx(const char*);
		~RegEx();
		void Load(const char*);
		int Matches(const char*) const; //-1 if no match, else num matching chars
	private:
		bool SetContains(const char*, char) const;
		int WhereInSet(const char*, char) const;
		char ParseChar(const char*, int&) const;
		bool plainstring; //false==set
		bool repeat; //false==once, true==any number
		char* value; //string or set
		int valuelen;
		RegEx *next;
};

#endif
