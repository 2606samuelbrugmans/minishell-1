
#include "../inc/minishell.h"

int valid_arg(char *arg)
{
    return(1);
}

int tok_type_init(char **tab_input, t_commands *commands, size_t index)
{
    char *previous_arg;

    previous_arg = NULL;
    if(index > 0)
        previous_arg = tab_input[index - 1];
    commands->args[index] = malloc(sizeof(t_token));
    if (!commands->args[index])
        return (0); // Handle malloc failure
    commands->args[index]->content = ft_strdup(tab_input[index]);
    if (ft_strlen(tab_input[index]) == 1 && special_char(tab_input[index], 0) != NONE)
        commands->args[index]->type = special_char(tab_input[index], 0);        //see if (char)tab_input[0] prettier
    else if (tab_input[index][0] == '-')
        commands->args[index]->type = FLAG;
    else
    {
        if(previous_arg 
            && special_char(previous_arg, 0) == REDIR_IN 
            || special_char(previous_arg, 0) == REDIR_OUT)
        {
                commands->args[index]->type = FILENAME;
        }
        else
            commands->args[index]->type = CMD;
    }
    return(0);
}

t_commands    tokenizer(char *input)
{
    t_commands commands;
    char **tab_input;
    size_t tab_index;
    
    tab_input = ft_split_shell(input);
    tab_index = 0;
    commands.args = malloc(sizeof(t_token *) * (tab_size(tab_input) + 1));
    while(tab_input[tab_index])
    {
        if (valid_arg(tab_input[tab_index]) == NOPE)        //will treat inputs errors from here
            exit(1);
        else
            tok_type_init(tab_input, &commands, tab_index);
        tab_index++;
    }
    commands.args[tab_index] = NULL;
    // free_tab(tab_input);
    return(commands);
}
