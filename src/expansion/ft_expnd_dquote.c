#include "../../include/minishell.h"

#include <stdio.h> // Para printf
#include <stdlib.h> // Para malloc/free

char *ft_expand_double_quotes(char **input, char **argv, char **env)
{    
    char *str = NULL;
    char *tmp = NULL;

    printf("Inicializando ft_expand_double_quotes\n");
    printf("input: %s\n", *input);

    // Verifica a sintaxe de aspas duplas
    if (!ft_check_double_quote_syntax(*input)) {
        printf("Sintaxe de aspas duplas inválida\n");
        return NULL;
    }

    *input += 1; // Avança o ponteiro para depois da aspa de abertura
    printf("Avançou o ponteiro, novo input: %s\n", *input);

    // Loop para processar o conteúdo dentro das aspas
    while (*(*input) && (*(*input) != '\"')) {
        printf("Processando caractere: %c\n", **input);

        if (*(*input) == '$') {
            printf("Encontrado $ - Expansão de variável de ambiente\n");
            tmp = ft_expand_env_variable(input, argv, env);
        } else {
            printf("Texto comum detectado, expandindo: %c\n", **input);
            tmp = ft_expand_plain_text(input, "$\"");
        }

        printf("tmp após expansão: %s\n", tmp);

        str = ft_merge_strings(str, tmp); // Mescla o conteúdo de tmp em str
        printf("str após mesclar: %s\n", str);

        // Avança o ponteiro de input
        (*input)++;
    }

    // Se encontrou a aspa de fechamento, avança o ponteiro
    if (*(*input)) {
        *input += 1;
        printf("Fechamento da aspa encontrado, avançando ponteiro: %s\n", *input);
    }

    // Se str estiver vazio ou NULL, aloca memória para uma string vazia
    if (!str || !*str) {
        printf("String vazia ou NULL, alocando memória para string vazia\n");
        free(str);
        str = ft_calloc(1, 1); // Aloca memória para uma string vazia
        if (!str) {
            printf("Erro ao alocar memória\n");
            return NULL;
        }
    }

    printf("Resultado final de str: %s\n", str);
    return str;
}

//ok
int ft_check_double_quote_syntax(char *str)
{
    int i;
    int quote_count;

    i = 0;
    quote_count = 0;
    while (str[i])
    {
        if (str[i] == '\"')
            quote_count++;
        i++;
    }
    if (quote_count % 2 != 0)
    {
        ft_perror(0, "syntax_error", "aspas duplas desbalanceadas.");
        return 0;
    }
    return 1;
}
