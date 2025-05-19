/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:06:50 by scesar            #+#    #+#             */
/*   Updated: 2025/05/19 18:03:51 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	shell()
{
    char	*input;
    t_commands *commands;
    char	cwd[PATH_MAX];
    char	prompt[PATH_MAX + 3];
    
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
        commands = tokenizer(input);
        if(commands)
        {
            printf("top\n");
            while(commands)
            {
                int i = 0;
                printf("|-------------cmd-------------|\n");
                while(commands->args[i])
                {
                    printf("%s ", commands->args[i]->content);
                    i++;
                }
                printf("\n");
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

int	main(void)
{
	shell();
	return(0);
}
