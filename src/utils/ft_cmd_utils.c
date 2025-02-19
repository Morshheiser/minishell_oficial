#include "../../include/minishell.h"

t_cmd	*ft_create_new_command(t_fd *in, t_fd *out, char **args)
{
	t_cmd	*arg;

	arg = ft_calloc(sizeof(t_cmd), 1);
	if (arg)
	{
		arg->fdin.ffd = in->ffd;
		arg->fdin.fnm = in->fnm;
		arg->fdout.ffd = out->ffd;
		arg->fdout.fnm = out->fnm;
		arg->args = args;
		arg->next = 0;
	}
	return (ft_check_alloc(arg, "create_new_command"));
}

void	ft_cmd_append(t_cmd **cmd_list, t_cmd *new_cmd)
{
	t_cmd	*last;

	if (!cmd_list || !new_cmd)
		return ;
	new_cmd->next = NULL;
	if (!*cmd_list)
	{
		*cmd_list = new_cmd;
		return ;
	}
	last = *cmd_list;
	while (last->next)
		last = last->next;
	last->next = new_cmd;
}
