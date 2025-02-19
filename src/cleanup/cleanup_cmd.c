#include "../../include/minishell.h"

void	ft_clean_cmd(t_cmd **cmd)
{
	t_cmd	*current_cmd;

	if (!cmd || !*cmd)
		return ;
	while (*cmd)
	{
		current_cmd = *cmd;
		*cmd = current_cmd->next;
		ft_clean_fd(&current_cmd->fdin);
		ft_clean_fd(&current_cmd->fdout);
		if (current_cmd->args)
			current_cmd->args = ft_clean_split(current_cmd->args);
		free(current_cmd);
	}
}
