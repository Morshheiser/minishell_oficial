#include "../../include/minishell.h"

char	**ft_arr_copy(char **arr, int size)
{
	int		i;
	int		len;
	char	**arr_cpy;

	if (!arr)
		return (NULL);
	i = 0;
	len = 0;
	while (arr[len])
		len++;
	arr_cpy = malloc(sizeof(char *) * (len + 1 + size));
	ft_memset(arr_cpy, 0, sizeof(char *) * (len + 1 + size));
	if (!arr_cpy)
		return (NULL);
	while (i < len && arr[i])
	{
		arr_cpy[i] = ft_strdup(arr[i]);
		i++;
	}
	while (i < len + size)
	{
		arr_cpy[i] = NULL;
		i++;
	}
	return (arr_cpy);
}

void	ft_free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	ft_free_env(t_env *env)
{
	int	i;

	i = 0;
	if (!env || !env->var_list)
		return ;
	while (env->var_list[i])
	{
		free(env->var_list[i]);
		i++;
	}
	if (env->var_list)
		free(env->var_list);
	if (env->pwd)
		free(env->pwd);
}
