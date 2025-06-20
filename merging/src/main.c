/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:03:54 by scesar            #+#    #+#             */
/*   Updated: 2025/06/20 15:40:57 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	*init_commands(t_commands	*cmd_as_tokens)
{
	t_instructions *first_instr;
	t_instructions *current_instr;
	t_instructions *next_instr;
	size_t index;

	first_instr = NULL;
	current_instr = NULL;
	next_instr = NULL;
	index = 0;
	while(cmd_as_tokens)
	{
		next_instr = malloc(sizeof(t_instructions));
		if(!next_instr)
			return(NULL);
		next_instr->cmd_name = cmd_as_tokens->args[0]->content;
		next_instr->executable = cmd_as_tokens->as_str;
		next_instr->next = NULL;
		if (!first_instr)
			first_instr = next_instr;
		else
			current_instr->next = next_instr;
		current_instr = next_instr;
		cmd_as_tokens = cmd_as_tokens->next_command;
	}
	return(first_instr);
}

int treat_input(t_minishell **minish, char *input)
{
	t_commands *cmd_as_tokens;

	if(!input || *input == '\0')
		return(1);
	if(!first_check(input))
		return(0);
	if(add_loc_var(&(*minish)->envp,&(*minish)->local_var, input))
		return(1);
	(*minish)->parsed_string = get_new_string(**minish, input);
	if(!(*minish)->parsed_string)
		return(0);		//handle error
	cmd_as_tokens = tokenizer((*minish)->parsed_string);
	if(!cmd_as_tokens)
		return(0);		//handle errors
	(*minish)->instru = init_commands(cmd_as_tokens);
	free(cmd_as_tokens);
	//need to free cmd_as_tokens_here
	if (!(*minish)->instru)
		return(0);		//handle errors or empty inputs
	return (1);
}

void	init_minish(t_minishell **minish, char **envp)
{
	(*minish) = malloc(1 * sizeof(t_minishell));
	(*minish)->envp = NULL;
	(*minish)->local_var = NULL;
	(*minish)->instru = NULL;
	(*minish)->number_of_commands = 0;
	(*minish)->fd_pipes = NULL;
	set_envp(&(*minish)->envp, envp);	//need to free this
}

int	main(int ac, char **av, char **envp)
{
	t_minishell		*minish;
	char *prompt;
	char *input;

	init_minish(&minish, envp);
	while(1)
	{
		prompt = get_prompt(&minish->envp);
		if(!prompt)
			break;
		input = readline(prompt);
		free(prompt);
		if(!input)
		{
			printf("exit\n");
			break;
		}
		add_history(input);
		treat_input(&minish, input);
		free(input);
	}
	free_minish(&minish);
	return(0);
}
