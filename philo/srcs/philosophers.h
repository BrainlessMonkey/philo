/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adedieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 21:41:05 by adedieu           #+#    #+#             */
/*   Updated: 2022/11/22 21:47:18 by adedieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int						id;
	int						meals;
	size_t					lastmeal;
	pthread_mutex_t			fork;
	pthread_mutex_t			lm;
	pthread_t				thread;
	t_data					*data;
}	t_philo;

typedef struct s_data
{
	int						philo_number;
	size_t					start_time;
	size_t					ttdie;
	size_t					tteat;
	size_t					ttsleep;
	int						repeat;
	int						status;
	pthread_mutex_t			stat;
	pthread_mutex_t			print;
	t_philo					*philos;
}	t_data;

int		ft_atoi(const char *nptr);
int		check_args(int argc, char **argv);
int		init_philos(int nb_philo_number, t_philo *philos, t_data *data);
int		init_data(t_data *data, char **argv);
size_t	checking(t_data *data, int i);
size_t	get_time(void);
void	create_threads(t_data *data);
void	mutex_clean(t_data *data);
void	p_print(char *str, t_philo *philo, int s);
void	p_usleep(size_t ms);
void	*life(void *philo);
#endif
