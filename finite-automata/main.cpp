
#include <iostream>
#include <stdio.h>
#include <ctype.h>

#define IDENT 1
#define ERR 2

enum State {
	INITIAL, ALPHA, NON_ALPHA, ERROR
};

State delta(State state, char c) {
	State ret;
	switch (state) {
	case INITIAL:
		if (isalpha(c))
			ret = ALPHA;
		else
			ret = NON_ALPHA;
		break;
	case ALPHA:
		if (isalnum(c))
			ret = ALPHA;
		break;
	default:
		ret = ERROR;
		break;
	}
	return ret;
}

// alphabetic character followed by up to 5 alphanumeric characters
int recog_ident () {
	State state = INITIAL;
	char c = getchar();
	while (state != ERROR && c != EOF) {
		state = delta(state, c);
		c = getchar();
	}
	if (state == ALPHA || state == NON_ALPHA)
		return 1;
	else
		return 0;
}

// pascal comment
enum class PascalState {
	INITIAL, COMMENT, CLOSING_BRACE, ERROR
};

PascalState delta(PascalState state, char c) {
	PascalState ret;
	switch (state) {
	case PascalState::INITIAL:
		if (c == '{')
			ret = PascalState::COMMENT;
		else
			ret = PascalState::ERROR;
	break;
	case PascalState::COMMENT:
		if (c == '}')
			ret = PascalState::CLOSING_BRACE;
		else
			ret = PascalState::COMMENT;
	break;
	default:
		ret = PascalState::ERROR;
		break;
	}
	return ret;
}

// alphabetic character followed by up to 5 alphanumeric characters
int recog_pascal_comment () {
	PascalState state = PascalState::INITIAL;
	char c = getchar();
	while (state != PascalState::ERROR && c != EOF) {
		state = delta(state, c);
		c = getchar();
	}
	if (state == PascalState::CLOSING_BRACE)
		return 1;
	else
		return 0;
}

int main () {

	std::cout << recog_ident() << std::endl;

	// std::cout << recog_pascal_comment() << std::endl;

	return 0;
}






