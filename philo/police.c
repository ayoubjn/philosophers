/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   police.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 16:05:39 by ajana             #+#    #+#             */
/*   Updated: 2022/08/16 02:06:18 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_cond(t_args *args, t_philo *philo)
{
	int	hunger;
	int	eating;

	hunger = get_time(args->start) - read_lock(philo->last_meal, &args->wr_lock);
	eating = read_lock(philo->is_eating, &args->wr_lock);
	if ((hunger >= args->time_to_die) && (!eating))
		return (0);
	return (1);
}

int	police_man(t_args *args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < args->num_of_philos && count < args->num_of_philos)
	{
		if (!(read_lock((args->philos_arr[i]).meals, &args->wr_lock)))
			count++;
		else if (!death_cond(args, &(args->philos_arr[i])))
		{
			print_lock(&(args->philos_arr[i]), RED "died\n" reset);
			pthread_mutex_lock(&args->p_lock);
			mutex_destroy(args);
			return (0);
		}
		i++;
	}
	if (count >= args->num_of_philos)
		return (0);
	return (1);
}
