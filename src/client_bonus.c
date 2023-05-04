/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchizhov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 20:30:10 by vchizhov          #+#    #+#             */
/*   Updated: 2023/04/01 21:55:46 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

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

void	handler(int signum)
{
	(void)signum;
}

int	main(int ac, char **av)
{
	int			pid;
	char		*str;
	int			i;
	static int	bit;

	i = 0;
	str = av[2];
	if (ac != 3)
		ft_putstr_fd("Error!\n", 1);
	else
	{
		pid = ft_atoi(av[1]);
		while (str[i])
		{
			signal(SIGUSR1, handler);
			send_bit(pid, str[i]);
			i++;
			if (SIGUSR1)
				bit++;
		}
	}
	ft_putstr_fd("Counts of bit was sent ", 1);
	ft_putnbr_fd(bit, 1);
	write(1, "\n", 1);
}
