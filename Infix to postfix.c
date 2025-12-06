#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define MAX_SIZE 100

// Operator Stack (for Infix to Postfix conversion)
char opStack[MAX_SIZE];
int opTop=-1;

// Number Stack (for Postfix evaluation)
int numStack[MAX_SIZE];
int numTop=-1;

// --- Operator Stack Functions ---

// Pushes an item onto the operator stack
void opPush(char item) {
    if (opTop>=MAX_SIZE-1) {
        printf("Stack Overflow\n");
    }
    else {
        opStack[++opTop]=item;
    }
}

// Pops an item from the operator stack
char opPop(){
    if (opTop<0){
        return '\0'; // Return null char for underflow
    }
    else{
        return opStack[opTop--];
    }
}

// Peeks at the top item of the operator stack
char opPeek(){
    if (opTop<0){
        return '\0';
    }
    else{
        return opStack[opTop];
    }
}

// --- Utility Functions ---

// Compares and returns the precedence of the operator (comp -> Compare Precedence)
int comp(char op){
	if(op=='+'||op=='-') return 1;
	if(op=='*'||op=='/') return 2;
	return 0;
}

// Checks if a character is a digit
int isDigit(char c){
	if(c>='0'&&c<='9'){
		return 1;
	}
	return 0;
}

// Checks if a character is a valid operator
int isOperator(char c) {
    if(c=='+'||c=='-'||c=='*'||c=='/') return 1;
}

// --- Core Conversion Function ---

// Converts an infix expression to a postfix expression
char* InfixtoPostfix(char *infix){
	int i=0, j=0, parenCount=0;
	//Allocate memory for the postfix string. Allocate slightly more for spaces.
	char *postfix=(char *)malloc(MAX_SIZE * sizeof(char));
	
	if(postfix==NULL){
		printf("Memory allocation failed");
		return NULL;
	}
	
	char next;
	opTop=-1; // Reset operator stack
	printf("%s\n", infix);
	while(infix[i]!='\0'){
		next=infix[i];
		if(isDigit(next)==1){
			 // Read multi-digit number
			while(isDigit(infix[i])){
				postfix[j]=infix[i];
				j++;
				i++;
			}
			postfix[j]=' '; // Add space separator for evaluation
			j++;
			i--; // Decrement i to correctly process the next character
		}
		else if(next=='('){
			parenCount++;
			opPush(next);
			
		}
		else if(next==')'){
			parenCount--;
			if (parenCount< 0) { // Check for unbalanced ')'
                free(postfix);
                printf("Error: Unbalanced right parenthesis ')'\n");
                return NULL;
        	}
        	
			while(opTop>-1 && opPeek()!='('){
				postfix[j]=opPop();
				j++;
			}
			if(opTop>-1 && opPeek()=='(' ) opPop();
			else{
				free(postfix);
                printf("Error: Miss matched parenthesis.\n");
                return NULL;
			}
		}else if(isOperator(next)) {
            // Pop operators with greater or equal precedence
            while(opTop>-1 && opPeek()!='('&&comp(opPeek()) >= comp(next)) {
                postfix[j++] = opPop();
            }
            opPush(next);
        } else if (next!=' ' && next!='\t') {
            // Handle invalid characters
             free(postfix);
             printf("Error: Invalid character '%c' in expression.\n", next);
             return NULL;
        }
		
		i++;
	}
	if (parenCount!=0) {
        free(postfix);
        printf("Error: Unbalanced left parenthesis '('\n");
        return NULL;
    }
    
    // Pop any remaining operators
    while (opTop>-1) {
         if (opPeek()=='(') {
            // Should be caught by paren_count check, but safe
            free(postfix);
            printf("Error: Unbalanced parenthesis remaining.\n");
            return NULL;
        }
        postfix[j++] = opPop();
    }
    
    postfix[j] = '\0';
    return postfix;
}

// --- Number Stack Functions ---

// Pushes an item onto the number stack
void numPush(int item){
    if (numTop>=MAX_SIZE-1) {
        printf("Stack Overflow\n");
    }
    else{
        numStack[++numTop]=item;
    }
}

// Pops an item from the number stack
int numPop(){
    if (numTop<0){
        printf("Error: Stack Underflow\n");
        return 0;
    }
    else{
        return numStack[numTop--];
    }
}

// --- Evaluation Utility ---

// Performs the arithmetic operation
int operate(int num1, int num2, char op){
	switch(op){
		case '+' : return num1+num2;
		case '-' : return num1-num2;
		case '*' : return num1*num2;
		case '/' : 
			if(num2==0){
				printf("Error: Division by zero.\n");
				return 0;
			}
			return num1/num2;
		default: return 0;
	}
}

// --- Core Evaluation Function ---

// Evaluates the postfix expression
int evaluate(char *postfix){
	int i=0;
	numTop=-1; // Reset number stack
	char next;
	int num1=0, num2, num3, result;
	if(postfix==NULL) return 0;
	
	while(postfix[i]!='\0'){
		next=postfix[i];
		if (next == ' '|| next=='\t') {
            i++;
            continue;
        }
		if(isDigit(next)==1){
			num1=0;
			// Read multi-digit number
			while(isDigit(postfix[i])==1){
			
				num1=num1*10+(postfix[i]-'0');
				i++;
			}
			numPush(num1);
		}else if(isOperator(next)){
			if(numTop < 1) {
                printf("Error: Postfix expression is invalid (missing operands).\n");
                return 0;
            }
			int num3=numPop();
			int num2=numPop();
			
			result=operate(num2, num3, next);
			numPush(result);
			i++;
		}else{
			i++;
		}
	}
	if(numTop==0){
		return numPop();
	}else if(numTop>0){
        printf("Error: Postfix expression is invalid (too many operands).\n");
        return 0;
    }
	else {
        printf("Error: Postfix expression is empty or malformed.");
        return 0;
    }
}



int main() {
    char infix_expression[MAX_SIZE];
    char *postfix_expression = NULL;
    char choice = 'y';

    // Loop continues as long as the user wants to evaluate more expressions
    while (choice=='y' || choice=='Y') {
        printf("\nEnter an infix expression (e.g., (10+2)*3): \n");
        
        // Read the entire line of input
        if (fgets(infix_expression, MAX_SIZE, stdin)==NULL) {
            fprintf(stderr, "Error reading input.\n");
            break;
        }
        // Remove trailing newline character added by fgets
        infix_expression[strcspn(infix_expression, "\n")]=0; 
        
        // 1. Convert Infix to Postfix
        postfix_expression=InfixtoPostfix(infix_expression);
        
        if (postfix_expression!=NULL) {
            printf("\n? Postfix Expression: %s\n", postfix_expression);
            
            // 2. Evaluate Postfix Expression
            int final_result=evaluate(postfix_expression);
            
            // Check if evaluation was successful (numTop should be -1 after cozumle returns the result)
            // Note: evaluate handles its own stack check before returning
            if (numTop==-1) { 
                printf("?? Result: %d\n", final_result);
            } else {
                printf("? Evaluation Failed. Check error messages above.\n");
            }

            // Free the dynamically allocated memory
            free(postfix_expression);
            postfix_expression = NULL;
        } else {
            printf("\n? Conversion Failed. Check error messages above.\n");
        }
        
        printf("\nDo you want to evaluate another expression? (y/n): ");
        if (scanf(" %c", &choice) != 1) {
            choice = 'n'; // Assume 'n' on read failure
        }
        // Consume the rest of the line (including newline) after scanf for the next loop
        while (getchar() != '\n'); 
    }
    
    printf("\nExiting the program. Goodbye!\n");
    getch();
    return 0;
}

