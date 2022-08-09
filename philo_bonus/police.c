/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   police.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 16:05:39 by ajana             #+#    #+#             */
/*   Updated: 2022/08/09 22:40:59 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_mthfs(t_args *args)
{
	int	i = -1;

	while (++i < args->num_of_philos)
		kill((args->philos_arr[i]).pid, SIGKILL);
}

int	death_cond(t_args *args, int ind)
{
	int	hunger;

	hunger = get_time(args->start) - (args->philos_arr[ind]).last_meal;
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
			sem_unlink("forks");
			sem_unlink("print_sem");
			kill_mthfs(args);
			return (0);
		}
	}
	return (1);
}
