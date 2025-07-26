/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:11:14 by scesar            #+#    #+#             */
/*   Updated: 2025/07/24 10:05:38 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	heredoc_handle(char *stop)
{
	char	*input;
	int		fd;
	char	*tmp_file;

	tmp_file = "/tmp/.minishell_heredoc";
	fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (-1);
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
			break ;
		if (input && (ft_strncmp(input, stop, ft_strlen(input)) == 0))
		{
			free(input);
			break ;
		}
		putstr_bsn(input, fd, YES);
		free(input);
	}
	close(fd);
	fd = (open(tmp_file, O_RDONLY));
	unlink(tmp_file);
	return (fd);
}

void	treat_redir_in(t_minishell *minish, t_redir *redir, int parser, int *fd)
{
	if (redir->type == REDIR_IN)
	{
		if (access(redir->file_name, F_OK) != 0)
			error(minish, "no such file or directory:", redir->file_name, 127);
		else if (access(redir->file_name, R_OK) != 0)
			error(minish, "permission denied:", redir->file_name, 126);
		else
		{
			(*fd) = open(redir->file_name, O_RDONLY);
			if ((*fd) == -1)
				error(minish, "couldn't open file", redir->file_name, 126);
		}
	}
	else if (redir->type == HEREDOC)
	{
		(*fd) = heredoc_handle(redir->file_name);
		if ((*fd) == -1)
			error(minish, "heredoc error", NULL, 130);
	}
}

void	treat_redir_out(t_minishell *minish, t_redir *redir,
		int parser, int *fd)
{
	if (access(redir->file_name, F_OK) == 0
		&& access(redir->file_name, W_OK) != 0)
		error(minish, "permission denied:", redir->file_name, 126);
	if (redir->type == REDIR_OUT)
		(*fd) = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == APPEND)
		(*fd) = open(redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if ((*fd) == -1)
		error(minish, "couldn't open file", redir->file_name, 126);
}

void	access_test(t_minishell *minish, t_instructions *instr, int parser)
{
	int	index;
	int	fd;

	index = 0;
	while (index < instr->nb_files_in)
	{
		treat_redir_in(minish, &instr->in_redir[index], parser, &fd);
		if (index != instr->nb_files_in - 1)
			close(fd);
		else
			instr->pipe[0] = fd;
		index++;
	}
	index = 0;
	while (index < instr->nb_files_out)
	{
		treat_redir_out(minish, &instr->out_redir[index], parser, &fd);
		if (index != instr->nb_files_out - 1)
			close(fd);
		else
			instr->pipe[1] = fd;
		index++;
	}
}

void	no_redirection_proc(t_minishell *minish, t_instructions *instr,
		int parser)
{
	if (instr->nb_files_in > 0)
		dup2(instr->pipe[0], STDIN_FILENO);
	else if (parser != 0)
		dup2(minish->fd_pipes[parser - 1][0], STDIN_FILENO);
	if (instr->nb_files_out > 0)
		dup2(instr->pipe[1], STDOUT_FILENO);
	else if (parser != minish->number_of_commands - 1)
		dup2(minish->fd_pipes[parser][1], STDOUT_FILENO);
	close_stuff(minish, parser);
	if (instr->nb_files_in > 0)
		close(instr->pipe[0]);
	if (instr->nb_files_out > 0)
		close(instr->pipe[1]);
}
