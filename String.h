#pragma once

class String
{
public:
	String();
	String(const char* string);
	String(const String& string);
	~String();

	const char* c_str();
	unsigned int getSize();
	char toInteger(int& number);
	//char toInteger(unsigned int& number);
	char split(char**& buffer, unsigned int& buffer_size, unsigned char split_letter);
public:
	static char writeText(String& string);
    static char readFromFile(String& string, const char* fileName, char show_content= true);
public:
	char& operator[](unsigned int index);
	bool operator ==(const char* str2); 
	void operator=(const char* string);
private:
	char* str;
	unsigned int size;
};