#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <set>
#include <list>
#include <map>
#include <vector>

#include "lexer_def.hpp"

struct Keyword {
	std::string str;
	TokenType type;
};


struct Token {
    TokenType type;
    int position;
    std::string data;
    Token(TokenType type): type(type) {}
    Token(TokenType type, const std::string &data): type(type), data(data) {}
    virtual void write(std::ostream &output) const {
		std::string typeAsStr;
		if(TkMap.find(type) != TkMap.end())
			typeAsStr = TkMap[type];
		else
			typeAsStr += type;

        output << "{" << typeAsStr << " " << data << "}";
    };
    virtual ~Token() {};
};

struct NumericToken : Token {
    double value;
    NumericToken():Token(TOKEN_NUMBER) {}
    NumericToken(const std::string &data, double value):
        Token(TOKEN_NUMBER, data), value(value) {}
    void write(std::ostream &output) const {
		std::string typeAsStr;
		if(TkMap.find(type) != TkMap.end())
			typeAsStr = TkMap[type];
		else
			typeAsStr += type;

        output << "{" << typeAsStr << " " << value << "}";
    }
};

struct SymbolToken : Token {
	SymbolType symbol;
    SymbolToken():Token(TOKEN_SYMBOL) {}
    SymbolToken(const SymbolType symbol):
        Token(TOKEN_SYMBOL), symbol(symbol) {}
    void write(std::ostream &output) const {
		output << "{sym" << symbol << "}";
    }
};


struct ErrorToken : Token {
	std::string error_str;
	ErrorToken():Token(TOKEN_ERROR) {}
	ErrorToken(const std::string &error_str):
			Token(TOKEN_ERROR), error_str(error_str) {}
	void write(std::ostream &output) const {
		output << "!!" << error_str << "!!";
	}
};

std::ostream &operator<<(std::ostream &output, const Token &token) {
    token.write(output);
    return output;
}



