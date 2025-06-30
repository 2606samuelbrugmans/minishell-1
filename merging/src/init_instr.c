/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   init_instr.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/20 20:06:44 by scesar			#+#	#+#			 */
/*   Updated: 2025/06/25 12:13:34 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

# include "../inc/minishell.h"

void free_instr (t_instructions *instru)
{

}

// void set_redir(t_instructions *instr, t_commands *cmd)
// {
// 	size_t index;

// 	index = 0;
// 	// instr->redir = malloc(sizeof(t_redir));
// 	while(cmd->args[index])
// 	{
// 		if(cmd->args[index]->type == REDIR_IN || cmd->args[index]->type == HEREDOC)
// 		{
// 			if (cmd->args[index + 1] && cmd->args[index + 1]->type == FILENAME)
// 				add_redir(&instr->in_redir, cmd->args[index]->type, cmd->args[index + 1]->content);
// 			index++;
// 		}
// 		else if(cmd->args[index]->type == REDIR_OUT || cmd->args[index]->type == APPEND)
// 		{
// 			if (cmd->args[index + 1] && cmd->args[index + 1]->type == FILENAME)
// 				add_redir(&instr->out_redir, cmd->args[index]->type, cmd->args[index + 1]->content);
// 			index++;
// 		}
// 		index ++;
// 	}
// }

int init_redir(t_instructions **instr, t_commands *cmd, size_t *index, size_t *in_index, size_t *out_index)
{
	int in_count;
	int out_count;

	in_count = count_redir(&cmd, REDIR_IN);
	out_count = count_redir(&cmd, REDIR_OUT);
	(*index) = 0;
	(*in_index) = 0;
	(*out_index) = 0;
	(*instr)->in_redir = malloc(sizeof(t_redir) * (in_count + 1));
	if(!(*instr)->in_redir)
		return(0);		//malloc error
	(*instr)->out_redir = malloc(sizeof(t_redir) * (out_count + 1));
	if(!(*instr)->out_redir)
		return(0);		//malloc error
	(*instr)->nb_files_in = in_count;
	(*instr)->nb_files_out = out_count;
	(*instr)->in_redir[in_count].file_name = NULL;
	(*instr)->out_redir[out_count].file_name = NULL;
	return(1);
}

t_redir  *add_redir(t_redir **redir_list, t_token_type type, char *file, size_t *io_index)
{
	t_redir *added;

	(*redir_list)[*io_index].file_name = ft_strdup(file);
	if(!(*redir_list)[*io_index].file_name)
		return(NULL);		//malloc error
	(*redir_list)[*io_index].type = type;
	added = &(*redir_list)[*io_index];
	(*io_index) ++;
	return(added);
}


//////// in progress
int set_redir(t_instructions *instr, t_commands *cmd)
{
	size_t index;
	size_t in_index;
	size_t out_index;

	if(!init_redir(instr, cmd, &index, &in_index, &out_index))
		return(0);
	while(cmd->args[index])
	{
		if(cmd->args[index]->type == REDIR_IN || cmd->args[index]->type == HEREDOC)
		{
			if(!add_redir(&(*instr)->in_redir, cmd->args[index]->type, cmd->args[index + 1]->content, &in_index))
				return(0);
			index += 2;
		}
		else if(cmd->args[index]->type == REDIR_OUT || cmd->args[index]->type == APPEND)
		{
			if(!add_redir(&(*instr)->out_redir, cmd->args[index]->type, cmd->args[index + 1]->content, &out_index))
				return(0);
			index += 2;
		}
		else
			index ++;
	}
	return(1);
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
		if(!set_redir(&minish->instru[index], cmd_as_tokens))
			return(NULL);			//malloc error;
		cmd_as_tokens = cmd_as_tokens->next_command;
		index ++;
	}
	return(minish->instru);
}
