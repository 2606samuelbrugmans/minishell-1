#include "../inc/minishell.h"

int add_loc_var(t_env **minish_envp, t_env **minish_local_var, char *input) //minish_loc_var has to be set NULL
{
	t_env *last_var;
	t_env *next_var;
	char *equal;
	size_t key_len;
	size_t i;

	last_var = NULL;
	next_var = NULL;
	equal = valid_var_add(input);
	if (!equal)
		return(0);
	next_var = malloc(sizeof(t_env));
	if(!next_var)
		return(0);							//malloc error
	key_len = equal - input;
	next_var->VAR = ft_substr(input, 0, key_len);
	next_var->value = ft_strdup(equal + 1);
	if(var_already_there(minish_envp, minish_local_var, next_var->VAR))
	{
		free(get_VAR(minish_envp, minish_local_var, next_var->VAR)->value);
		get_VAR(minish_envp, minish_local_var, next_var->VAR)->value = next_var->value;
		free((next_var)->VAR);	//should I free it in var_already_there ?
		free(next_var);
		return(1);
	}
	next_var->next = NULL;
	if(!*minish_local_var)
		*minish_local_var = next_var;
	else
	{
		last_var = *minish_local_var;
		while(last_var->next)
			last_var = last_var->next;
		last_var->next = next_var;
	}
	return(1);
}

char *ft_strjoinchar(char *str, char c)
{
	char *new_str;
	char temp[2];

	temp[0] = c;
	temp[1] = '\0';
	new_str = ft_strjoin(str, temp);
	free(str);
	return(new_str);
}

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
    actual_var = get_VAR(&minishell.envp, &minishell.local_var, pres_var);
	if(!actual_var || !actual_var->value)
		renew_str = ft_strdup(temp);
	else
		renew_str = ft_strjoin(temp, actual_var->value);
	free(temp);
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
			str_ind++;
        }
		else if(string[str_ind] == '\'' && !in_double)
		{
			temp = new_str;
			new_str = ft_strjoinchar(temp, string[str_ind]);
			if(!new_str)
				return(NULL);
			str_ind++;
			while(string[str_ind] && string[str_ind] != '\'')
			{
				temp = new_str;
				new_str = ft_strjoinchar(temp, string[str_ind]);
				if(!new_str)
					return(NULL);		//malloc errorr
				str_ind++;
			}
			if(string[str_ind])
			{
				temp = new_str;
				new_str = ft_strjoinchar(temp, string[str_ind]);
				if(!new_str)
					return(NULL);
				str_ind++;
			}
		}
		else if(string[str_ind] == '$')
		{
			temp = new_str;
			new_str = replace_var(minishell, string, &str_ind, temp);
			if(!new_str)
				return(NULL);
		}
		else
		{
			temp = new_str;
			new_str = ft_strjoinchar(temp, string[str_ind]);
			if(!new_str)
				return(NULL);
			str_ind++;
		}
	}
	return(new_str);
}
