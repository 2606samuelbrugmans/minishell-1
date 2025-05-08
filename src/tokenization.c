
#include "../inc/minishell.h"

int tok_type_init(char *tab_elem, t_commands *commands)
{
    size_t index;
    
    index = 0;
    commands->args[index]->content = tab_elem;
    if (special_char(tab_elem) != 0)
        commands->args[index]->type = special_char(tab_elem);
    else if (tab_elem[0] == '-')
        commands->args[index]->type = FLAG;
    else
    commands->args[index]->type = CMD;
    return(0);
}

t_commands    tokenizer(char *input)
{
    t_commands commands;
    char **tab_input;
    size_t tab_index;
    
    tab_input = ft_split_shell(input);
    tab_index = 0;
    commands.args = malloc(sizeof(t_token) * (tab_size(tab_input) + 1));
    while(tab_input[tab_index])
    {
        if (valid_arg(tab_input[tab_index]) == NOPE)        //will treat inputs errors from here
            exit(1);
        else
            tok_type_init(tab_input[tab_index], &commands);
        tab_index++;
    }
}