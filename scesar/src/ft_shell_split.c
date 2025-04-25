#include "../inc/minishell.h"

// bool reach_next_arg(char *input, size_t index, int quote)

size_t next_arg_len(char *input, size_t index, int quote)
{
    size_t  len;

    len = 0;
    if(quote == SIMPLE_QUOTE)
    {
        while(input[index] != "\'" || input[index] != '\0')
        {
            len++;
            index++;
        }
    }
    else if(quote == DOUBLE_QUOTE)
    {
        while(input[index] != "\"" || input[index] != '\0')
        {
            len++;
            index++;
        }
    }
    else
    {
        while(input[index] != " " || input[index] != '\0')
        {
            len++;
            index++;
        }
    }
    return(len);
}

void    put_elem_in_tab(char **tab, size_t tab_index, char *input, size_t input_index, int quote)
{
    char *elem;
    size_t elem_size;
    size_t elem_index;

    elem_index = 0;
    elem_size = next_arg_len(input, input_index, quote) + 1;
    elem = (char *)malloc(sizeof(char) * elem_size);
    while(elem_index < elem_size + 1)
    {
        elem[elem_index] = input[input_index];
        elem_index++;
        input_index++;
    }
    elem_index = '\0';
    *tab[tab_index] = elem;
}

size_t nbr_of_elem(char *input)
{
    size_t index;
    size_t res;
    
    index = 0;
    res = 0;
    while(input[index])
    {
        while(input[index] == ' ')
            index++;
        while(input[index] != ' ' && input[index] != '\0')
        {
            if (input[index] == "\'")
            {
                while(input[index] != "\'" || input[index] != '\0')
                    index++;
            }
            else if (input[index] == "\"")
            {
                while(input[index] != "\"" || input[index] != '\0')
                    index++;
            }
            index++;
        }
        res++;
    }
    return(res);
}

char **ft_split_shell(char *input)
{
	size_t	input_index;
	size_t	tab_index;
	size_t	tab_size;
    char **tab_of_elem;
    
    tab_index = 0;
    input_index = 0;
    tab_size = nbr_of_elem(input) + 1;
    tab_of_elem = (char**)malloc(sizeof(char *) * (tab_size));
    while (tab_size > 0)
    {
        while(input[input_index] == ' ')
        input_index++;
        while(input[input_index] != ' ' && input[input_index] != '\0')
        {
            if (input[input_index] == "\'")
                put_elem_in_tab(tab_of_elem, tab_index, input, input_index, SIMPLE_QUOTE);
            else if (input[input_index] == "\"")
                put_elem_in_tab(tab_of_elem, tab_index, input, input_index, DOUBLE_QUOTE);
            else
                put_elem_in_tab(tab_of_elem, tab_index, input, input_index, 0);
        }
    }
}