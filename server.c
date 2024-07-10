/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabguerr <gabguerr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:38:49 by gabguerr          #+#    #+#             */
/*   Updated: 2024/06/05 23:05:32 by gabguerr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minitalk.h"

static int	g_x = 0;

void	take_client_pid(int nb, int bol)
{
	static int	result = 0;

	if (nb >= 0)
	{
		result *= 10;
		result += (nb - '0');
	}
	if (bol)
	{
		kill(result, SIGUSR1);
		g_x = 1;
		result = 0;
	}
}

void	signal_handler(int signum)
{
	static int	str1 = 0;
	static int	i = 0;

	if (signum == SIGUSR1)
		str1 = str1 | 1;
	if (++i == 8)
	{
		if (str1 == 27)
			take_client_pid (-1, 1);
		else if (g_x)
			write (1, &str1, 1);
		else if (!g_x)
			take_client_pid(str1, 0);
		if (!str1)
		{
			g_x = 0;
			write(1, "\n", 1);
		}
		str1 = 0;
		i = 0;
	}
	else
		str1 <<= 1;
}

int	main(void)
{
	write(1, "serverPID: ", 12);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1)
		pause ();
	return (0);
}
