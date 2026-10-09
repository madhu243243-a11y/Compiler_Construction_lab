#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* List of C keywords recognized by the lexical analyzer */
const char *keywords[] = {
    "int", "float", "char", "double",
    "if", "else", "while", "for", "return"
};

int isKeyword(const char *word)
{
    int i;
    for (i = 0; i < 9; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int isSpecialSymbol(char ch)
{
    return (ch == '{' || ch == '}' || ch == '(' || ch == ')' ||
            ch == ';' || ch == ',' || ch == '[' || ch == ']');
}

int main()
{
    int ch;
    printf("Enter C program (Ctrl+Z then Enter on Windows, Ctrl+D on Linux to finish):\n");

    while ((ch = getchar()) != EOF)
    {
        /* Ignore whitespace */
        if (isspace(ch))
        {
            continue;
        }

        /* Identifiers and Keywords */
        if (isalpha(ch) || ch == '_')
        {
            char word[100];
            int idx = 0;
            word[idx++] = (char)ch;

            while ((ch = getchar()) != EOF && (isalnum(ch) || ch == '_'))
            {
                if (idx < 99)
                {
                    word[idx++] = (char)ch;
                }
            }
            word[idx] = '\0';

            if (isKeyword(word))
                printf("%s -> KEYWORD\n", word);
            else
                printf("%s -> IDENTIFIER\n", word);

            if (ch != EOF)
                ungetc(ch, stdin);
        }
        /* Numbers */
        else if (isdigit(ch))
        {
            char num[100];
            int idx = 0;
            num[idx++] = (char)ch;

            while ((ch = getchar()) != EOF && isdigit(ch))
            {
                if (idx < 99)
                {
                    num[idx++] = (char)ch;
                }
            }
            num[idx] = '\0';

            printf("%s -> NUMBER\n", num);

            if (ch != EOF)
                ungetc(ch, stdin);
        }
        /* Multi-character and Single-character Operators */
        else if (ch == '=' || ch == '!' || ch == '<' || ch == '>' ||
                 ch == '&' || ch == '|' || ch == '+' || ch == '-' ||
                 ch == '*' || ch == '/' || ch == '%')
        {
            int next = getchar();

            /* Check 2-character operators */
            if ((ch == '=' && next == '=') ||
                (ch == '!' && next == '=') ||
                (ch == '<' && next == '=') ||
                (ch == '>' && next == '=') ||
                (ch == '&' && next == '&') ||
                (ch == '|' && next == '|') ||
                (ch == '+' && next == '+') ||
                (ch == '-' && next == '-'))
            {
                printf("%c%c -> OPERATOR\n", ch, next);
            }
            else
            {
                if (next != EOF)
                    ungetc(next, stdin);
                printf("%c -> OPERATOR\n", ch);
            }
        }
        /* Special Symbols */
        else if (isSpecialSymbol(ch))
        {
            printf("%c -> SPECIAL SYMBOL\n", ch);
        }
        /* Unknown characters */
        else
        {
            printf("%c -> UNKNOWN\n", ch);
        }
    }

    return 0;
}