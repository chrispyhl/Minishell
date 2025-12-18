

#include "../../includes/minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		// TODO: implement gc
		free(array[i]);
		i++;
	}
	// TODO: implement gc
	free(array);
}
