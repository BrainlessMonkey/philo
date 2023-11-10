/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alive.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adedieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 21:41:05 by adedieu           #+#    #+#             */
/*   Updated: 2022/11/22 21:47:18 by adedieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

int	status_check(t_philo *philo)
{
	if (philo->data->repeat != -1 && philo->meals == philo->data->repeat)
	{
		pthread_mutex_lock(&(philo->data->stat));
		philo->data->status = 0;
		pthread_mutex_unlock(&(philo->data->stat));
	}
	pthread_mutex_lock(&(philo->data->stat));
	if (!philo->data->status)
	{
		pthread_mutex_unlock(&(philo->data->stat));
		return (0);
	}
	pthread_mutex_unlock(&(philo->data->stat));
	return (1);
}

void	p_sleep(t_philo	*philo)
{
	p_print("is sleeping\n", philo, 1);
	p_usleep(philo->data->ttsleep);
}

void	p_think(t_philo *philo)
{
	p_print("is thinking\n", philo, 1);
}

void	p_eat(t_philo *philo)
{
	if (philo->data->philo_number == 1)
	{
		p_print("has taken a fork\n", philo, 1);
		pthread_mutex_lock(&(philo->data->stat));
		philo->data->status = 0;
		p_print("died\n", philo, 0);
		pthread_mutex_unlock(&(philo->data->stat));
		return ;
	}
	pthread_mutex_lock(&(philo->data->philos[philo->id - 1].fork));
	p_print("has taken a fork\n", philo, 1);
	pthread_mutex_lock(&(philo->data->philos[philo->id
			% philo->data->philo_number].fork));
	p_print("has taken a fork\n", philo, 1);
	philo->meals++;
	p_print("is eating\n", philo, 1);
	pthread_mutex_lock(&(philo->lm));
	philo->lastmeal = get_time();
	pthread_mutex_unlock(&(philo->lm));
	p_usleep(philo->data->tteat);
	pthread_mutex_unlock(&(philo->data->philos[philo->id - 1].fork));
	pthread_mutex_unlock(&(philo->data->philos[philo->id
			% philo->data->philo_number].fork));
}

void	*life(void *philo)
{
	pthread_mutex_lock(&(((t_philo *)philo)->lm));
	((t_philo *)philo)->lastmeal = get_time();
	pthread_mutex_unlock(&(((t_philo *)philo)->lm));
	if (((t_philo *)philo)->id % 2 == 0)
		p_usleep(1);
	while (status_check((t_philo *)philo))
	{
		p_eat((t_philo *)philo);
		p_sleep((t_philo *)philo);
		p_think((t_philo *)philo);
	}
	return (philo);
}
