/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrugman <sbrugman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:47:40 by sbrugman          #+#    #+#             */
/*   Updated: 2025/03/07 18:17:46 by sbrugman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/wait.h>

char	*path_finding(char **argv, char **env, int who);

/* pipex.c */
void	process(char **argv, char **env, int *fd);
char	*get_path(char *command_to_path, char *paths, int index);
int		find_string(char **env, char *path);
char	*potential_pathing(char *paths, char *command_to_path, int *index);
void	putcommand(char *command_to_path, char *potential_path, int size);

/* familia */
void	execute(char *path, char **args, int file);
void	ft_putstr_fd(char *s, int fd);
void	error(char *reason, char **args, char *path, int file);
void	child_process(char **argv, char **env, int *fd);
void	second_child(char **argv, char **env, int *fd);

/* basic functions */
int		ft_strlen(char *string, int index);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);
void	ft_get_next_word(char **next_word, size_t *next_word_len, char c);
size_t	ft_nb_words(char const *s, char c);
char	**ft_malloc_error(char **tab);

#endif
