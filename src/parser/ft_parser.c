#include "../../include/minishell.h"
//ok
#include <stdio.h>

void parse_input(char *line, t_shell *shell)
{
    char **args;
    t_cmd *no;
    int i;

    // Verificando se a linha é válida
    if (!line || !*line)
    {
        printf("[DEBUG] Linha vazia ou nula recebida, retornando...\n");
        return ;
    }

    // Dividindo a linha por "|"
    printf("[DEBUG] Dividindo a linha: %s\n", line);
    args = ft_split_with_set(line, "|");
    if (!args)
    {
        printf("[DEBUG] Erro ao dividir a linha, retornando...\n");
        return;
    }

    // Iterando pelos argumentos divididos
    i = 0;
    while (args[i])
    {
        printf("[DEBUG] Processando argumento: %s\n", args[i]);

        // Inicializando e processando o comando
        no = ft_init_and_process_command(args[i], shell);
        if (!no)
        {
            printf("[DEBUG] Erro ao inicializar e processar comando, limpando e quebrando...\n");
            ft_clean_cmd(&shell->cmd);
            break;
        }

        // Adicionando o comando à lista de comandos
        printf("[DEBUG] Comando processado com sucesso, adicionando à lista...\n");
        ft_cmd_append(&shell->cmd, no);
        i++;
    }

    // Limpando a memória dos argumentos divididos
    printf("[DEBUG] Limpando os argumentos divididos...\n");
    args = ft_clean_split(args);
    printf("[DEBUG] Fim da função parse_input\n");
}
