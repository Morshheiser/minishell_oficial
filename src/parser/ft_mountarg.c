#include "../../include/minishell.h"

//ok
t_cmd *ft_init_and_process_command(char *input, t_shell *shell)
{
    t_cmd  *cmd;
    t_fd    in_out[2];
    char    **args;

    printf("Iniciando ft_init_and_process_command\n");

    in_out[IN].fnm = 0;
    in_out[IN].ffd = -2;
    in_out[OUT].fnm = 0;
    in_out[OUT].ffd = -2;
    args = 0;
    
    printf("Chamada de ft_configure_redirections\n");
    if (ft_configure_redirections(input, in_out, shell) < 0)
    {
        printf("Erro ao configurar redirecionamentos\n");
        return (ft_command_error(&in_out[IN], &in_out[OUT], args));
    }

    printf("Chamada de ft_clean_redirection_tokens\n");
    ft_clean_redirection_tokens(input);

    printf("Chamada de ft_extract_command_arguments\n");
    args = ft_extract_command_arguments(input, shell);
    if (!args)
    {
        printf("Erro ao extrair argumentos do comando\n");
        return (ft_command_error(&in_out[IN], &in_out[OUT], args));
    }

    printf("Chamada de ft_create_new_command\n");
    cmd = ft_create_new_command(&in_out[IN], &in_out[OUT], args);
    if (!cmd)
    {
        printf("Erro ao criar novo comando\n");
        cmd = ft_command_error(&in_out[IN], &in_out[OUT], args);
    }
    printf("Comando criado: %p\n", cmd);
    return (cmd);
}

t_cmd *ft_command_error(t_fd *in, t_fd *out, char **split)
{
    printf("ft_command_error: Cleaning up split and file descriptors\n");
    split = ft_clean_split(split);
    ft_clean_fd(in);
    ft_clean_fd(out);
    return (0);
}

void ft_handle_redirection(char *str)
{
    int i = 0;
    
    printf("Iniciando ft_handle_redirection com str: %s\n", str);

    while (str[i] == '<' || str[i] == '>')
        i++;
    
    while (ft_isspace(str[i]))
        i++;
    
    if (str[i] == '\'' || str[i] == '"')
    {
        printf("Encontrou aspas: %c\n", str[i]);
        i += ft_find_quote_end(str + i) + 1;
    }
    else
    {
        while (str[i] && !ft_strchr("<>| \t\n\v\r\f", str[i]))
            i++;
    }

    printf("Alterando a string para espaços\n");
    ft_memset(str, ' ', i);
}

void ft_clean_redirection_tokens(char *str)
{
    printf("Iniciando ft_clean_redirection_tokens com str: %s\n", str);

    while (*str)
    {
        printf("Passando para a próxima parte da string\n");
        str += ft_find_quote_end(str);
        if (*str == '<' || *str == '>')
        {
            printf("Redirecionamento encontrado: %c\n", *str);
            ft_handle_redirection(str);
        }
        else if (*str >= 9 && *str <= 13)
        {
            printf("Caractere especial encontrado, substituindo por espaço\n");
            *str = ' ';
        }
        str++;
    }
}

int ft_process_argument(char **args, int index, t_shell *shell)
{
    char *expanded;
    int j;

    printf("Iniciando ft_process_argument para o argumento: %s\n", args[index]);

    expanded = ft_expand_variables(args[index], shell->argv, shell->env->var_list);
    free(args[index]);

    if (!expanded)
    {
        printf("Erro ao expandir variáveis, removendo argumento\n");
        j = index;
        while (args[j])
        {
            args[j] = args[j + 1];
            j++;
        }

        return (0);
    }

    args[index] = expanded;
    printf("Argumento expandido: %s\n", args[index]);

    return (1);
}

char **ft_extract_command_arguments(char *line, t_shell *shell)
{
    char **args;
    int i;

    printf("Iniciando ft_extract_command_arguments com linha: %s\n", line);

    args = ft_split_with_set(line, " \t\n\v\f\r");

    if (!args)
    {
        printf("Erro ao dividir a linha em argumentos\n");
        return (NULL);
    }

    i = 0;
    while (args[i])
    {
        printf("Processando argumento: %s\n", args[i]);
        if (!ft_process_argument(args, i, shell))
        {
            printf("Argumento removido: %s\n", args[i]);
            continue;
        }

        i++;
    }

    return (args);
}
