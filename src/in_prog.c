#include "../inc/minishell.h"

char *replace_var(t_minishell minishell, char *string, size_t *str_ind, char *temp)
{
	size_t len_var;
    t_env *actual_var;
    char *pres_var;
    char *renew_str;

    len_var = 0;
    renew_str = NULL;
    (*str_ind)++;
    while(string[*str_ind + len_var] && string[*str_ind + len_var] != ' ' && string[*str_ind + len_var] != '\"')
        len_var++;
    pres_var = ft_substr(string, *str_ind, len_var);
    if(!pres_var)
        return(NULL);       //malloc error;
    (*str_ind) += len_var;
    // printf("str[%zu] : |%c|\n", *str_ind, string[*str_ind]);
    // printf("pres_var : %s\n", pres_var);
    actual_var = get_VAR(minishell.envp, minishell.local_var, pres_var);
	if(!actual_var)
		renew_str = temp;
	else
		renew_str = ft_strjoin(temp, actual_var->value);
	return (renew_str);
}

char    *get_new_string(t_minishell minishell, char *string)
{
	char *temp;
    char *new_str;
    bool in_double;
    size_t str_ind;
    size_t new_str_ind;

    str_ind = 0;
    new_str_ind = 0;
    in_double = false;
    new_str = ft_strdup("");
    if(!new_str)
        return(NULL);   //malloc error
	while(string[str_ind])
	{
		if(string[str_ind] == '\"')
        {
            if(in_double == false)
                in_double = true;
            else
                in_double = false;
        }
		if(string[str_ind] == '\'' && !in_double)
		{
			while(string[str_ind] && string[str_ind] != '\'')
			{
				temp = new_str;
				new_str = ft_strjoin(temp, string[str_ind]);
				if(!new_str)
				{
					free(temp);
					return(NULL);		//malloc errorr
				}
				str_ind++;
			}
			new_str = ft_strjoin(temp, string[str_ind]); //add ' or '\0'
		}
		if(string[str_ind] == '$')
		{
			temp = new_str;
			new_str = replace_var(minishell, string, &str_ind, temp);
			if(!new_str);
				return(NULL);
		}
		if(string[str_ind])
		{
			temp = new_str;
			new_str = ft_strjoin(temp, string[str_ind]);
			if(!new_str);
			{
				free(temp);
				return(NULL);
			}
			str_ind++;
		}
	}
	return(new_str);
}
