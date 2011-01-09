/* Some of the more tedious parts go here */

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
	SYMBOL_EQUAL,
	SYMBOL_NEQUAL,
	SYMBOL_PLUS,
	SYMBOL_MINUS,
	SYMBOL_ASTERISK,
	SYMBOL_FWDSLASH,
	SYMBOL_BWDSLASH,
	SYMBOL_PARENS_LEFT,
	SYMBOL_PARENS_RIGHT,
	SYMBOL_BRACE_LEFT,
	SYMBOL_BRACE_RIGHT,
	SYMBOL_BRACKET_LEFT,
	SYMBOL_BRACKET_RIGHT,
	SYMBOL_LT,
	SYMBOL_GT,
	SYMBOL_LTE,
	SYMBOL_GTE,
	SYMBOL_BETWEEN,
} SymbolType;


#define MAP_SYMBOL(str, symbol) MAP_TOKEN(str, TOKEN_SYMBOL); \
	SmMap.insert(StrSm(str, symbol));
#define MAP_TOKEN_TYPE(meaning, str) TkMap.insert(TkKw((meaning), (str)))
#define MAP_TOKEN(str, meaning) KwMap.insert(KwTk((str), (meaning)))

static std::map<TokenType, std::string> TkMap;
static std::map<std::string, TokenType> KwMap;
static std::map<std::string, SymbolType> SmMap;

typedef std::pair<std::string, TokenType> KwTk;
typedef std::pair<TokenType, std::string> TkKw;
typedef std::pair<std::string, SymbolType> StrSm;

static void buildSymbolMap() {
	MAP_TOKEN("goto", TOKEN_GOTO);
	MAP_TOKEN("rewrite", TOKEN_REWRITE);
	MAP_SYMBOL(":", SYMBOL_COLON);
	MAP_SYMBOL("(", SYMBOL_PARENS_LEFT);
	MAP_SYMBOL(")", SYMBOL_PARENS_RIGHT);
	MAP_SYMBOL("{", SYMBOL_BRACE_LEFT);
	MAP_SYMBOL("}", SYMBOL_BRACE_RIGHT);	
	MAP_SYMBOL("=", SYMBOL_EQUAL);
	MAP_SYMBOL("[", SYMBOL_BRACKET_LEFT);
	MAP_SYMBOL("]", SYMBOL_BRACKET_RIGHT);
	MAP_SYMBOL("<", SYMBOL_LT);
	MAP_SYMBOL(">", SYMBOL_GT);
	MAP_SYMBOL("<=", SYMBOL_LTE);
	MAP_SYMBOL(">=", SYMBOL_GTE);
	MAP_SYMBOL("<>", SYMBOL_BETWEEN);
	MAP_SYMBOL("!=", SYMBOL_NEQUAL);
	MAP_SYMBOL("+", SYMBOL_PLUS);
	MAP_SYMBOL("-", SYMBOL_MINUS);
}

static void buildTokenMap() {
	MAP_TOKEN_TYPE(TOKEN_GOTO, "goto");
	MAP_TOKEN_TYPE(TOKEN_UNKNOWN, "unknown");
	MAP_TOKEN_TYPE(TOKEN_IDENTIFIER, "id");
	MAP_TOKEN_TYPE(TOKEN_STRING, "str");
	MAP_TOKEN_TYPE(TOKEN_NUMBER, "num");
	MAP_TOKEN_TYPE(TOKEN_FILE, "file");
}

