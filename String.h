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
	char toFloat(float& number);
	char split(char**& buffer, int& buffer_size, unsigned char split_letter);
public:
	static char writeText(String& string);
    static char readFromFile(String& string, const char* fileName, char show_content= true);
	static char boolean(String& string);
	static char permutations(String& string, bool repeat = false);
	static char bruteForce(String& string);
public:
	char& operator[](unsigned int index);
	bool operator ==(const char* str2); 
	void operator=(const char* string);
	void operator=(String& string);
private:
	char* str;
	unsigned int size;
};