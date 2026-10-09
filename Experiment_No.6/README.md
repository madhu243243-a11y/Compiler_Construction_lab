# Experiment 6: Design of a Simple High-Level Language (MiniLang)

**Course Outcome:** CO6

## Aim
To design a simple high-level language containing arithmetic and logical operations, pointers, branch instructions, and loop instructions, and implement lexical analysis and basic syntax validation using C.

## Language Specification (MiniLang)
MiniLang supports:
1. **Variable Declarations:** `int a; int b;`
2. **Arithmetic Operators:** `+`, `-`, `*`, `/`, `%`
3. **Relational Operators:** `<`, `>`, `<=`, `>=`, `==`, `!=`
4. **Logical Operators:** `&&`, `||`, `!`
5. **Pointer Operations:** `int *p; p = &a; b = *p;`
6. **Branch Instructions:** `if (condition) { ... } else { ... }`
7. **Loop Instructions:** `while (condition) { ... }`
8. **Delimiters:** `(`, `)`, `{`, `}`, `;`

## Compiler Front-End Architecture
```text
MiniLang Source Program
          ↓
   Lexical Analyzer
          ↓
        Tokens
          ↓
    Syntax Parser
          ↓
  Syntax Validation
          ↓
   Semantic Analysis
          ↓
   Intermediate Code
```

## Algorithm
1. Start the program.
2. Read the multi-line MiniLang source program terminated by `#`.
3. Scan the input character by character:
   - Identify keywords (`int`, `if`, `else`, `while`).
   - Identify identifiers and constants.
   - Identify arithmetic, relational, and logical operators.
   - Identify delimiters and special symbols.
4. Display all classified tokens in tabular format.
5. Perform basic syntax checking:
   - Validate matching braces `{}` and parentheses `()`.
   - Report any unbalanced brackets or unexpected syntax errors.
6. Display syntax validation result and terminate.

## Program Code
See [`minilang.c`](./minilang.c).

## Sample Input & Output

### Input
```text
int a;
int b;
a = 10;
b = 20;

if (a < b)
{
    a = a + 1;
}

while (a < b)
{
    a = a + 1;
}
#
```

### Output
```text
============================================
         MINILANG IMPLEMENTATION
============================================

----- LEXICAL ANALYSIS -----
int             : KEYWORD
a               : IDENTIFIER
;               : DELIMITER
int             : KEYWORD
b               : IDENTIFIER
;               : DELIMITER
a               : IDENTIFIER
=               : OPERATOR
10              : CONSTANT
;               : DELIMITER
b               : IDENTIFIER
=               : OPERATOR
20              : CONSTANT
;               : DELIMITER
if              : KEYWORD
(               : DELIMITER
a               : IDENTIFIER
<               : OPERATOR
b               : IDENTIFIER
)               : DELIMITER
{               : DELIMITER
a               : IDENTIFIER
=               : OPERATOR
a               : IDENTIFIER
+               : OPERATOR
1               : CONSTANT
;               : DELIMITER
}               : DELIMITER
while           : KEYWORD
(               : DELIMITER
a               : IDENTIFIER
<               : OPERATOR
b               : IDENTIFIER
)               : DELIMITER
{               : DELIMITER
a               : IDENTIFIER
=               : OPERATOR
a               : IDENTIFIER
+               : OPERATOR
1               : CONSTANT
;               : DELIMITER
}               : DELIMITER

----- SYNTAX CHECK -----
Syntax structure is valid.

============================================
               END OF PROGRAM
============================================
```