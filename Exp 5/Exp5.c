#include<stdio.h>
#include<string.h>

void convert(char alpha[], char beta[]) {
    printf("\n");
    printf("Considering A` to be X\n");
    printf("Considering e as epsilon");
    char dash= 'X';
    char arr1[50];
    char arr2[50];
    arr1[0] = alpha[0];
    arr1[1] = '-';
    arr1[2] = '>';
    
    arr2[0] = dash;
    arr2[1] = '-';
    arr2[2] = '>';
    
    int j = 3;
    int k = 3;
    while(j<strlen(beta)+3) {
        if(beta[j-3] == '|') {
            arr1[k++] = dash;
        } else {
            arr1[k++] = beta[j-3];    
        }
        j++;
    }
    arr1[j] = dash;
    printf("\n");
    j = 3;
    while(j<strlen(alpha)+1) {
        arr2[j] = alpha[j-2];
        j++;
    }
    arr2[j++] = dash;
    arr2[j++] = '|';
    arr2[j++] = 'e';
    
    
    printf("\n");
    printf("New productions\n");
    for(int i=0;i<strlen(arr1)-9;i++) {
        printf("%c", arr1[i]);    
    }
    printf("\n");
    for(int i=0;i<strlen(arr2);i++) {
        printf("%c", arr2[i]);    
    }
    return;
}

void getRange(int j, int i, char productions[][50]) {
    int k=3;
    char beta[50];
    char alpha[50];
    int idxA = 0;
    int idxB = 0;
    while(k!=j) {
        beta[idxB++] = productions[i][k];
        k++;
    }
    while(productions[i][k] != '|') {
        alpha[idxA++] = productions[i][k++];
    }
    k++;
    while(k != strlen(productions[i])) {
        beta[idxB++] = productions[i][k++];
    }
    printf("This is alpha extracted out\n");
    for(int i=0;i<strlen(alpha)-1;i++) {
        printf("%c", alpha[i]);
    }
    printf("\n");
    printf("This is beta extracted out\n");
    printf("%s", beta);
    convert(alpha, beta);
    return;
}

int main()
{

    int a = 1,rule=-1;
    char productions[50][50],production[50], beta[50];
    printf("Enter Productions in Format A->B|C\n");
    do
    {
        rule++;
        scanf("%s",production);
        strcpy(productions[rule],production);
        printf("Press 1 to Enter More\n");
        scanf("%d",&a);
    }while(a);
    
    for(int i=0;i<=rule;i++)
    {
        for(int j=0;j<=strlen(productions[i]);j++)
        {
            printf("%c ",productions[i][j]);
        }
        printf("\n");
    }
    for(int i=0;i<=rule;i++)
    {
        for(int j=3;j<=strlen(productions[i]);j++)
        {
            if((productions[i][j-1] == '>' || productions[i][j-1] == '|') && (productions[i][0] == productions[i][j]))
            {
                printf("%s is Left Recursive Grammar\n",productions[i]);
                getRange(j, i, productions);
                break;
            }
        }
    }
}