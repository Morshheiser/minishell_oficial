#include "../../include/minishell.h"

char	*ft_expand_plain_text(char **line, char *eofs)
{
	int	i;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '\\' && (*line)[i + 1] == '$')
			return (ft_expand_plain_dollar(line, eofs));
		i++;
	}
	return (ft_expand_plain_eof(line, eofs));
}

char	*ft_expand_plain_eof(char **line, char *eofs)
{
	int		i;
	char	*result;

	if (!line)
		return (0);
	i = 0;
	while ((*line)[i])
	{
		if (!ft_strchr(eofs, (*line)[i]))
			i++;
		else
			break ;
	}
	result = ft_substr(*line, 0, i);
	*line += i;
	return (result);
}

int	count_escaped_dollar(const char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] == '$')
		{
			count++;
			i += 2;
		}
		else
		{
			i++;
			count++;
		}
	}
	return (count);
}

char	*ft_expand_plain_dollar(char **line, char *eofs)
{
	int i;
	int len;
	char *result;

	if (!line)
		return (NULL);
	i = 0;
	len = 0;
	if (!(result = malloc(count_escaped_dollar(*line) + 1)))
		return (NULL);
	while ((*line)[i])
	{
		if ((*line)[i] == '\\' && (*line)[i + 1] == '$')
		{
			result[len++] = '$';
			i++;
		}
		else
			result[len++] = (*line)[i];
		i++;
	}
	result[len] = '\0';
	*line += i;
	return (result);
}