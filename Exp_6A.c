//Vishal Salvi
//2019230069
//BATCH C
//52

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

char *parsing_table[4][8] = {
    {"","i",";",":","n","r",",","$"},
    {"D","iL;","NIL","NIL","NIL","NIL","NIL","NIL"},
    {"L","NIL","NIL",":T","NIL","NIL",",iL","NIL"},
    {"T","NIL","NIL","NIL","n","r","NIL","NIL"}
};

int top = 1;

void display_parsing_table() {

    printf("Parsing table of the grammar is: \n\n");
    for(int i = 0;i<4;i++) {
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


void parse(char input[]) {
    int i = 0;
    char stack[100];
    stack[0] = '$';
    stack[1] = 'D';
    stack[2] = '\0';
    bool flag = true;
    printf("\n------------------------------------------------------------------------");
    printf("\n\nStack \tInput Buffer \tProduction\n");
    printf("%s \t%s\n",stack,input);
    char *production;
    while(strlen(stack) != 0) {
        if(getRowIndex(stack[top]) == -1 || getColIndex(input[i]) == -1) {
            flag = false;
            break;
        }
        production = parsing_table[getRowIndex(stack[top])][getColIndex(input[i])];

        printf("\t\t\t%c -> %s\n",stack[top],production);

        pop(stack);


        for(int k=strlen(production)-1;k>=0;k--) {
            push(production[k],stack);

        }

        while(stack[top] == input[i] && strlen(stack) != 0){
            if(stack[top] == '$') {
                printf("%s \tAccepted\n",stack);
            }
            else {
                printf("%s \t%s\n",stack,input);
            }
            pop(stack);
            strcpy(input,sliceInput(input));

        }

        printf("%s \t%s\n",stack,input);
    }
    if(!flag) {
        printf("%s \tNot Accepted\n",stack);
    }

}

int main() {
    printf("The context free grammar is: \n");
    printf("D=iL;\nL=,iL|:T\nT=n|r\n\n");


	int state = -1;
	char input[40];

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