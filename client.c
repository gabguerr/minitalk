/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabguerr <gabguerr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:38:46 by gabguerr          #+#    #+#             */
/*   Updated: 2024/06/05 23:06:13 by gabguerr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minitalk.h"

void	send_binary_signal(char *binary, int sp_id)
{
	int	i;

	i = 0;
	while (binary[i])
	{
		if (binary[i] == '0')
			kill(sp_id, SIGUSR2);
		else if (binary[i] == '1')
			kill(sp_id, SIGUSR1);
		usleep(5000);
		i++;
	}
}

void	send_client_pid(int server_pid)
{
	char	*cpid;
	int		i;
	char	*c_binary;
	int		x;

	i = 0;
	cpid = itoa_pid(getpid());
	while (cpid[i])
	{
		c_binary = convertbinary(cpid[i]);
		x = 0;
		while (c_binary[x])
		{
			if (c_binary[x] == '0')
				kill(server_pid, SIGUSR2);
			else if (c_binary[x] == '1')
				kill(server_pid, SIGUSR1);
			usleep(1000);
			x++;
		}
		free(c_binary);
		i++;
	}
	free(cpid);
}

void	message(int signum)
{
	if (signum == SIGUSR1)
		write(1, "SUCCESS!\n", 10);
}

int	main(int argc, char **argv)
{
	int		i;
	int		len;
	char	*binary;

	i = 0;
	signal(SIGUSR1, message);
	if (argc == 3)
	{
		send_client_pid(ft_atoi(argv[1]));
		len = ft_strlen(argv[2]);
		while (len >= i)
		{
			binary = convertbinary(argv[2][i]);
			send_binary_signal(binary, ft_atoi(argv[1]));
			free(binary);
			i++;
		}
	}
	else
		write(1, "ERROR", 6);
	return (0);
}
