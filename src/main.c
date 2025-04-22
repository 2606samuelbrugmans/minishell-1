/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:06:50 by scesar            #+#    #+#             */
/*   Updated: 2025/04/22 16:06:56 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    tokenizer(t_commands *cmds, char **tab_inputs)
{
    
}

t_commands    *parser(char *inputs)
{
    char **tab_inputs;
    size_t  index;
    t_commands *cmds;
    
    tab_inputs = ft_split_shell(inputs, ' ');
    if (!tab_inputs)
    return(NULL); //need error message
    while(tab_inputs[index])
    {
        tokenizer(cmds, tab_inputs[index]);
        index ++;
    }
    free(tab_inputs);
    
}

void	shell()
{
    char	*input;
    // char    **tab_inputs;   //should free before quit
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
        commands = parser(input);
        // tab_inputs = ft_split(input, ' ');      //see if my split is enough (work with tab or smth ele)
        // run_command(tab_inputs);
        
        free(input);
    }
}

int	main(void)
{
	shell();
	return(0);
}
