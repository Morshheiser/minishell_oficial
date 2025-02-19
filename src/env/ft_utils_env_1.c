#include "../../include/minishell.h"

int	ft_size(char **arr)
{
	int	len;

	len = 0;
	if (!arr)
		return (len);
	while (arr[len])
		len++;
	return (len);
}

int	ft_vetor_size(char **ev)
{
	int	i;

	i = 0;
	while (ev[i])
		i++;
	return (i);
}

int	ft_size_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			i++;
	}
	return (i);
}

int	ft_srch_arr(char **array, char *str)
{
	int	i;
	int	len;

	if (!array || !str)
		return (-1);
	len = ft_strlen(str);
	i = 0;
	while (array[i])
	{
		if (!ft_strncmp(array[i], str, len) && array[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

long long int	ft_atolli(const char *str)
{
	long long int	result;
	int				sign;
	int				i;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		result *= 10;
		result += sign * (str[i] - '0');
		i++;
	}
	return (result);
}
