#include "inc/minishell.h"
#include "Libft/inc/libft.h"

int main(int ac, char **av)
{
    int i = 0;
    printf("ac : %d\n", ac);
    while(av[i])
    {
        printf("av[%d] : %s\n", i, av[i]);
        i++;
    }
    // printf("after del : %s\n", str2);
    // char *str = "|Bonjour";
    // char *str2 = "|";
    // i = ft_strncmp(str2, str, ft_strlen(str));
    // printf("res : %d\n", i);
}