/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkraikua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 13:56:19 by tkraikua          #+#    #+#             */
/*   Updated: 2022/04/18 13:56:19 by tkraikua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putnbr(int n)
{
	if (n > 9)
		ft_putnbr(n / 10);
	write(1, &"0123456789"[n % 10], 1);
}

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static char	letter = 0;
	static int	b_cnt = 0;

	(void)ucontext;
	if (sig == SIGUSR2)
		letter += (1 << b_cnt);
	b_cnt++;
	if (b_cnt == 8)
	{
		b_cnt = 0;
		if (letter)
			write(1, &letter, 1);
		else
		{
			letter = 0;
			write(1, "\n", 1);
			kill(info->si_pid, SIGUSR2);
			return ;
		}
		letter = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	write(1, "Server PID: ", 12);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
