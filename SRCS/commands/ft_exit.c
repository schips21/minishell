#include "../shell_header.h"

/*
Таня, а ты уверена, что exit работает именно так?
у него просто еще и аргументы могут быть
*/

void	ft_exit(t_info *info)
{
	if (info)
		exit(0);
}
