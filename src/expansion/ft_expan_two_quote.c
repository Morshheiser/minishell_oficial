#include "../../include/minishell.h"

char	*ft_expand_double_quotes(char **input, char **argv, char **env)
{
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = NULL;
	if (!ft_check_double_quote_syntax(*input))
		return (NULL);
	*input += 1;
	while (*(*input) && (*(*input) != '\"'))
	{
		if (*(*input) == '$')
			tmp = ft_expand_env_variable(input, argv, env);
		else
			tmp = ft_expand_plain_text(input, "$\"");
		str = ft_merge_strings(str, tmp);
		(*input)++;
	}
	if (*(*input))
		*input += 1;
	if (!str || !*str)
	{
		free(str);
		str = ft_calloc(1, 1);
		if (!str)
			return (NULL);
	}
	return (str);
}

int	ft_check_double_quote_syntax(char *str)
{
	int	i;
	int	quote_count;

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
		return (0);
	}
	return (1);
}
