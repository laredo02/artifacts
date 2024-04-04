

	int num_lines = 0, num_chars = 0;

	int getId () {
		static int id = 0;
		++id;
		return id;
	}

%%

id		printf("%d", getId()); num_chars+=2;
\n		num_lines++; num_chars++;
.		num_chars++;

%%

int yywrap() {}
int main () {
	yylex();
	printf("#lines: %d\n#chars: %d\n", num_lines, num_chars);
}
