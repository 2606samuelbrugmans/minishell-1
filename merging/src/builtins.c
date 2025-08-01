#include "../inc/minishell.h"

int is_builtin(char *cmd)
{
	return
	(
		ft_strcmp(cmd, "echo") == 0 ||	  //try with smth like echooo, or cd12,...
		ft_strcmp(cmd, "cd") == 0 ||
		ft_strcmp(cmd, "pwd") == 0 ||
		ft_strcmp(cmd, "export") == 0 ||
		ft_strcmp(cmd, "unset") == 0 ||
		ft_strcmp(cmd, "env") == 0 ||
		ft_strcmp(cmd, "exit") == 0
	);
}

int built_in_parent(char *cmd)
{
	return
	(
		ft_strcmp(cmd, "cd") == 0 ||
		ft_strcmp(cmd, "export") == 0 ||
		ft_strcmp(cmd, "unset") == 0 ||
		ft_strcmp(cmd, "exit") == 0
	);
}
// int builtin_env(char **envp)
// {
//	 int index;

//	 index = 0;
//	 while (envp[index] != NULL)
//	 {
//		 printf("%s", envp[index]);
//		 index++;
//	 }
//	 return (0);
// }
int exec_builtin(t_token **executables, t_minishell *shell)
{
	if (ft_strcmp(executables[0]->content, "echo") == 0)
		return builtin_echo(executables);
	if (ft_strcmp(executables[0]->content, "cd") == 0)
		 return builtin_cd(executables, shell);
	if (ft_strcmp(executables[0]->content, "pwd") == 0)
		return builtin_pwd();
	// if (ft_strcmp(argv[0], "export") == 0)
	//	 return builtin_export(argv, shell);
	// if (ft_strcmp(argv[0], "unset") == 0)
		// return builtin_unset(argv, shell);
	// if (ft_strcmp(argv[0], "env") == 0)
	//	 return builtin_env(shell->envp);
	// if (ft_strcmp(argv[0], "exit") == 0)
	//	 return builtin_exit();
	return (-1);
}

int builtin_echo(t_token **executables)
{
	int i;
	int j;
	int newline;

	i = 1;
	j = 1;
	newline = 1;
	if(executables[1] && executables[1]->content && ft_strcmp(executables[1]->content, "-n") == 0)
	{
		while(executables[1]->content[j] && executables[1]->content[j] == 'n')
			j++;
		if(executables[1]->content[j] == '\0')
		{
			newline = 0;
			i = 2;
		}
	}
	while (executables[i])
	{
		printf("%s", executables[i]->content);
		if (executables[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
int builtin_cd(t_token **executables, t_minishell *minish)
{
	 char *path;
	 int home;

	 if (!executables[1]->content)
	 {
		home = find_string(minish->envp, "HOME");
		if (home == -1)
		{
			write(2, "bash: cd: HOME not set", 23);
			return (0);
		}
		path = getenv("HOME");
	}
	else
		path = executables[1]->content;
	if (chdir(path) != 0)
	 {
		perror("cd");
		return 1;
	}
	 // Update PWD and OLDPWD in env here
	return (0);
}

int builtin_pwd(void)
{
	char cwd[500];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("pwd");
	return 0;
}
// int find_nth(char**envp, int meower)
// {
//	 int index = 0;
//	 int current = -1;

//	 while (envp[index] != NULL)
//	 {
//		 if (ft_strcmp(envp[index], envp[meower]) > 0)
//		 {
//			 if (current == -1 || ft_strcmp(envp[index], envp[current]) < 0)
//				 current = index;
//		 }
//		 index++;
//	 }
//	 return (current);
// }
// int find_first(char **envp)
// {
//	 int index;
//	 int tmp;
//	 int index_two;

//	 index = 0;
//	 tmp = ft_strcmp(envp[0], envp[1]);
//	 if (tmp > 0)
//		 index_two = 1;
//	 else
//		 index_two = 0;
//	 index = 2;
//	 while (envp[index] != NULL)
//	 {
//		 tmp = ft_strcmp(envp[index_two], envp[index]);
//		 if (tmp > 0)
//			 index_two = index;
//		 index++;
//	 }
//	 return (index_two);
// }
// void print_declare(char **envp)
// {
//	 int *order;
//	 int index;
// 	int len;

// 	len =ft_sstrlen(envp);
//	 order = malloc(sizeof(int) * + 1);
//	 order[0] = ft_sstrlen(envp);
//	 index = 2;
//	 order[1] = find_first(envp);
//	 while (index != order[0])
//	 {
//		 order[index] = find_nth(envp, order[index - 1]);
//		 index++;
//	 }
//	 index = 1;
//	 while (index != order[0])
//	 {
//		 printf("declare -x %s\n", envp[order[index]]);
//		 index++;
//	 }
// }
// int builtin_export(char **argv, t_minishell *minish)
// {
//	 int index;

//	 index = 1;
//	 if (argv[1] == NULL)
//		 print_declare(minish->envp);
//	 else
//	 {
//		 while (argv[index] != NULL)
//		 {
//			 if (ft_strchr(argv[index], '=') != NULL)
//				 minish->envp = ft_sstrjoin(minish->envp, argv[index]);
//			 index++;
//		 }
//	 }

//	 return (0);
// }

// int builtin_exit(void)
// {
//	 return (-2);
// }

// int builtin_unset(char **argv, t_minishell *minish)
// {
//	 int where[ft_sstrlen(argv) - 1];
//	 int index;

//	 index = 0;
//	 while (argv[index + 1] != NULL)
//	 {
//		 where[index] = find_string(minish->envp, argv[index + 1]);
//		 index++;
//	 }
//	 minish->envp = remake_env(minish->envp, where, index);
//	 return (0);
// }
// int is_in_where(int *repertoire, int index, int unseteds)
// {
//	 int explore;

//	 explore = 0;
//	 while (explore != unseteds)
//	 {
//		 if (repertoire[explore] == index)
//			 return (0);
//		 explore++;
//	 }
//	 return (-1);
// }

// char **remake_env(char **envpsrc, int *where, int unseteds)
// {
//	 char **envpdst;
//	 int length;
//	 int index;
//	 int index_two;

//	 length = ft_sstrlen(envpsrc) - unseteds;
//	 envpdst = malloc(length + 1 * sizeof(char *));
//	 index = 0;
//	 index_two = 0;
//	 while (envpsrc[index_two] != NULL)
//	 {
//		 if (!is_in_where(where, index_two, unseteds))
//		 {
//			 (envpdst[index] = envpsrc[index_two]);
//			 index++;
//		 }
//		 index_two++;
//	 }
//	 return (envpdst);
// }
