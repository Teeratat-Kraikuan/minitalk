/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkraikua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 22:23:59 by tkraikua          #+#    #+#             */
/*   Updated: 2022/04/22 22:23:59 by tkraikua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

t_message	g_mes;

int	ft_atoi(const char *str)
{
	size_t	i;
	int		res;

	i = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (0);
	return (res);
}

void	check_arg(int argc, char **argv)
{
	if (argc != 3)
	{
		write(1, "Invalid arguments.\n", 19);
		exit(1);
	}
	if (ft_atoi(argv[1]) <= 0)
	{
		write(1, "Invalid PID.\n", 13);
		exit(1);
	}
}

void	received(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)info;
	(void)ucontext;
	write(1, "message sent.\n", 14);
	exit(0);
}

void	send_message(int sig, siginfo_t *info, void *ucontext)
{
	int	bit;

	(void)sig;
	(void)ucontext;
	if (g_mes.b_cnt == 7)
	{
		g_mes.message++;
		g_mes.b_cnt = 0;
	}
	else
		g_mes.b_cnt++;
	bit = ((*g_mes.message) >> g_mes.b_cnt) % 2;
	usleep(50);
	if (bit)
		kill(info->si_pid, SIGUSR2);
	else
		kill(info->si_pid, SIGUSR1);
}

int	main(int argc, char **argv)
{
	struct sigaction	send;
	struct sigaction	end;
	int					bit;

	check_arg(argc, argv);
	send.sa_sigaction = &send_message;
	send.sa_flags = SA_SIGINFO;
	sigemptyset(&send.sa_mask);
	sigaction(SIGUSR1, &send, NULL);
	end.sa_sigaction = &received;
	end.sa_flags = SA_SIGINFO;
	sigemptyset(&end.sa_mask);
	sigaction(SIGUSR2, &end, NULL);
	g_mes.message = argv[2];
	g_mes.b_cnt = 0;
	bit = ((*g_mes.message) >> g_mes.b_cnt) % 2;
	if (bit)
		if (kill(ft_atoi(argv[1]), SIGUSR2) == -1)
			return (2);
	if (!bit)
		if (kill(ft_atoi(argv[1]), SIGUSR1) == -1)
			return (2);
	while (1)
		pause();
	return (0);
}
