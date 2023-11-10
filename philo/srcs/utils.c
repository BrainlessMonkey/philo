/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adedieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 21:41:05 by adedieu           #+#    #+#             */
/*   Updated: 2022/11/22 21:47:18 by adedieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

void	mutex_clean(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&(data->stat));
	pthread_mutex_destroy(&(data->print));
	while (++i < data->philo_number)
	{
		pthread_mutex_destroy(&(data->philos[i].fork));
		pthread_mutex_destroy(&(data->philos[i].lm));
	}
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("gettimeofday error\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	p_usleep(size_t ms)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(50);
}

void	p_print(char *str, t_philo *philo, int s)
{
	static int	i = 1;
	size_t		time;

	pthread_mutex_lock(&(philo->data->print));
	if (i)
	{
		if (!s)
			i = 0;
		time = get_time() - philo->data->start_time;
		printf("%ld %d %s", time, philo->id, str);
	}
	pthread_mutex_unlock(&(philo->data->print));
}

size_t	checking(t_data *data, int i)
{
	size_t	res;

	pthread_mutex_lock(&(data->philos[i].lm));
	res = ((get_time() - data->philos[i].lastmeal) <= data->ttdie);
	pthread_mutex_unlock(&(data->philos[i].lm));
	return (res);
}
