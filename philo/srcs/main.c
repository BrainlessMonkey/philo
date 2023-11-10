/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adedieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 21:41:05 by adedieu           #+#    #+#             */
/*   Updated: 2022/11/22 21:47:18 by adedieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

int	ft_atoi(const char *nptr)
{
	int	s;
	int	r;
	int	i;

	s = 1;
	r = 0;
	i = 0;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			s = -s;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		r = (r * 10) + (s * (nptr[i] - 48));
		i++;
	}
	if (nptr[i] != '\0')
		return (-1);
	return (r);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		printf("Invalid number of argument.\n"
			"Usage: ./philo <nb_p> <death_time>"
			" <eating_time> <sleep_time> [nb_meal]\n");
		return (0);
	}
	while (argv[++i])
	{
		if (ft_atoi(argv[i]) < 0)
		{
			printf("Invalid argument, must be only digit\n");
			return (0);
		}
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!check_args(argc, argv))
		return (1);
	if (init_data(&data, argv))
		return (2);
	create_threads(&data);
	mutex_clean(&data);
	free(data.philos);
	return (0);
}
