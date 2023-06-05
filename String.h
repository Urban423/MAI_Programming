#pragma once

class String
{
public:
	String();
	String(const char* string);
	String(const int* string);
	String(const String& string);
	~String();

	const char* c_str();
	int*& getText();
	unsigned int& getSize();
	char toInteger(int& number);
	char toFloat(float& number);
	char split(String*& buffer, int& buffer_size, unsigned char split_letter);
	char replaceSymbol(String& buffer, char SymbolToReplace, char replacement);
	char removeSymbol(int SymbolToRemove);
	char add(unsigned int index, int Symbol);
	char remove(unsigned int index);
public:
	static char IntegerToString(String& buffer, int number, int showError = 0);
public:
	int& operator[](unsigned int index);
	bool operator ==(const char* str2);
	void operator=(const char* string);
	void operator=(const wchar_t* string);
	void operator=(String& string);
private:
	int* str;
	unsigned int size;
};

char printUTF8(String& str);
char writeText(String& string);
char readFromFile(String& string, const char* fileName);