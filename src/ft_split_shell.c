#include "../inc/minishell.h"

void free_tab(char **tab)
{
    size_t i;
    
    i = 0;
    if (!tab)
        return;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

size_t next_arg_len(char *input, size_t index)
{
    size_t len;
    char quote;

    len = 0;
    quote = NONE;
    if (input[index] == '\'' || input[index] == '\"')
    {
        quote = input[index];
        len++;
        index++;
    }
    while (input[index] != '\0')
    {
        if(quote != NONE && input[index] == quote)
        {
            len++;
            index++;
            break;
        }
        else if (quote == NONE && input[index] == ' ')
            break;
        len++;
        index++;
    }
    return(len);
}

int    put_elem_in_tab(char **tab, size_t tab_index, char *input, size_t *input_index)
{
    char *elem;
    size_t elem_size;
    size_t elem_index;
    elem_index = 0;
    elem_size = next_arg_len(input, *input_index) + 1;
    elem = malloc(sizeof(char) * elem_size);
    if (!elem)
        return(0);                 //need to handle malloc error
    while(elem_index < elem_size - 1)
    {
        elem[elem_index] = input[*input_index];
        elem_index++;
        (*input_index)++;
    }
    elem[elem_index] = '\0';
    tab[tab_index] = elem;
    return(1);
}

size_t nbr_of_elem(char *input)
{
    size_t index;
    size_t nbr;
    char quote;
    
    index = 0;
    nbr = 0;
    quote = NONE;
    while(input[index])
    {
        while(input[index] == ' ')
            index++;
        if (input[index] == '\'' || input[index] == '\"')
        {
            quote = input[index];
            index++;
            while(input[index] && input[index] != quote)
                index++;
            if (input[index] == quote)
                index++;
        }
        while (input[index] != ' ' && input[index])
            index++;
        if (input[index] || (input[index - 1] != ' ')) //checks if the line finishes with spaces or if we reached the end
            nbr++;
    }
    return(nbr);
}

char **ft_split_shell(char *input)
{
	size_t	input_index;
	size_t	tab_index;
	size_t	tab_size;
    char **tab_of_elem;
    
    if(!input)
        return(NULL);
    tab_index = 0;
    input_index = 0;
    tab_size = nbr_of_elem(input) + 1;
    tab_of_elem = malloc(sizeof(char *) * (tab_size));
    if(!tab_of_elem)
        return (NULL);                 //malloc error
    while (tab_index < tab_size - 1)
    {
        while(input[input_index] == ' ')
            input_index++;
        if (input[input_index] != '\0')
        {
            if(!put_elem_in_tab(tab_of_elem, tab_index, input, &input_index))
            {
                free_tab(tab_of_elem);
                return(NULL);
            }
        }
        tab_index++;
    }
    tab_of_elem[tab_index] = NULL;
    return (tab_of_elem);
}
