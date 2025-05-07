#include "inc/minishell.h"
#include "Libft/inc/libft.h"

int main(int ac, char **av)
{
    // int i = 0;
    // printf("ac : %d\n", ac);
    // while(av[i])
    // {
    //     printf("av[%d] : %s\n", i, av[i]);
    //     i++;
    // }
    char *str = "ee'ePar' exem'ple 'oui ";
    char *str2 = ft_delchar(str, '\'');
    printf("after del : %s\n", str2);
}