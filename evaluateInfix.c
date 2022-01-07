// CPP program to evaluate a given
// expression where tokens are
// separated by space.
#include <stdio.h>
#include <string.h>

typedef struct intStack intStack;
typedef struct charStack charStack;

struct intStack{
    int sz, arr[100];
} intSt;

struct charStack{
    char arr[100];
    int sz;
} charSt;

void intPush(int data){
    intSt.arr[intSt.sz++] = data;
}

void charPush(char data){
    charSt.arr[charSt.sz++] = data;
}

int intTop(){
    return intSt.arr[intSt.sz-1];
}

char charTop(){
    return charSt.arr[charSt.sz-1];
}

void intPop(){
    intSt.sz--;
}

void charPop(){
    charSt.sz--;
}

int intEmpty(){
    if(intSt.sz==0) return 1;
    return 0;
}

int charEmpty(){
    if(charSt.sz==0) return 1;
    return 0;
}

int precedence(char op){
	if(op == '+'||op == '-')
	return 1;
	if(op == '*'||op == '/')
	return 2;
	return 0;
}

int applyOp(int a, int b, char op){
	switch(op){
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/': return a / b;
	}
}

int isDigit(char ch){
    if(ch >='0'&&ch<='9') return 1;
    return 0;
}

int evaluate(char* tokens){
	int i;
	for(i = 0; i < strlen(tokens); i++){
		
		// Current token is a whitespace,
		// skip it.
		if(tokens[i] == ' ')
			continue;
		
		// Current token is an opening
		// brace, push it to 'ops'
		else if(tokens[i] == '('){
		    charPush(tokens[i]);
// 			ops.push(tokens[i]);
		}
		
		// Current token is a number, push
		// it to stack for numbers.
		else if(isDigit(tokens[i])){
			int val = 0;
			
			// There may be more than one
			// digits in number.
			while(i < strlen(tokens) &&
						isDigit(tokens[i]))
			{
				val = (val*10) + (tokens[i]-'0');
				i++;
			}
			
// 			values.push(val);
            intPush(val);
			
			// right now the i points to
			// the character next to the digit,
			// since the for loop also increases
			// the i, we would skip one
			// token position; we need to
			// decrease the value of i by 1 to
			// correct the offset.
			i--;
		}
		
		// Closing brace encountered, solve
		// entire brace.
		else if(tokens[i] == ')')
		{
			while(!charEmpty() && charTop() != '(')
			{
				int val2 = intTop();
				intPop();
				
				int val1 = intTop();
				intPop();
				
				char op = charTop();
				charPop();
				
				intPush(applyOp(val1, val2, op));
			}
			
			// pop opening brace.
			if(!charEmpty())
			charPop();
		}
		
		// Current token is an operator.
		else
		{
			// While top of 'ops' has same or greater
			// precedence to current token, which
			// is an operator. Apply operator on top
			// of 'ops' to top two elements in values stack.
			while(!charEmpty() && precedence(charTop())
								>= precedence(tokens[i])){
				int val2 = intTop();
				intPop();
				
				int val1 = intTop();
				intPop();
				
				char op = charTop();
				charPop();
				
				intPush(applyOp(val1, val2, op));
			}
			
			// Push current token to 'ops'.
			charPush(tokens[i]);
		}
	}
	
	// Entire expression has been parsed at this
	// point, apply remaining ops to remaining
	// values.
	while(!charEmpty()){
		int val2 = intTop();
		intPop();
		
		int val1 = intTop();
		intPop();
		
		char op = charTop();
		charPop();
				
		intPush(applyOp(val1, val2, op));
	}
	
	// Top of 'values' contains result, return it.
	return intTop();
}

int main() {
    intSt.sz = 0;
    charSt.sz = 0;
	int a = evaluate("10 + 2 * 6");
	int b = evaluate("100 * 2 + 12");
	int c = evaluate("100 * ( 2 + 12 )");
	int d = evaluate("100 * ( 2 + 12 ) / 14");
	printf("%d %d %d %d", a, b, c ,d);
	return 0;
}

// This code is contributed by Nikhil jindal.
