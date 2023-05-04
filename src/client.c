/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchizhov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 20:22:21 by vchizhov          #+#    #+#             */
/*   Updated: 2023/04/01 21:44:38 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_bit(int pid, int c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((c & (1 << i)) == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(1000);
		i++;
	}
}

int	main(int ac, char **av)
{
	int		pid;
	char	*str;
	int		i;

	i = 0;
	str = av[2];
	if (ac != 3)
		ft_putstr_fd("Error!\n", 1);
	else
	{
		pid = ft_atoi(av[1]);
		while (str[i])
		{
			send_bit(pid, str[i]);
			i++;
		}
	}
}
