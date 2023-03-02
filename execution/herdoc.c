#include "../minishell.h"

int	herdoc(char *del)
{
	int p[2];
	pid_t	id;
	char	*hold;

	pipe(p);
	id = fork();
	if (!id)
	{
		close(p[0]);
		while (1)
		{
			hold = readline("> ");
			if (!hold)
				break ;
			if (!ft_strcmp(hold, del))
			{
				free (hold);
				break;
			}
			write (p[1], hold, ft_strlen(hold));
			write(p[1] , "\n", 1);
			free (hold);
		}
		close (p[1]);
		exit (0);
	}
	waitpid(id, 0, 0);
	close (p[1]);
	return (p[0]);
}

int	ft_cmdsize(t_cmd *lst)
{
	int	len;

	if (!lst)
		return (0);
	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}
