/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:30:39 by ajana             #+#    #+#             */
/*   Updated: 2022/08/02 18:56:39 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_argv(char **av, t_args *args)
{
	args->num_of_philos = atoi(av[1]);
	args->time_to_die = atoi(av[2]);
	args->time_to_eat = atoi(av[3]);
	args->time_to_sleep = atoi(av[4]);
	if (av[5])
		args->num_of_meals = atoi(av[5]);
	else
		args->num_of_meals = -1;
}

void	create_threads(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->num_of_philos)
	{
		pthread_create(&((args->philos_arr[i]).thread), NULL, routine, &(args->philos_arr[i]));
		usleep(100);
	}
	i = -1;
	while (++i < args->num_of_philos)
		pthread_detach((args->philos_arr[i]).thread);
}

void	*philos_init(t_args *args)
{
	int		i;
	t_philo	*philosopher;

	i = 0;
	gettimeofday(&(args->start), NULL);
	pthread_mutex_init(&(args->p_lock), NULL);
	pthread_mutex_init(&(args->wr_lock), NULL);
	while (i < args->num_of_philos)
	{
		philosopher = &(args->philos_arr[i]);
		pthread_mutex_init(&(philosopher->fork), NULL);
		philosopher->id = i + 1;
		philosopher->meals = args->num_of_meals;
		philosopher->args = args;
		i++;
	}
	create_threads(args);
	return (NULL);
}
