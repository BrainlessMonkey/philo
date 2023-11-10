/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adedieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 21:41:05 by adedieu           #+#    #+#             */
/*   Updated: 2022/11/22 21:47:18 by adedieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

int	init_philos(int nb_philo, t_philo *philos, t_data *data)
{
	int	i;

	i = -1;
	while (++i < nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].meals = 0;
		philos[i].lastmeal = data->start_time;
		pthread_mutex_init(&(philos[i].fork), NULL);
		pthread_mutex_init(&(philos[i].lm), NULL);
		philos[i].data = data;
	}
	return (0);
}

int	init_data(t_data *data, char **argv)
{
	data->philo_number = ft_atoi(argv[1]);
	data->start_time = get_time();
	data->ttdie = ft_atoi(argv[2]);
	data->tteat = ft_atoi(argv[3]);
	data->ttsleep = ft_atoi(argv[4]);
	if (argv[5])
		data->repeat = ft_atoi(argv[5]);
	else
		data->repeat = -1;
	data->status = 1;
	pthread_mutex_init(&(data->stat), NULL);
	pthread_mutex_init(&(data->print), NULL);
	data->philos = malloc(sizeof(t_philo) * data->philo_number);
	if (!data->philos)
	{
		printf("Malloc error\n");
		return (1);
	}
	if (init_philos(data->philo_number, data->philos, data))
	{
		free(data->philos);
		printf("Mutex error\n");
		return (2);
	}
	return (0);
}

void	create_threads(t_data	*data)
{
	int	i;

	i = -1;
	while (++i < data->philo_number)
		pthread_create(&(data->philos[i].thread),
			NULL, &life, &(data->philos[i]));
	i = -1;
	while (checking(data, ++i))
	{
		if (i == data->philo_number - 1)
			i = -1;
		usleep(100);
	}
	pthread_mutex_lock(&(data->stat));
	if (data->status)
	{
		data->status = 0;
		p_print("died\n", &(data->philos[i]), 0);
	}
	pthread_mutex_unlock(&(data->stat));
	i = -1;
	while (++i < data->philo_number)
		pthread_join(data->philos[i].thread, NULL);
}
