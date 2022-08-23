/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   police.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 16:05:39 by ajana             #+#    #+#             */
/*   Updated: 2022/08/23 04:47:37 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*finish(void *arg)
{
	int	i;
	t_args	*args;

	i = -1;
	args = (t_args *)arg;
	if (sem_wait(args->died))
		return (NULL);
	sem_unlink("print_sem");
	sem_unlink("forks");
	sem_unlink("died");
	while (++i < args->num_of_philos)
		kill((args->philos_arr[i]).pid, SIGKILL);
	return (NULL);
}
