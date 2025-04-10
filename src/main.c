/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephen <stephen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:06:50 by scesar            #+#    #+#             */
/*   Updated: 2025/04/10 16:22:06 by stephen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// char *find_command(char *command)
// {
//     char *path;
//     char **path_tab;

//     path = getenv("PATH");
//     path_tab = ft_split(path, ':');
    
//     while()
// }

void    run_command(char **tab_inputs)
{
    pid_t   pid;
    int status;

    if (!tab_inputs || !tab_inputs[0])
        return;
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }
    else if (pid == 0)
    {
        if (execve(tab_inputs[0], tab_inputs, NULL) == -1)
        {
            perror("execve");
            return;
        }
    }
    else
        waitpid(pid, &status, 0);
}

void	shell()
{
    char	*input;
    char    **tab_inputs;   //should free before quit
    char	cwd[PATH_MAX];
    char	prompt[PATH_MAX + 3];
    
    getcwd(cwd, sizeof(cwd));
    ft_strlcpy(prompt, cwd, sizeof(prompt));        //see if I should make an strcpy
    ft_strlcat(prompt, "$ ", sizeof(prompt));       //see if I should make an strcat
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
        tab_inputs = ft_split(input, ' ');      //see if my split is enough (work with tab or smth ele)
        run_command(tab_inputs);
        //what would happend if I put run_command(ft_split(input, ' ') ? Does it works ? Do I need to free smth afterwards? I could save some lines...)
        
        // int j = 0;
        // while(tab_inputs[j])
        // {
        //     printf("tab_inputs[%d] = %s\n", j, tab_inputs[j]);
        //     j++;
        // }
        free(input);
        free(tab_inputs);
    }
}

int	main(void)
{
	shell();
	return(0);
}
