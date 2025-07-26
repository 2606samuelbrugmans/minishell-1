/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:45:43 by scesar            #+#    #+#             */
/*   Updated: 2025/07/25 17:50:53 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	treat_input(t_minishell **minish, char *input)
{
	t_commands	*cmd_as_tokens;

	if (empty_input(input))
		return (1);
	if (!first_check(input))
		return ((*minish)->last_exit_status = 2, 3);			//still have to return 3 ?
	if (add_loc_var(&(*minish)->envp, &(*minish)->local_var, input))
		return (1);
	cmd_as_tokens = tokenizer(input);
	if (!cmd_as_tokens)
		return (0);
	if (!second_check(cmd_as_tokens))
		return(3);								//still have to change the 3 ?
	(*minish)->number_of_commands = count_commands(cmd_as_tokens);
	(*minish)->instru = init_insrtu((*minish), cmd_as_tokens);
	free_commands(cmd_as_tokens);
	if (!(*minish)->instru)
		return (0);
	int i = 0;
	// while((*minish)->instru[0].in_redir[i].file_name)
	// {
	// 	printf("file : %s\n", (*minish)->instru[0].in_redir[i].file_name);
	// 	printf("type : %d\n", (*minish)->instru[0].in_redir[i].type);
	// 	i++;
	// }
	// i = 0;
	// while((*minish)->instru[0].out_redir[i].file_name)
	// {
	// 	printf("file : %s\n", (*minish)->instru[0].out_redir[i].file_name);
	// 	printf("type : %d\n", (*minish)->instru[0].out_redir[i].type);
	// 	i++;
	// }
	(*minish)->fd_pipes = malloc(sizeof(int [2])
			* ((*minish)->number_of_commands));
	if (!(*minish)->fd_pipes)
		return (0);
	run(*minish);
	return (1);
}

void	init_minish(t_minishell **minish, char **envp)
{
	char	*shlvl[3];

	shlvl[0] = "export";
	shlvl[1] = "shlvl=1";
	shlvl[2] = NULL;
	(*minish) = malloc(1 * sizeof(t_minishell));
	if (!(*minish))
		exit_shell("Something went wrong while initializing minish\n", NULL);
	(*minish)->envp = NULL;
	(*minish)->local_var = NULL;
	(*minish)->parsed_string = NULL;
	(*minish)->instru = NULL;
	(*minish)->number_of_commands = 0;
	(*minish)->fd_pipes = NULL;
	(*minish)->last_exit_status = 0;
	write(2, "seg2", 5);

	if (!set_envp(&(*minish)->envp, envp))
		exit_shell("Something went wrong while setting env\n", minish);
	write(2, "seg3", 5);

	if (get_var(&(*minish)->envp, &(*minish)->local_var, "shlvl") == NULL)
		exec_builtin(shlvl, (*minish));
	write(2, "seg4", 5);

	setup_signals();
	write(2, "seg5", 5);

}

int	main(int ac, char **av, char **envp)
{
	t_minishell		*minish;
	char			*prompt;
	char			*input;
	int				input_res;

	init_minish(&minish, envp);
	while (1)
	{
		write(2, "seg", 4);
		prompt = get_prompt(&minish->envp);
		write(2, "prompt", 7);
		if (!prompt)
			break ;
		input = readline(prompt);
		free(prompt);
		if (!input)
			break ;
		if (input && *input)
			add_history(input);
		if (treat_input(&minish, input) == 0)
			return (free(input), free_minish_total(&minish), 0);
		free(input);
	}
	free_minish_total(&minish);
	printf("exit\n");
	return (0);
}
