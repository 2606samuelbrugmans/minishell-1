/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_instr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:06:44 by scesar            #+#    #+#             */
/*   Updated: 2025/06/25 12:13:34 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

void  *add_redir(t_redir **redir_list, t_token_type type, char *file)
{
	t_redir	*new;
	t_redir	*last;

	new = malloc(sizeof(t_redir));
	if(!new)
		return(NULL);		//malloc error
	new->type = type;
	new->file_name = ft_strdup(file);
	if(!new->file_name)
		return(NULL);		//malloc error
	new->next = NULL;
	if(!(*redir_list))
	{
		*redir_list = new;
	}
	else
	{
		last = *redir_list;
		while(last->next)
			last = last->next;
		last->next = new;
	}
	return(new);
}

void set_redir(t_instructions *instr, t_commands *cmd)
{
	size_t index;

	index = 0;
	// instr->redir = malloc(sizeof(t_redir));
	while(cmd->args[index])
	{
		if(cmd->args[index]->type == REDIR_IN || cmd->args[index]->type == HEREDOC)
		{
			if (cmd->args[index + 1] && cmd->args[index + 1]->type == FILENAME)
				add_redir(&instr->in_redir, cmd->args[index]->type, cmd->args[index + 1]->content);
			index++;
		}
		else if(cmd->args[index]->type == REDIR_OUT || cmd->args[index]->type == APPEND)
		{
			if (cmd->args[index + 1] && cmd->args[index + 1]->type == FILENAME)
				add_redir(&instr->out_redir, cmd->args[index]->type, cmd->args[index + 1]->content);
			index++;
		}
		index ++;
	}
}

t_instructions	*init_insrtu(t_minishell *minish, t_commands	*cmd_as_tokens)
{
	size_t	index;

	index = 0;
	minish->instru = malloc((minish->number_of_commands + 1) * sizeof(t_instructions));
	if(!minish->instru)
		return(NULL);		//malloc error;
	while(cmd_as_tokens)
	{
		ft_bzero(&minish->instru[index], sizeof(t_instructions));
		minish->instru[index].command = ft_strdup(cmd_as_tokens->as_str);
		minish->instru[index].executable = cmd_as_tokens->args;
		minish->instru[index].path_command = NULL;
		minish->instru[index].in_redir = NULL;
		minish->instru[index].out_redir = NULL;
		set_redir(&minish->instru[index], cmd_as_tokens);
		cmd_as_tokens = cmd_as_tokens->next_command;
		index ++;
	}
	return(minish->instru);
}
