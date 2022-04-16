/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkraikua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 21:46:07 by tkraikua          #+#    #+#             */
/*   Updated: 2022/04/15 21:46:07 by tkraikua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
	return (res);
}

void	send_message(int server_pid, int letter)
{
		int	bit;
		int	i;

		i = 7;
		while (i >= 0)
		{
			bit = (letter >> i) % 2;
			if (bit)
				kill(server_pid, SIGUSR2);
			else
				kill(server_pid, SIGUSR1);
			usleep(50);
			i--;
		}
}

int	main(int argc, char **argv)
{
	int		server_pid;
	char	*message;

	if (argc != 3)
	{
		write(1, "Invalid arguments.\n", 19);
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		write(1, "Invalid PID.\n", 13);
		return (1);
	}
	message = argv[2];
	while (*message)
	{
		send_message(server_pid, *message);
		message++;
	}
	send_message(server_pid, 0);
	return (0);
}
