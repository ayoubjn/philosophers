/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   police.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 16:05:39 by ajana             #+#    #+#             */
/*   Updated: 2022/08/07 22:15:48 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_cond(t_args *args, int ind)
{
	int	hunger;

	pthread_mutex_lock(&args->wr_lock);
	hunger = get_time(args->start) - (args->philos_arr[ind]).last_meal;
	pthread_mutex_unlock(&args->wr_lock);
	if (hunger >= args->time_to_die)
		return (0);
	return (1);
}

int	police_man(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->num_of_philos)
	{
		if (!death_cond(args, i))
		{
			print_lock(&(args->philos_arr[i]), RED "died\n" reset);
			pthread_mutex_lock(&args->p_lock);
			mutex_destroy(args);
			return (0);
		}
	}
	return (1);
}
