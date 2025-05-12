#include "../inc/minishell.h"

void first_check(char *input)
{
    size_t index;

    index = 0;
    if (unclosed_quotes(input))
    {
        printf("Syntax error: Unclosed quotes.\n");
        exit(1);
    }
    while(input[index])
    {
        if((unsigned char)input[index] < 32 && input[index] != '\t' && input[index] != '\n')
        {
            printf("Syntax error: Unescaped character: ASCII %d\n", input[index]);
            exit(1);
        }
        index ++;
    }

}

int unclosed_quotes(char *input)
{
    size_t index;

    index = 0;
    while(input[index])
    {
        if(input[index] == '\'' || input[index] == '\"')
        {
            if (end_quotes(input, &index) == 0)
                return(YES);
        }
        else
            index ++;
    }
        return(NOPE);
}