/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   police.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 16:05:39 by ajana             #+#    #+#             */
/*   Updated: 2022/08/02 21:59:15 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_cond(t_args *args)
{
	int	i = 0;
	int	hunger = 0;
	t_philo	*philosopher;

	while (i < args->num_of_philos)
	{
		philosopher = &(args->philos_arr[i]);
		if (pthread_mutex_lock(&(args->wr_lock)))
			return (-1);
		hunger = get_time(args->start) - philosopher->last_meal;
		if ((hunger >= args->time_to_die) && (!(philosopher->is_eating)))
			return (i);
		if (pthread_mutex_unlock(&(args->wr_lock)))
			return (-1);
		i++;
	}
	return (-1);
}

void	*police_man(t_args *args)
{
	int	i;

	i = -1;
	while (i == -1)
		i = death_cond(args);
	print_lock(&(args->philos_arr[i]), RED "died\n" reset);
	pthread_mutex_lock(&(args->p_lock));
	mutex_destroy(args);
	return (NULL);
}
