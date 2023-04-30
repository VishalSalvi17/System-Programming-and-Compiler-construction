/*
Vishal Salvi
TE COMPS
C - Batch
2019230069
Exp 6c  - To implement different types of Parsers for the given grammar.
*/

// Including all the required libraries
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


// initializing all the required variables
int terminal_count;		//no.of terminals

char start;		//starting non terminal symbol

FILE *fp;		//file pointer

// Initializing the parsing table
char slrparserTable[20][20][20]={ {"  ","  ","s4","s5","  "}, {"s6","  ","  ","  ","a"}, {"r2","  ","s4","s5","r2"},
	{"r4","s8","r4","r4","r4"}, {"r6","r6","r6","r6","r6"}, {"r7","r7","r7","r7","r7"},
	{"  ","  ","s4","s5","  "}, {"r3","s8","r3","r3","r3"}, {"r5","r5","r5","r5","r5"},
	{"r1","  ","s4","s5","r1"},
};

char nonTermsArray[100];	//array of non terminals

int numprod;		//no. of productions

char productionArray[50][20];	//2d array for productions

char alternateProd[50][20];

// Initializing the GoTo table
int GoToTable[20][20]={
	{1,2,3}, {0,0,0}, {0,0,7},
	{0,0,0}, {0,0,0}, {0,0,0},
	{0,9,3}, {0,0,0},{0,0,0},
	{0,0,7}
};

//array of terminals
char terms[100];

//
//no.of non terminals
int nonterm;

int idx=0;

//input string buffer
char inpbuffer[20];

//input buffer index
int buffidx=0;

//stack
char stack[50];

//stack top index
int stacktop=-1;

//
//check if character is non terminal_count
int isNonTerminal(char c)
{
	for(int i=0;i<nonterm;i++)
	{
		if(c==nonTermsArray[i])
		{
			//if non term return 1
			return 1;
		}
	}
	//if not a non term return 0
	return 0;
}

int isStEmpty()
{
	if(stacktop==0) {
        return 0;
        // Stack is empty
    } else {
        return 1;
        // Stack is not empty
    }
}

char popFromStack()
{
	char data;
	char emp='N';
	//if stack not empty popFromStack the stack top

	if(isStEmpty())
	{
		data=stack[stacktop];
		stacktop-=1;
		return data;
	}
	else
	{
		printf("Stack is empty\n");
		return emp;
		//if stack is empty return N
	}
}

void pushIntoStack(char data)
{
	stacktop+=1;
	stack[stacktop]=data;
	//pushIntoStack data in stack
}

void printSt()
{
	//print stack
	for (int i=0;i<=stacktop;i++)
	{
		printf("%c",stack[i]);
	}
	if(stacktop>=7)
	{
		printf("\t");
	}
	else
	printf("\t\t");
}

void printBuffer()
{
	//print buffer
	for (int i=buffidx;i<strlen(inpbuffer);i++)
	{
		printf("%c",inpbuffer[i]);
	}
	printf("\t\t");
}

int parse()
{
	while(1)
	{
        // if stacktop is non terminal
		if(isNonTerminal(stack[stacktop])==1)
		{
			// prev character in stack
			int prev=stack[stacktop-1]-'0';
			int ntidx;//to get the index of non terminal
			int f=0; //flag
			for(int i=0;i<=nonterm;i++)
			{
				//finding index of non terminal
				if(stack[stacktop]==nonTermsArray[i])
				{
					ntidx=i;
					f=1;
					//if found flag=1
				}
			}
			if(f!=1)//if flag is not 1, then non terminal not 					found
			{

				printf("\nSyntax error, string cannot be parsed");//print error
				return 0;
				//end while
			}

			// find GOTO value for corresponding state and non 				terminal_count

			if(GoToTable[prev][ntidx]!=0)
			{
				printf("%d",GoToTable[prev][ntidx]);
				//pushIntoStack the goto value in stack

				pushIntoStack(GoToTable[prev][ntidx]+'0');
				//print output
				printf("\n");

				printSt();
	    			printBuffer();
    			}
    			else  //if no goto value found
    			{
    				printf("\nSyntax error, string cannot be parsed");
				return 0;
    			}

		}
		else 	//if stacktop is number
		{
			int num = stack[stacktop]-'0';
			//number at stacktop

			int tidx;
			//terminal_count index

			int f=0;
			//flag

			for(int i=0;i<=terminal_count;i++)
			{
				//finding index of terminal_count
				if(inpbuffer[buffidx]==terms[i])
				{
					tidx=i;
					f=1;
					//if found, flag=1
				}
			}
			if(f!=1)
			{
				//if flag not 1 then error
				printf("\nSyntax error, string cannot be parsed");		//print error
				return 0;
				//end while loop and return to 						main function
			}

            //store the action
			char action[10];

            //copy the required action
			strcpy(action,slrparserTable[num][tidx]);
			printf("%s",action);

			if(action[0]=='s')
			{
				//if action is shift
				printf(" Shift %c ", inpbuffer[buffidx]);

				//pushIntoStack input character to stack
				pushIntoStack(inpbuffer[buffidx]);
				buffidx++;
				pushIntoStack(action[1]);
				//pushIntoStack action number to stack

				//print output
				printf("\n");
				printSt();
    			printBuffer();

			}
			else if(action[0]=='r')
			{
				//if action is reduce
				char product[10];
				//product string

				strcpy(product,alternateProd[action[1]-'0']);
				//copy product string which stores the respective production

				printf(" Reduce %s",product);
				int len=strlen(product)-3;

				//popFromStack the right side of production
                // We always popFromStack double the lenght of the string
				for(int i=0;i<len*2;i++)
				{
					popFromStack();
				}

				//pushIntoStack left side of production
				pushIntoStack(product[0]);

				//print output
				printf("\n");
				printSt();
    			printBuffer();

			}
			else if(action[0]=='a')
			{
				//accept the string
				//print accept and end while loop
				printf(" Accept");
				return 1;
			}
			else
			{
				//if no value in action table
				printf("\nSyntax error, string cannot be parsed");
				return 0;
			}
		}
	}
}

int main()
{
    FILE *fp=fopen("input.txt","r");

    fscanf(fp,"%d",&terminal_count);
    fgetc(fp);

    // Now taking in the input for all the terminals
    for(int i=0; i<terminal_count; i++)
    {
        fscanf(fp,"%s", &terms[i]);
		//input of terminal symbols
        fgetc(fp);
    }


    // Also appending $ at the end since we require $ at the end
    terms[terminal_count]='$';

    fscanf(fp, "%d", &nonterm);
    fgetc(fp);

    // Now taking te input of all the no terminals
    for(int i=0; i<nonterm; i++)
    {
        fscanf(fp,"%s", &nonTermsArray[i]);
        fgetc(fp);
    }

    fscanf (fp, "%d", &numprod);
    fgetc(fp);

    for(int i=0; i<numprod; i++)
    {
        fscanf(fp, "%s", productionArray[i]);
        char left[3];
        int k=0;

        //separating all the productions
        for(int j=0;j<3;j++)
        {
            // now seperating out all productions
        	left[j]=productionArray[i][j];
            // Below statement is used to store a single complex production in two different lines
            // For example T->FT|id
            // The store T->FT and T->id
        	alternateProd[idx][k++]=productionArray[i][j];
        }

        // Now segrating according to the above mentioned rule
        for(int j=3;j<strlen(productionArray[i]);j++)
        {
        	if(productionArray[i][j]!='|')
        	{
        	    // So here we segregate
        		alternateProd[idx][k++]=productionArray[i][j];
        	}
        	else
        	{
        		idx++;
        		k=0;
        		while(k<3)
        		{
                    // Now storing the values into the alternateProd array
        			alternateProd[idx][k]=left[k];
        			k++;
        		}
        	}

        }
        idx++;
    }

    fgetc(fp);

    // Taking input for the start symbol
    fscanf(fp,"%s", &start);
    fgetc(fp);

    // Taking input for the input string
    fscanf(fp,"%s", inpbuffer);
    fgetc(fp);

    // pushing $ symbol onto stack
    pushIntoStack('$');

    // pushing start symbol '0' onto stack
    pushIntoStack('0');

    printf("\nStack\t\tInput Buffer\tAction\n");
    printSt();
    printBuffer();
    int result=parse();

    if(result>0)
    {//if parsing successfull
    	printf("\nThe parser has accepted the input string\n");
    }

    return 0;
}
