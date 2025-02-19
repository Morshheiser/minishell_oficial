#include "../../include/minishell.h"

int ft_check_lexer(char *line)
{
    if (!line || !*line)
    {
        printf("[DEBUG] Linha vazia ou nula\n");
        return (0);
    }

    printf("[DEBUG] Verificando se as operações estão fechadas\n");
    if (!ft_check_closed_op(line))
    {
        printf("[DEBUG] Erro na verificação de operações fechadas\n");
        return (0);
    }
    
    printf("[DEBUG] Verificando a sintaxe do pipe\n");
    if (!ft_check_pipe_syntax(line))
    {
        printf("[DEBUG] Erro na sintaxe do pipe\n");
        return (0);
    }
    
    printf("[DEBUG] Verificando a sintaxe do redirecionamento (<)\n");
    if (!ft_check_redir_syntax(line, '<'))
    {
        printf("[DEBUG] Erro na sintaxe do redirecionamento '<'\n");
        return (0);
    }

    printf("[DEBUG] Verificando a sintaxe do redirecionamento (>)\n");
    if (!ft_check_redir_syntax(line, '>'))
    {
        printf("[DEBUG] Erro na sintaxe do redirecionamento '>'\n");
        return (0);
    }
    
    return (1);
}


int ft_check_closed_op(char *str)
{
    char quote_type;
    int i;

    i = 0;
    while (str[i])
    {
        printf("[DEBUG] Analisando caractere %c na posição %d\n", str[i], i);
        
        if ((str[i] == '\'') || (str[i] == '\"'))
        {
            quote_type = str[i];
            printf("[DEBUG] Encontrada aspa: %c\n", quote_type);
            i++;
            while (str[i] && (str[i] != quote_type))
            {
                printf("[DEBUG] Dentro das aspas: %c\n", str[i]);
                i++;
            }
            if (!str[i])
            {
                printf("[DEBUG] Erro: Aspas não fechadas corretamente\n");
                return (ft_lex_error(str[i], 1));
            }
        }
        i++;
    }
    return (1);
}


int ft_check_pipe_syntax(char *str)
{
    int first_cmd;
    int i;

    first_cmd = 0;
    i = 0;
    while (str[i])
    {
        printf("[DEBUG] Analisando caractere %c na posição %d\n", str[i], i);
        i += ft_find_quote_end(&str[i]);
        if (!str[i])
        {
            printf("[DEBUG] Erro: Pipe no final da string\n");
            return (ft_lex_error(str[i], 2));
        }
        if (!first_cmd && (!ft_isspace(str[i]) && (str[i] != '|')))
        {
            first_cmd = 1;
        }
        if (str[i] == '|')
        {
            printf("[DEBUG] Encontrado pipe na posição %d\n", i);
            if (!first_cmd)
            {
                printf("[DEBUG] Erro: Pipe não é precedido por um comando\n");
                return (ft_lex_error(str[i], 3));
            }
            first_cmd = 0;
        }
        i++;
    }
    if (!first_cmd)
    {
        printf("[DEBUG] Erro: Pipe no final da string sem comando\n");
        return (ft_lex_error(str[i], 4));
    }
    return (first_cmd);
}


int ft_check_redir_syntax(char *str, char opt)
{
    int redir;
    int i;
    int num;

    num = ft_strlen(str);
    i = 0;
    while (str[i] && i < num)
    {
        redir = 0;
        printf("[DEBUG] Analisando caractere %c na posição %d\n", str[i], i);
        
        if (str[i] == '\'' || str[i] == '\"')
        {
            i += ft_find_quote_end(&str[i]) + 1;
        }
        else if (str[i] == opt)
        {
            while ((str[i + redir] == opt) && (redir < 4) && (i + redir < num))
                redir++;
            
            printf("[DEBUG] Encontrado redirecionamento %c com %d caracteres consecutivos\n", opt, redir);
            
            if (redir > 2)
            {
                printf("[DEBUG] Erro: Redirecionamento com mais de dois sinais consecutivos\n");
                return (ft_lex_error(str[i], 5));
            }
            
            i += redir;
            while (ft_isspace(str[i]))
                i++;
            
            if (str[i] == '\0' || str[i] == '|' || str[i] == '>' || str[i] == '<')
            {
                printf("[DEBUG] Erro: Esperado um argumento após o redirecionamento\n");
                return (ft_lex_error(str[i], 6));
            }
        }
        i++;
    }
    return (1);
}


int ft_lex_error(char c, int n)
{

    if (!c)
        status_g = ft_perror(2, "lexer", "erro de sintaxe: token inesperado 'newline' encontrado");
    else if (c == '|')
        status_g = ft_perror(2, "lexer", "erro de sintaxe: uso incorreto do operador pipe '|'");
    else if (c == '<' || c == '>')
        status_g = ft_perror(2, "lexer", "erro de sintaxe: redirecionamento inválido '%c'", c);
    else if (ft_isspace(c))
        status_g = ft_perror(2, "lexer", "erro de sintaxe: espaço extra não esperado antes do token");
    else
        status_g = ft_perror(2, "lexer", "erro de sintaxe: operador inválido '%c' encontrado", c);
    return (0);
}
