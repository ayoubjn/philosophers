/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:30:39 by ajana             #+#    #+#             */
/*   Updated: 2022/08/29 10:43:04 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_args *args, t_philo *philos_arr)
{
	int	i;

	i = -1;
	gettimeofday(&(args->start), NULL);
	while (++i < args->num_of_philos)
	{
		pthread_create(&(philos_arr[i].thread), NULL, routine, &philos_arr[i]);
		pthread_detach((args->philos_arr[i]).thread);
		usleep(10);
	}
}

void	*philos_init(t_args *args)
{
	int		i;
	t_philo	*philosopher;

	i = 0;
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
	create_threads(args, args->philos_arr);
	return (NULL);
}
