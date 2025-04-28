/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:06:50 by scesar            #+#    #+#             */
/*   Updated: 2025/04/28 16:00:37 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	shell()
{
    char	*input;
    char    **tab_inputs;   //should free before quit
    t_commands *commands;
    char	cwd[PATH_MAX];
    char	prompt[PATH_MAX + 3];
    
    getcwd(cwd, sizeof(cwd));
    ft_strlcpy(prompt, cwd, sizeof(prompt));        //see if I should make an strcpy
    ft_strlcat(prompt, "$ ", sizeof(prompt));       //see if I should make an strcat
    commands = malloc(sizeof(commands));
	while (1)
	{
        input = readline(prompt);      // need to add the $
		if (!input)
        {
            printf("\nExiting shell...\n");
            break;
        }
        if (*input)
            add_history(input);
        // commands = tokenizer(input);
        tab_inputs = ft_split_shell(input);      //see if my split is enough (work with tab or smth ele)
        
        // run_command(tab_inputs);
        int i = 0;
        while(tab_inputs[i])
        {
            printf("arg[%d] : %s\n", i, tab_inputs[i]);
            i++;
        }
        free_tab(tab_inputs);
    }
}

int	main(void)
{
	shell();
	return(0);
}
