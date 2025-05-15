
#include "../inc/minishell.h"

size_t count_next_tokens(t_token **whole_commands, size_t index)
{
    size_t tokens;

    tokens = 0;
    while(whole_commands[index] && ft_strncmp(whole_commands[index]->content, "|", ft_strlen(whole_commands[index]->content)) != 0)
    {
        tokens++;
        index++;
    }
    return(tokens);
}

t_commands *new_command_node()
{
    t_commands *cmd = malloc(sizeof(t_commands));
    if (!cmd)
        return NULL;
    cmd->args = NULL;
    cmd->next_command = NULL;
    cmd->valid = true;
    return (cmd);
}

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

void  linker(t_commands whole_commands, t_commands *current_command, size_t *whole_index)
{
    size_t curr_index;
    size_t count;

    curr_index = 0;
    count = count_next_tokens(whole_commands.args, *whole_index);
    current_command->args = malloc(sizeof(t_token *) * (count + 1));
    if(!current_command->args)
        return;     //malloc error
    while(curr_index < count)
    {
        current_command->args[curr_index] = whole_commands.args[*whole_index];
        curr_index++;
        (*whole_index)++;
    }
    current_command->args[curr_index] = NULL;
    if(whole_commands.args[*whole_index] && whole_commands.args[*whole_index]->type == PIPE)
        (*whole_index)++;

}

t_commands    *tokenizer(char *input)
{
    t_commands whole_commands;
    t_commands *first;
    t_commands *current;
    char **tab_input;
    size_t tab_index;

    whole_commands.args = NULL;
    whole_commands.valid = false;
    if(!first_check(input))
        return(NULL);
    tab_input = ft_split_shell(input);
    if (!tab_input)
        return(NULL); // could be empty input or malloc error I think but have to check
    tab_index = 0;
    whole_commands.args = malloc(sizeof(t_token *) * (tab_size(tab_input) + 1));
    if(!whole_commands.args)
    {
        free_tab(tab_input);
        exit(1);        //malloc error
    }
    while(tab_input[tab_index])
    {
        if(!tok_type_init(tab_input, &whole_commands, tab_index))
        {
            free_tab(tab_input);
            exit(1);
        }
        tab_index++;
    }
    whole_commands.args[tab_index] = NULL;
    tab_index = 0;
    first = new_command_node();
    if(!first)
        return (NULL);
    linker(whole_commands, first, &tab_index);
    current = first;
    while(whole_commands.args[tab_index])
    {
        current->next_command = new_command_node();
        current = current->next_command;
        linker(whole_commands, current, &tab_index);
    }
    free_tab(tab_input);
    free(whole_commands.args);
    return(first);
}
