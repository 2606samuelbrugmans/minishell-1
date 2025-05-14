
#include "../inc/minishell.h"

int count_next_tokens(char **tab_input, size_t index)
{
    int tokens;

    while(tab_input[index] && ft_strncmp(tab_input[index], "|", ft_strlen(tab_input[index])) != 0)
    {
        tokens++;
        index++;
    }
    return(tokens);
}

int count_commands(char *input)
{
    size_t index;
    int cmd_nbr;

    index = 0;
    cmd_nbr = 1;
    while(input[index])
    {
        if (input[index] == '\'')
            cmd_nbr++;
        index++;
    }
    return(cmd_nbr);
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

void    tokenizer(t_commands *first_command, char *input)
{
    t_commands *command;
    char **tab_input;
    size_t tab_index;
    size_t cmd_index;

    // cmd_nbr = count_commands(input);     //see if "if (cmd_nbr = 0)" needed
    if (!first_check(input));
        return;
    tab_input = ft_split_shell(input);
    if (!tab_input)
        return; // could be empty input or malloc error I think but have to check
    command->args = malloc(sizeof(t_token *) * (count_next_tokens(tab_input, tab_index) + 1)); //don't think its the right size
    if (!command->args)
        return;
    tab_index = 0;
    while (tab_input[tab_index])
    {
        if (ft_strcmp(tab_input[tab_index], "|") == 0)
        {
            command->args[cmd_index] = NULL;
            command->next_command = malloc(sizeof(t_commands));
            if (!command->next_command)
                return;

            command = command->next_command;
            command->args = malloc(sizeof(t_token *) * (count_next_tokens(tab_input, tab_index) + 1));
            if (!command->args)
                return;
            cmd_index = 0;
            tab_index++;
            continue;
        }
        if (!tok_type_init(tab_input, command, cmd_index))
            return;

        cmd_index++;
        tab_index++;
    }
    command->args[cmd_index] = NULL;
    command->next_command = NULL;
    free_tab(tab_input);
    return;
}

// t_commands    tokenizer(char *input)
// {
//     t_commands commands;
//     char **tab_input;
//     size_t tab_index;

//     first_check(input);
//     commands.args = NULL;
//     commands.valid = false;
//     tab_input = ft_split_shell(input);
//     if (!tab_input)
//         return(commands); // could be empty input or malloc error I think but have to check
//     tab_index = 0;
//     commands.args = malloc(sizeof(t_token *) * (tab_size(tab_input) + 1));
//     if(!commands.args)
//     {
//         free_tab(tab_input);
//         exit(1);        //malloc error
//     }
//     while(tab_input[tab_index])
//     {
//         if(!tok_type_init(tab_input, &commands, tab_index))
//         {
//             free_tab(tab_input);
//             exit(1);
//         }
//         tab_index++;
//     }
//     commands.args[tab_index] = NULL;
//     free_tab(tab_input);
//     commands.valid = true;
//     return(commands);
// }
