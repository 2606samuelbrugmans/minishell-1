
#include "../inc/minishell.h"

int tok_type_init(char **tab_input, t_commands *commands, size_t index)
{
    t_token *previous_arg;

    previous_arg = NULL;
    commands->args[index] = malloc(sizeof(t_token));
    if (!commands->args[index])
        return (0); // Handle malloc failure
    commands->args[index]->content = ft_strdup(tab_input[index]);
    if(!commands->args[index]->content)
        return(0);
    if(index > 0)  
        previous_arg = commands->args[index - 1];
    if (special_symb(tab_input[index], 0) != NONE)
        commands->args[index]->type = special_symb(tab_input[index], 0);        //see if (char)tab_input[0] prettier
    else if (previous_arg && tab_input[index][0] == '-' && previous_arg->type == CMD)
        commands->args[index]->type = FLAG;
    else
    {
        if(previous_arg && 
            special_symb(previous_arg->content, 0) != NONE &&
            special_symb(previous_arg->content, 0) != PIPE)
            commands->args[index]->type = FILENAME;
        else
            commands->args[index]->type = CMD;
    }
    return(1);
}

t_commands    tokenizer(char *input)
{
    t_commands commands;
    char **tab_input;
    size_t tab_index;

    first_check(input);
    commands.args = NULL;
    commands.valid = false;
    tab_input = ft_split_shell(input);
    if (!tab_input)
        return(commands); // could be empty input or malloc error I think but have to check
    tab_index = 0;
    commands.args = malloc(sizeof(t_token *) * (tab_size(tab_input) + 1));
    if(!commands.args)
    {
        free_tab(tab_input);
        exit(1);        //malloc error
    }
    while(tab_input[tab_index])
    {
        if(!tok_type_init(tab_input, &commands, tab_index))
        {
            free_tab(tab_input);
            exit(1);
        }
        tab_index++;
    }
    commands.args[tab_index] = NULL;
    free_tab(tab_input);
    commands.valid = true;
    return(commands);
}
