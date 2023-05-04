/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchizhov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:47:17 by vchizhov          #+#    #+#             */
/*   Updated: 2023/04/01 21:55:20 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	handler(int signum, siginfo_t *info, void *ucontext)
{
	static int	bit;
	static int	character;

	(void) ucontext;
	if (signum == SIGUSR1)
	{
		character |= (1 << bit);
	}
	bit++;
	if (bit == 8)
	{
		ft_putchar_fd(character, 1);
		bit = 0;
		character = 0;
		kill(info->si_pid, SIGUSR1);
	}
}

int	main(int ac, char **av)
{
	struct sigaction	act;

	(void) ac;
	(void) av;
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 2);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = handler;
	while (1)
	{
		sigaction(SIGUSR1, &act, NULL);
		sigaction(SIGUSR2, &act, NULL);
		pause();
	}
}
