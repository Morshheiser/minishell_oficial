#include "../../include/minishell.h"
char	*ft_expand_variables(char *input, char **args, char **env)
{
	char	*result;
	char	*temp;

	if (!input)
	{
		printf("[DEBUG] Entrada nula\n");
		return (NULL);
	}
	result = NULL;

	// Exibe a entrada inicial
	printf("[DEBUG] Entrada inicial: %s\n", input);

	while (*input)
	{
		if (*input == '$')
		{
			printf("[DEBUG] Encontrado $\n");
			temp = ft_expand_env_variable(&input, args, env);
		}
		else if (*input == '\"')
		{
			printf("[DEBUG] Encontrado aspas duplas \"\n");
			printf("[DEBUG]  %s\n", input);
			temp = ft_expand_double_quotes(&input, args, env);
		}
		else if (*input == '\'')
		{
			printf("[DEBUG] Encontrado aspas simples '\'\n");
			temp = ft_expand_single_quotes(&input);
		}
		else
		{
			printf("[DEBUG] Caracter comum encontrado: %c\n", *input);
			temp = ft_expand_plain_text(&input, "$\'\"");
		}

		// Exibe o valor temporário antes de adicionar à string final
		printf("[DEBUG] Temp antes de adicionar: %s\n", temp);
		result = ft_merge_strings(result, temp);

		if (!result)
		{
			printf("[DEBUG] Falha ao mesclar strings\n");
			return (NULL);
		}

		// Exibe o resultado após mesclar
		printf("[DEBUG] Resultado após mesclar: %s\n", result);
	}

	// Exibe a saída final
	printf("[DEBUG] Saída final: %s\n", result);
	return (result);
}
