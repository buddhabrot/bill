#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <set>
#include <list>
#include <map>
#include <vector>


typedef enum {
    TOKEN_NONE,
    TOKEN_STITCH,
	TOKEN_IDENTIFIER,
    TOKEN_STRING,
    TOKEN_FILE,
    TOKEN_NUMBER,
	TOKEN_GOTO,
	TOKEN_REWRITE,
	TOKEN_COLON,
	TOKEN_SYMBOL,
	TOKEN_UNKNOWN,
	TOKEN_ERROR,
	TOKEN_EOF
} TokenType;

typedef enum {
	SYMBOL_COLON,
	SYMBOL_PARENS_LEFT,
	SYMBOL_PARENS_RIGHT,
	SYMBOL_BRACE_LEFT,
	SYMBOL_BRACE_RIGHT,
	SYMBOL_BRACKET_LEFT,
	SYMBOL_BRACKET_RIGHT,
	SYMBOL_ANGLE_BRACKET_LEFT,
	SYMBOL_ANGLE_BRACKET_RIGHT,
} SymbolType;

struct Keyword {
	std::string str;
	TokenType type;
};

static std::map<TokenType, std::string> TkMap;
static std::map<std::string, TokenType> KwMap;
static std::map<std::string, SymbolType> SmMap;

typedef std::pair<std::string, TokenType> KwTk;
typedef std::pair<TokenType, std::string> TkKw;
typedef std::pair<std::string, SymbolType> StrSm;

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



