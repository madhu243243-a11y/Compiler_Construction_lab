#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 500

char keywords[][10] = {
    "int", "if", "else", "while"
};

int isKeyword(char word[])
{
    int i;
    for (i = 0; i < 4; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int isDelimiter(char ch)
{
    return (ch == '(' || ch == ')' ||
            ch == '{' || ch == '}' ||
            ch == ';');
}

int isOperatorStart(char ch)
{
    return (ch == '+' || ch == '-' ||
            ch == '*' || ch == '/' ||
            ch == '%' || ch == '<' ||
            ch == '>' || ch == '=' ||
            ch == '!' || ch == '&' ||
            ch == '|');
}

void lexicalAnalysis(char input[])
{
    int i = 0;
    char token[MAX];

    printf("\n----- LEXICAL ANALYSIS -----\n");
    while (input[i] != '\0')
    {
        /* Ignore white spaces */
        if (isspace(input[i]))
        {
            i++;
            continue;
        }

        /* Identifier or Keyword */
        if (isalpha(input[i]) || input[i] == '_')
        {
            int j = 0;
            while (isalnum(input[i]) || input[i] == '_')
            {
                token[j++] = input[i++];
            }
            token[j] = '\0';

            if (isKeyword(token))
                printf("%-15s : KEYWORD\n", token);
            else
                printf("%-15s : IDENTIFIER\n", token);
        }
        /* Number */
        else if (isdigit(input[i]))
        {
            int j = 0;
            while (isdigit(input[i]))
            {
                token[j++] = input[i++];
            }
            token[j] = '\0';
            printf("%-15s : CONSTANT\n", token);
        }
        /* Delimiter */
        else if (isDelimiter(input[i]))
        {
            printf("%-15c : DELIMITER\n", input[i]);
            i++;
        }
        /* Operators */
        else if (isOperatorStart(input[i]))
        {
            char op[3];
            op[0] = input[i];
            op[1] = '\0';

            if ((input[i] == '<' || input[i] == '>' ||
                 input[i] == '=' || input[i] == '!') &&
                input[i + 1] == '=')
            {
                op[1] = '=';
                op[2] = '\0';
                i += 2;
            }
            else if (input[i] == '&' && input[i + 1] == '&')
            {
                op[1] = '&';
                op[2] = '\0';
                i += 2;
            }
            else if (input[i] == '|' && input[i + 1] == '|')
            {
                op[1] = '|';
                op[2] = '\0';
                i += 2;
            }
            else
            {
                i++;
            }
            printf("%-15s : OPERATOR\n", op);
        }
        else
        {
            printf("%-15c : UNKNOWN SYMBOL\n", input[i]);
            i++;
        }
    }
}

void syntaxCheck(char input[])
{
    int i = 0;
    int braces = 0;
    int parentheses = 0;
    int errors = 0;

    printf("\n----- SYNTAX CHECK -----\n");
    while (input[i] != '\0')
    {
        if (input[i] == '{')
            braces++;
        else if (input[i] == '}')
        {
            braces--;
            if (braces < 0)
            {
                printf("Error: Unexpected '}'\n");
                errors++;
                braces = 0;
            }
        }
        else if (input[i] == '(')
            parentheses++;
        else if (input[i] == ')')
        {
            parentheses--;
            if (parentheses < 0)
            {
                printf("Error: Unexpected ')'\n");
                errors++;
                parentheses = 0;
            }
        }
        i++;
    }

    if (braces != 0)
    {
        printf("Error: Unbalanced braces {}\n");
        errors++;
    }

    if (parentheses != 0)
    {
        printf("Error: Unbalanced parentheses ()\n");
        errors++;
    }

    if (errors == 0)
        printf("Syntax structure is valid.\n");
    else
        printf("Syntax errors detected.\n");
}

int main()
{
    char input[MAX];
    int position = 0;
    char ch;

    printf("============================================\n");
    printf("         MINILANG IMPLEMENTATION\n");
    printf("============================================\n");
    printf("\nEnter MiniLang program.\n");
    printf("Enter # on a new line to finish.\n\n");

    while (position < MAX - 1)
    {
        ch = getchar();
        if (ch == '#')
            break;
        input[position++] = ch;
    }
    input[position] = '\0';

    /* Check for empty input */
    if (position == 0)
    {
        printf("\nNo MiniLang program was entered.\n");
        printf("Please enter at least one valid statement.\n");
        return 0;
    }

    lexicalAnalysis(input);
    syntaxCheck(input);

    printf("\n============================================\n");
    printf("               END OF PROGRAM\n");
    printf("============================================\n");

    return 0;
}