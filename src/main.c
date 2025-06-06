/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:06:50 by scesar            #+#    #+#             */
/*   Updated: 2025/06/06 16:50:20 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	shell(char **env)
{
    char	*input;
    t_commands *commands;
    char	cwd[PATH_MAX];
    char	prompt[PATH_MAX + 3];

    commands = NULL;
    getcwd(cwd, sizeof(cwd));
    ft_strlcpy(prompt, cwd, sizeof(prompt));        //see if I should make an strcpy
    ft_strlcat(prompt, "$ ", sizeof(prompt));       //see if I should make an strcat
	while (1)
	{
        input = readline(prompt);
		if (!input)
        {
            printf("\nExiting shell...\n");
            break;
        }
        if (*input)
            add_history(input);
        // printf("inputs : |%s|\n\n", input); why doesnt work with empty input ?
        // add_env_var (input);                                                                   //here but maybe more efficient to put it inside ft_split_shell
        commands = tokenizer(input, env);
        if(commands)
        {
            while(commands)
            {
                int i = 0;
                printf("|-------------cmd-------------|\n");
                printf("%s\n", commands->as_str);
                i = 0;
                while(commands->args[i])
                {
                    printf("token [%d] : %s | type : %d\n", i, commands->args[i]->content, commands->args[i]->type);
                    i++;
                }
                commands = commands->next_command;
            }
        }
    }
}

int	main(int ac, char **av, char **env)
{
	shell();
	return(0);
}
