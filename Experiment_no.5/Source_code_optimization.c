#include <stdio.h>
#include <string.h>

int main()
{
    char expression[100];

    printf("Enter expression: ");
    fgets(expression, sizeof(expression), stdin);

    if (strstr(expression, "* 2") != NULL)
    {
        printf("\nOptimized expression:\n");
        printf("Replace multiplication by 2 with addition.\n");
        printf("x = i + i\n");
    }
    else
    {
        printf("\nNo strength reduction applicable.\n");
    }

    return 0;
}