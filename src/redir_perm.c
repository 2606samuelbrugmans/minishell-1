#include "../inc/minishell.h"

int	find_last_slash(const char *path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	while (i > 0 && path[i] != '/')
		i--;
	return (i);
}

/*
 * Copies directory part from path into dir_buf.
 * Returns 1 if directory part exists and was copied,
 * 0 if no directory part (no slash found).
 * Assumes dir_buf_size > 0.
 */
int copy_dir_part(const char *path, char *dir_buf, int dir_buf_size)
{
	int	i;
	int	copy_len;
	int	j;

	i = find_last_slash(path);
	if (i <= 0)
		return (0);
	if (i < dir_buf_size - 1)
		copy_len = i;
	else
		copy_len = dir_buf_size - 1;
	j = 0;
	while (j < copy_len)
	{
		dir_buf[j] = path[j];
		j++;
	}
	dir_buf[j] = '\0';
	return (1);
}

/*
 * Checks if the directory part of the path exists and is a directory.
 * Returns 1 if no directory part or directory exists, 0 otherwise.
 */
int	check_directory_part(const char *path)
{
	char	dir[1024];

	if (!copy_dir_part(path, dir, 1024))
		return (1); // no directory part, so treat as valid

	return (is_directory(dir));
}
int	check_perm(char *path, t_token_type type)
{
	int index;

	if (path[0] == 0)
		return (ft_printf(2, "bash: %s: No such file or directory\n", path),2);
	if (!check_directory_part(path))
		return (ft_printf(2, "bash: %s: No such file or directory\n", path),2);
	if (is_directory(path))
		return (ft_printf(2, "%s: Is a directory\n", path), 3);
	if (type == REDIR_IN && access(path, F_OK) != 0)
		return (ft_printf(2, "%s: No such file or directory\n", path),2);
	if (access(path, F_OK) == 0 && out_tok(type) && (access(path, R_OK) != 0))
		return (ft_printf(2, "%s: Permission denied\n", path), 3);
	else if (type == REDIR_IN && (access(path, W_OK ) != 0))
		return (ft_printf(2, "%s: Permission denied\n", path), 3);
	return (1);
}
