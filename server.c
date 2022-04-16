/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkraikua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 21:10:08 by tkraikua          #+#    #+#             */
/*   Updated: 2022/04/14 21:10:08 by tkraikua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minitalk.h"

void	ft_putnbr(int n)
{
	if (n > 9)
		ft_putnbr(n / 10);
	write(1, &"0123456789"[n % 10], 1);
}

void	handler(int sig)
{
	int			bit;
	static char	letter;
	static int	count;
	
	if (sig == SIGUSR1)
		bit = 0;
	else if (sig == SIGUSR2)
		bit = 1;
	letter = letter * 2 | bit;
	count++;
	if (count == 8)
	{
		if (letter)
			write(1, &letter, 1);
		else
			write(1, "\n", 1);
		count = 0;
		letter = 0;
	}
}

int	main () {
	struct sigaction action;
	
	write(1, "Server PID: ", 12);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	action.sa_handler= &handler;
	action.sa_flags = 0;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while(1)
		pause(); 
	return(0);
}
