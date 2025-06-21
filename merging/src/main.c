/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:03:54 by scesar            #+#    #+#             */
/*   Updated: 2025/06/21 14:01:33 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	(*minish)->number_of_commands = count_commands(cmd_as_tokens);
	(*minish)->instru = init_insrtu((*minish), cmd_as_tokens);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	//for you to test, but a bit wierd, I'l simplify things and explain you also
	size_t i = 0;
	while(i < (*minish)->number_of_commands)
	{
		t_instructions *instr = &(*minish)->instru[i];
		printf("--------------------------\n");
		printf("        instr        \n");
		printf("--------------------------\n");
		printf("|whole command : %s|\n", instr->command);
		size_t j = 0;
		while(instr->executable[j])
		{
			printf("executable : %s | type : %d\n", instr->executable[j]->content, instr->executable[j]->type);
			j++;
		}
		t_redir *in = instr->in_redir;
		if(!in)
			printf("NO REDIR_IN\n");

		else
			while(in)
			{
				printf("redir_in : |file=%s|, |type=%d|\n", in->file_name, in->type);
				in = in->next;
			}
		t_redir *out = instr->out_redir;
		if(!out)
			printf("NO REDIR_OUT\n");

		else
			while(out)
			{
				printf("redir_in : |file=%s|, |type=%d|\n", out->file_name, out->type);
				out = out->next;
			}
		i++;
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// free_commands(cmd_as_tokens);
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
