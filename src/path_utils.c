#include "../inc/minishell.h"

int	path_len(char *string, int index)
{
	int	second_index;

	second_index = 0;
	while (string[index + second_index] != '\0'
		&& string[index + second_index] != ':'
		&& string[index + second_index] != ' ')
		second_index++;
	return (second_index);
}

void	putcommand(char *command_to_path, char *potential_path, int size)
{
	int	j;

	j = 0;
	while (command_to_path[j] != '\0')
	{
		potential_path[size + j] = command_to_path[j];
		j++;
	}
}
