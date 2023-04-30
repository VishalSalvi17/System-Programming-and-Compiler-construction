// EXPERIMENT 6A
// Name=Vishal Salvi
// Batch=C
// UID = 2019230069
// Roll No = 52

// Aim = � To implement Non-recursive Predictive Parser (Top-down parsing method)  for the given grammar


// creating parsing table for the given grammar {V,T,P,S} using first and follow
// V={D,L,T}
// T={i , ; , : , integer (n) , real (r) , ,}
// P={
    // D → i L;
    // L →, i L | : T
    // T → integer | real
//  }
// S=D
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

// created parsing table
char *parsing_table[4][8] = {
    // first left column is of variables
    // Top row is of terminals 
    {"","i",";",":","n","r",",","$"},
    {"D","iL;","NIL","NIL","NIL","NIL","NIL","NIL"},
    {"L","NIL","NIL",":T","NIL","NIL",",iL","NIL"},
    {"T","NIL","NIL","NIL","n","r","NIL","NIL"}
};

// Starting with initalizing top of stack as 1 
int top = 1;

// function to print parsing table
void display_parsing_table() {

    printf("Parsing table of the grammar is: \n\n");
    for(int i = 0;i<4;i++) {
         // loop for iterating throught the parsing table
        for(int j = 0;j<8;j++) {
            printf("%s \t",parsing_table[i][j]);
        }
        printf("\n");
    }
    
}

int getRowIndex(char str) {
    char row[3] = {"DLT"};
    for(int i=0;i<3;i++){
        if (str == row[i])
            return i+1;
    }
    return -1;
}

int getColIndex(char str) {
    char colmn[] = {"i;:nr,$"};
    for(int i=0;i<7;i++){
        if (str == colmn[i])
            return i+1;
    }
    return -1;
}

// Stack functions
void push(char str, char *stack) {
    top++;
    stack[top] = str;
    stack[top+1] = '\0';
}

void pop(char *stack) {
    stack[top] = '\0';
    top--;
}

char* sliceInput (char *input) {
    char* final = (char*)malloc( 50 * sizeof(char) );

	int i,j = 0;

	for(i = 1; input[i] != '\0'; i++){

		final[j] = input[i];
		j++;
	}
    final[j] = '\0';

    return final;

}

// main parsing algorithm
void parse(char input[]) {
    int i = 0;
    // creating stack of size 100
    char stack[100];
    // initialize first block of stack as $
    stack[0] = '$';
    // initialize second block of stack as D i.e. start symbol 
    stack[1] = 'D';
    // initialize third block of stack as end
    stack[2] = '\0';
    // accepted variable for checking valid string, initial value is true
    bool accepted = true;

    printf("\n------------------------------------------------------------------------");
    printf("\n\nStack \tInput Buffer \tProduction\n");
    printf("%s \t%s\n",stack,input);
    char *production;
    // run till stack is empty
    // start priting the result as string gets parsed
    while(strlen(stack) != 0) {
        // condition to check invalid string i.e. check if terminals and non terminal exists 
        if(getRowIndex(stack[top]) == -1 || getColIndex(input[i]) == -1) {
            // if any value of row or column is unchanged i.e. not found then string is invalid
            // setting accepted variable as false and exit
            accepted = false;
            break;
        }

        // mapping production in parsing table according to row & column values
        production = parsing_table[getRowIndex(stack[top])][getColIndex(input[i])];

        printf("\t\t\t%c -> %s\n",stack[top],production);

        // pop the last entry of stack
        pop(stack);

        // push the matched productions
        for(int k=strlen(production)-1;k>=0;k--) {
            push(production[k],stack);

        }

        // pop stack while it matched input lookup
        while(stack[top] == input[i] && strlen(stack) != 0){
            if(stack[top] == '$') {
                // in end of parsing i.e. if stack top is $ then accepted
                printf("%s \tAccepted\n",stack);
            }
            else {
                // if not end then print stack and input[start]
                printf("%s \t%s\n",stack,input);
            }
            // pop the stack to start again 
            pop(stack);
            strcpy(input,sliceInput(input));

        }
        // finally print stack values
        printf("%s \t%s\n",stack,input);
    }
    if(!accepted) {
        // for invalid string
        printf("%s \tNot Accepted\n",stack);
    }

}

int main() {
    printf("The context free grammar is: \n");
    printf("D=iL;\nL=,iL|:T\nT=n|r\n\n");


	int state = -1;
	char input[40];

    // exit with 3
	while(1){
		printf("Enter option: \n");
		printf("1. Recognizing string.");
        printf("2. Print Parsing Table.");
        printf("3. Exit.");
		scanf("%d",&state);

		switch (state)
		{
		case 1:

            printf("Enter the string to be parsed: ");
            scanf("%s",input);
            // taking input buffer and concatenating with $ at end 
            strcat(input,"$");
            parse(input);
            break;

        case 2:
			display_parsing_table();
            break;

        case 3:
			exit(0);

		default:
			break;
		}
	}

    return 0;
}
