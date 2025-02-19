#include "../../include/minishell.h"

#include <stdio.h>

char **ft_split_with_set(char *line, const char *set)
{
    char **split;
    int i = 0;
    int len;
    int num_words;

    if (!line || !set)
    {
        printf("[DEBUG] Erro: linha ou conjunto nulos!\n");
        return (0);
    }

    printf("[DEBUG] Alocando espaço para a divisão...\n");
    split = ft_allocate_split(line, set);
    if (!split)
    {
        printf("[DEBUG] Erro ao alocar espaço para a divisão!\n");
        return NULL;
    }

    // Contando o número de palavras
    printf("[DEBUG] Contando o número de palavras...\n");
    num_words = ft_count_word(line, set);
    printf("[DEBUG] Número de palavras: %d\n", num_words);

    // Loop para dividir a linha
    while (i < num_words)
    {
        // Ignorando delimitadores do conjunto
        printf("[DEBUG] Pulando delimitadores na posição %d\n", i);
        while (ft_strchr(set, *line))
        {
            printf("[DEBUG] Caractere delimitador encontrado: '%c' na posição %ld\n", *line, line - line);
            line++;
        }

        // Calculando o comprimento da palavra
        len = ft_len_word(line, set);
        printf("[DEBUG] Comprimento da palavra na posição %d: %d\n", i, len);

        // Extraindo a palavra
        split[i] = ft_sub_word(line, len);
        if (!split[i])
        {
            printf("[DEBUG] Erro ao alocar ou dividir a palavra!\n");
            return (ft_free_splterr(split));
        }

        printf("[DEBUG] Palavra extraída: '%s'\n", split[i]);

        // Avançando a linha
        line += len;
        i++;
    }

    split[i] = NULL;

    printf("[DEBUG] Divisão concluída com sucesso. Resultado: ");
    for (int j = 0; j < num_words; j++)
    {
        printf("'%s' ", split[j]);
    }
    printf("\n");

    return split;
}

char **ft_allocate_split(char *line, const char *set)
{
    char **split;
    int words;

    if (!line || !set)
        return NULL;
    words = ft_count_word(line, set);
    split = ft_calloc(words + 1, sizeof(char *));
    return split;
}

int ft_count_word(char *line, const char *set)
{
    int words = 0;
    int aux;
    int i = 0;

    if (!line || !set)
        return (0);

    while (line[i])
    {
        if (line[i] && !ft_strchr(set, line[i]))
        {
            words++;
            while (line[i] && !ft_strchr(set, line[i]))
            {
                aux = ft_find_quote_end(&line[i]);
                if (aux)
                    i += aux;
                else
                    i++;
            }
        while (line[i] && ft_strchr(set, line[i]))
            i++;
        }
    }
    return (words);
}

int ft_len_word(char *line, const char *set)
{
    int i;
    int quote_len;

    if (!line || !set)
        return (0);
    i = 0;
    while (line[i] && !ft_strchr(set, line[i]))
    {
        quote_len = ft_find_quote_end(&line[i]);
        if (quote_len) 
            i = i + quote_len;
        else
            i++;
    }
    return (i);
}

char *ft_sub_word(char *line, int len)
{
    char *word;
    char *temp;

    if (!line)
        return (0);
    temp = ft_substr(line, 0, len);
    word = ft_strtrim(temp, " \t\n\v\f\r");
    free(temp);
    return (ft_check_alloc(word, "split"));
}

