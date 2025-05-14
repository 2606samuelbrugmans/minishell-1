#include "../inc/minishell.h"

int first_check(char *input)
{
    size_t index;

    index = 0;
    if (unclosed_quotes(input))
    {
        printf("Syntax error: Unclosed quotes.\n");
        return(0);
    }
    while(input[index])
    {
        while(input[index] == ' ')
            index ++;
        if(input[index] = '|')
        {
            printf("Syntax error near unexpected token `|'\n");
            return(0);
        }
        if((unsigned char)input[index] < 32 && input[index] != '\t' && input[index] != '\n')
        {
            printf("Syntax error: Unescaped character: ASCII %d\n", input[index]);
            return(0);
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