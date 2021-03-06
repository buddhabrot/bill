#include "lexer.hpp"

// We shouldn't do this, but there's so many things we shouldn't do.
using namespace std;

static void init() {
	buildSymbolMap(); // defined in lexer_def.hpp
	buildTokenMap(); // defined in lexer_def.hpp
}

static std::list<Token*> tokens;

static Token* last_token = new Token(TOKEN_NONE);
static Token token_eof(TOKEN_EOF);

static int position;
static int line;

static int eat_char() {
    position += 1;
    return getchar();
}

static TokenType get_next_token() {
    static int last_char = ' ';
    TokenType found_token = TOKEN_NONE;

    while(isspace(last_char))
        last_char = eat_char();

	// eof?
	if(last_char == EOF) {
		last_token->type = TOKEN_EOF;
		found_token = last_token->type;
		return found_token;
	}
	
    last_token = new Token(TOKEN_UNKNOWN);

	// first character is alpha
    if(isalpha(last_char)) {
        last_token->type = TOKEN_IDENTIFIER;
        last_token->data += last_char; 
        // fetch next characters
        while(isalnum(last_char = eat_char()))
            last_token->data += last_char;
	
		// could also be a keyword
		if(KwMap.find(last_token->data) != KwMap.end()) {
			last_token->type = KwMap[last_token->data];
		}

        found_token = last_token->type;
        return found_token;
    }

	// first character is a digit
    if(isdigit(last_char) || last_char == '.') {
        double value;

        delete last_token;
        last_token = new NumericToken;
        do {
            last_token->data += last_char;
            last_char = eat_char();
        } while(isdigit(last_char) || last_char == '.');

        value = strtod(last_token->data.c_str(), NULL);
        ((NumericToken*) last_token)->value = value;

        found_token = last_token->type;
        return found_token;
    }

	// first character is "
	if(last_char == '"' || last_char == '\'') {
		int expected_terminal = last_char;
		last_token->type = TOKEN_STRING;

		while((last_char = eat_char()) != expected_terminal) {
			if(last_char == EOF) {
				delete last_token;
				// TODO (norepeat): put actual error strings elsewhere
				last_token = new ErrorToken("A string definition was never ended");

				found_token = last_token->type;
				return found_token;
			}
			last_token->data += last_char;
		} 
		// eat the terminal
		last_char = eat_char();
		found_token = last_token->type;
		return found_token;
	}

	// other symbols? read all non-alnum characters and then try the symbol map
	while(!isalnum(last_char) && !isspace(last_char) && last_char != EOF) {
		last_token->data += last_char;
		last_char = eat_char();
	}
	if(SmMap.find(last_token->data) != SmMap.end()) {
		SymbolType found_symbol = SmMap[last_token->data];
		delete last_token;
		last_token = new SymbolToken(found_symbol);	
		found_token = last_token -> type;
		return found_token;
	}

	// we don't know this character as the start of a token
	found_token = last_token->type;

    return found_token;
}

static int get_tokens() {
    // start with the last token (usually TOKEN_NONE or TOKEN_STITCH)

    do {
        tokens.push_back(last_token);
		get_next_token();
    }
    while(last_token && last_token->type != TOKEN_EOF);
    
    return last_token->type == TOKEN_EOF; 
}

int main(void) {
	init();

    get_tokens();
    
    std::list<Token*>::iterator i;
    for(i = tokens.begin(); i != tokens.end(); ++i)
        cout << **i << "" << endl;

    cout << "Final position:" << position << ";" << line << endl;

    cleanup:
	/* The lexer does not care for cleaning up */
    return 0;
}




