#include "../../include/minishell.h"

int ft_configure_redirections(char *input, t_fd *fd, t_shell *shell)
{
    int j;
    char symbol;
    int i;

    i = 0;
    printf("[DEBUG] Iniciando ft_configure_redirections\n");
    while (input[i])
    {
        j = 0;
        i += ft_find_quote_end(&input[i]);
        if (input[i] && (input[i] == '<') || (input[i] == '>'))
        {
            symbol = input[i];
            printf("[DEBUG] Encontrado redirecionamento: %c\n", symbol);
            while (input[i + j] && input[i + j] == symbol)
                j++;
            i = i + j;
            if (symbol == '<')
            {
                printf("[DEBUG] Chamando ft_input_redirection\n");
                if (ft_input_redirection(&input[i], fd, j, shell) < 0)
                    return (-1);
            }
            if (symbol == '>')
            {
                printf("[DEBUG] Chamando ft_output_redirection\n");
                if (ft_output_redirection(&input[i], fd, j, shell) < 0)
                    return (-1);
            }
        }
        else if (input[i])
            i++;
    }
    printf("[DEBUG] ft_configure_redirections concluído\n");
    return (0);
}

int ft_input_redirection(char *filename, t_fd *fd, int operator, t_shell *shell)
{
    t_fd temp_fd;

    printf("[DEBUG] Iniciando ft_input_redirection\n");
    if ((fd[IN].ffd == -1) || (fd[OUT].ffd == -1))
    {
        if (operator == 2)
        {
            printf("[DEBUG] Redirecionamento de entrada com heredoc\n");
            temp_fd.fnm = ft_set_filename(filename, shell);
            if (!temp_fd.fnm)
            {
                printf("[DEBUG] Erro ao configurar o nome do arquivo\n");
                return (-1);
            }
            temp_fd.ffd = ft_heredoc(temp_fd.fnm);
            ft_clean_fd(&temp_fd);
        }
        return (0);
    }
    
    ft_clean_fd(&fd[IN]);
    fd[IN].fnm = ft_set_filename(filename, shell);
    if (!fd[IN].fnm)
    {
        printf("[DEBUG] Erro ao configurar o nome do arquivo de entrada\n");
        return (-1);
    }
    if (operator == 1)
    {
        printf("[DEBUG] Abrindo arquivo de entrada com O_RDONLY\n");
        fd[IN].ffd = open(fd[IN].fnm, O_RDONLY, 00644);
    }
    else if (operator == 2)
    {
        printf("[DEBUG] Abrindo arquivo de entrada com heredoc\n");
        fd[IN].ffd = ft_heredoc(fd[IN].fnm);
    }
    return (0);
}

int ft_output_redirection(char *filename, t_fd *fd, int operator, t_shell *shell)
{
    printf("[DEBUG] Iniciando ft_output_redirection\n");
    if ((fd[IN].ffd != -1) && (fd[OUT].ffd != -1))
    {
        printf("[DEBUG] Limpando fd de saída e configurando arquivo\n");
        ft_clean_fd(&fd[OUT]);
        fd[OUT].fnm = ft_set_filename(filename, shell);
        if (!fd[OUT].fnm)
        {
            printf("[DEBUG] Erro ao configurar o nome do arquivo de saída\n");
            return (-1);
        }
        if (operator == 1)
        {
            printf("[DEBUG] Abrindo arquivo de saída com O_TRUNC\n");
            fd[OUT].ffd = open(fd[OUT].fnm, O_WRONLY | O_CREAT | O_TRUNC, 00644);
        }
        else if (operator == 2)
        {
            printf("[DEBUG] Abrindo arquivo de saída com O_APPEND\n");
            fd[OUT].ffd = open(fd[OUT].fnm, O_WRONLY | O_CREAT | O_APPEND, 00644);
        }
    }
    return (0);
}

char *ft_set_filename(char *input, t_shell *shell)
{
    char    *temp;
    char    *filename;
    char    quote_type;
    int     i;

    printf("[DEBUG] Iniciando ft_set_filename\n");
    i = 0;
    while (ft_isspace(*input))
        input++;
    if ((input[i] == '\'') || (input[i] == '\"'))
    {
        quote_type = input[i];
        i++;
        while (input[i] != quote_type)
            i++;
        i++;
    }
    else
        while (input[i] && !ft_strchr("<>| \t\n\v\r\f", input[i]))
            i++;
    temp = ft_substr(input, 0, i);
    printf("[DEBUG] Nome do arquivo temporário: %s\n", temp);
    
    filename = ft_expand_variables(temp, shell->argv, shell->env->var_list);
    free(temp);
    
    printf("[DEBUG] Nome do arquivo expandido: %s\n", filename);
    
    return (ft_check_alloc(filename, "set_filename"));
}
