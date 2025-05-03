#include "./inc/minishell.h"

int main(int ac, char **av)
{
    int i = 0;
    printf("ac : %d\n", ac);
    while(av[i])
    {
        printf("av[%d] : %s\n", i, av[i]);
        i++;
    }
}