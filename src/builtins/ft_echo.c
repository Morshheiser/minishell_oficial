#include "../../include/minishell.h"
// rever essa função
// observação rever novamente
int ft_echo(char **args)
{
    int i;
    int new_line;
    int j;

    i = 1;
    new_line = 1;

    // Verificando se a opção -n está presente
    printf("[DEBUG] Iniciando ft_echo. args[0]: %s\n", args[0]);

    // Verificando o loop para a opção -n
    while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
    {
        printf("[DEBUG] Encontrado '-n' em args[%d]: %s\n", i, args[i]);

        j = 1;
        while (args[i][j] == 'n')
        {
            printf("[DEBUG] Verificando se todos os caracteres são 'n': %c\n", args[i][j]);
            j++;
        }

        // Se encontrar qualquer outro caractere além de 'n', quebra o loop
        if (args[i][j] != '\0')
        {
            printf("[DEBUG] Caracter não é 'n' em args[%d]: %c\n", i, args[i][j]);
            break;
        }

        // Se for apenas 'n', altera a flag new_line
        printf("[DEBUG] Flag new_line alterada para 0 devido ao '-n' encontrado\n");
        new_line = 0;
        i++;
    }

    // Verificando se o argumento não é '-n'
    if (!(args[i] && args[i][0] == '-' && args[i][1] == 'n'))
    {
        printf("[DEBUG] Argumento não é '-n', ajustando new_line para 1\n");
        new_line = 1;
    }

    // Imprimindo os argumentos
    printf("[DEBUG] Imprimindo argumentos:\n");
    while (args[i])
    {
        printf("[DEBUG] Imprimindo argumento args[%d]: %s\n", i, args[i]);
        ft_putstr_fd(args[i], STDOUT_FILENO);

        if (args[++i])
        {
            ft_putstr_fd(" ", STDOUT_FILENO);
            printf("[DEBUG] Imprimindo espaço após argumento\n");
        }
    }

    // Se a flag new_line estiver ativada, imprime uma nova linha no final
    if (new_line)
    {
        printf("[DEBUG] Imprimindo nova linha no final\n");
        ft_putchar_fd('\n', STDOUT_FILENO);
    }

    status_g = 0;
    return 0;
}
