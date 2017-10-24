#include <string>
#ifndef PRINTER_H
#define PRINTER_H

using namespace std;

class Printer {
public:
	void pushInt(int tempInt);
	void pushChar(char tempChar);
	void returnAll();

private:
	string str = "";
	string asciiSymbol(char c, int layer);
};

#endif