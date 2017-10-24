#include "Printer.h"
#include <string>
#include <iostream>

using namespace std;

void Printer::pushInt(int tempInt) {
	str += to_string(tempInt);
}

void Printer::pushChar(char tempChar) {
	str += tempChar;
}

void Printer::returnAll() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < str.size(); j++) {
			cout << asciiSymbol(str[j], i) << " ";
		}
		cout << endl;
	}
	str.clear();
}

string Printer::asciiSymbol(char c, int layer) {
	string asciiDigits[5][10] = {
		{ "XXXX", "  X ", "XXXX", "XXXX", "X  X", "XXXX", "XXXX", "XXXX", "XXXX", "XXXX" },
		{ "X  X", "  X ", "   X", "   X", "X  X", "X   ", "X   ", "   X", "X  X", "X  X" },
		{ "X  X", "  X ", "XXXX", "XXXX", "XXXX", "XXXX", "XXXX", "  X ", "XXXX", "XXXX" },
		{ "X  X", "  X ", "X   ", "   X", "   X", "   X", "X  X", " X  ", "X  X", "   X" },
		{ "XXXX", "  X ", "XXXX", "XXXX", "   X", "XXXX", "XXXX", "X   ", "XXXX", "XXXX" },
	};
	string plus[5] = {
		"     ",
		"  X  ",
		"XXXXX",
		"  X  ",
		"     "
	};
	string minus[5] = {
		"     ",
		"     ",
		"XXXXX",
		"     ",
		"     "
	};
	string mul[5] = {
		"     ",
		" X X ",
		"  X  ",
		" X X ",
		"     "
	};
	string div[5] = {
		"    X",
		"   X ",
		"  X  ",
		" X   ",
		"X    "
	};
	string openBracket[5] = {
		" X   ",
		"X    ",
		"X    ",
		"X    ",
		" X   "
	};
	string closeBracket[5] = {
		"   X ",
		"    X",
		"    X",
		"    X",
		"   X ",
	};
	string equals[5] = {
		"     ",
		"XXXXX",
		"     ",
		"XXXXX",
		"     "
	};
	if (isdigit(c)) {
		return asciiDigits[layer][c - '0'];
	}
	switch (c) {
	case '+': {
		return plus[layer];
		break;
	}
	case '-': {
		return minus[layer];
		break;
	}
	case '*': {
		return mul[layer];
		break;
	}
	case '/': {
		return div[layer];
		break;
	}
	case '(': {
		return openBracket[layer];
		break;
	}
	case ')': {
		return closeBracket[layer];
		break;
	}
	case '=': {
		return equals[layer];
		break;
	}
	}
}
