

#include <iostream>
#include <string>

using namespace std;

enum Token {
  token_eof = -1,
  token_def = -2, token_extern = -3,
  token_identifier = -4, token_number = -5,
};

static std::string identifier_string;
static double number_value;

static int get_token () {
  static int last_character = ' ';

  // Skip any whitespace.
  while (isspace(last_character))
    last_character = getchar();

  // Handle comments.
  if (last_character == '#') {
    do
      last_character = getchar();
    while (last_character != EOF && last_character != '\n' && last_character != '\r');
    if (last_character == EOF)
      return get_token();
  }
  
  // Handle alphanum symbols.
  if (isalpha(last_character)) {
    identifier_string = last_character;
    while(isalnum(last_character = getchar())) {
      identifier_string += last_character;
    }

    if (identifier_string == "def")
      return token_def;
    else if (identifier_string == "extern")
      return token_extern;
    return token_identifier;
  }

  // Handle digits.
  if (isdigit(last_character || last_character == '.')) {
      std::string number_string;
      do {
	number_string += last_character;
	last_character = getchar();
      } while (isdigit(last_character) || last_character == '.');
      number_value = strtod(number_string.c_str(), 0);
      return token_number;
  }

  // Check for EOF
  if (last_character == EOF) {
    return token_eof;
  }

  int character = last_character;
  last_character = getchar();
  
  return character;
}

class ExprAbstractSyntaxTree {
public:
  virtual ~ExprAbstractSyntaxTree() {}
};

class NumberExprAbstractSyntaxTree : public ExprAbstractSyntaxTree {
  double value;
public:
  NumberExprAbstractSyntaxTree(double value) : value(value) {}
};

int main () {
  std::cout << "LLVM" << std::endl;
  int n = get_token();
  cout << n << endl;
  return 0;
}

