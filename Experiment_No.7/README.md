# Experiment 7: Lexical Analyzer in C

**Course Outcome:** CO3

## Aim
To write a lexical analyzer in C that reads a C-like program and classifies its lexemes into keywords, identifiers, numbers, operators, and special symbols according to lexical analysis rules (longest match, precedence, and token classification).

## Theory
Lexical analysis is the first phase of a compiler. It reads the source code as a stream of characters, groups them into meaningful units called **tokens**, and passes them to the parser. It also removes whitespace/comments and flags lexical errors.

| Term | Meaning | Example |
| :--- | :--- | :--- |
| **Token** | A category of lexical unit | `KEYWORD`, `IDENTIFIER` |
| **Lexeme** | The actual character sequence matched | `int`, `count` |
| **Pattern** | Regular expression describing a token | `[0-9]+` |

### Lexical Analysis Rules Simulated
1. **Longest match:** Multi-character operators like `==`, `!=`, `<=`, `>=`, `&&`, `||`, `++`, `--` take precedence over single characters.
2. **First rule / Priority:** Keywords (`int`, `if`, etc.) are checked before identifiers so they are not categorized as variable names.
3. **Default action:** Characters not recognized by any category are reported as `UNKNOWN`.

---

## Program Code (`lexer.c`)
See [`lexer.c`](./lexer.c):

```c
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
```

---

## Test Cases & Output

### Test Case 1: Sample Program
**Input:**
```c
int a = 10;
if (a > 5)
    a = a + 1;
```

**Output:**
```text
int -> KEYWORD
a -> IDENTIFIER
= -> OPERATOR
10 -> NUMBER
; -> SPECIAL SYMBOL
if -> KEYWORD
( -> SPECIAL SYMBOL
a -> IDENTIFIER
> -> OPERATOR
5 -> NUMBER
) -> SPECIAL SYMBOL
a -> IDENTIFIER
= -> OPERATOR
a -> IDENTIFIER
+ -> OPERATOR
1 -> NUMBER
; -> SPECIAL SYMBOL
```

### Test Case 2: Multi-Character Operators & Braces
**Input:**
```c
while (i <= 10) { i++; }
```

**Output:**
```text
while -> KEYWORD
( -> SPECIAL SYMBOL
i -> IDENTIFIER
<= -> OPERATOR
10 -> NUMBER
) -> SPECIAL SYMBOL
{ -> SPECIAL SYMBOL
i -> IDENTIFIER
++ -> OPERATOR
; -> SPECIAL SYMBOL
} -> SPECIAL SYMBOL
```

### Test Case 3: Unknown Symbol
**Input:**
```c
int x = 5 @ 3;
```

**Output:**
```text
int -> KEYWORD
x -> IDENTIFIER
= -> OPERATOR
5 -> NUMBER
@ -> UNKNOWN
3 -> NUMBER
; -> SPECIAL SYMBOL
```

---
