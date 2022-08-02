/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:38:09 by ajana             #+#    #+#             */
/*   Updated: 2022/08/02 19:02:45 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(struct timeval start)
{
	struct timeval	end;
	gettimeofday(&end, NULL);
	return((end.tv_sec * 1000 + (end.tv_usec / 1000)) -
			(start.tv_sec * 1000 + (start.tv_usec / 1000)));
}

void	msleep(int time_ms)
{
	struct	timeval now;

	gettimeofday(&now, NULL);
	while (get_time(now) < time_ms)
		;
}

void	print_lock(t_philo *philo, char *msg)
{
	int	time;

	time = get_time(philo->args->start);
	if (pthread_mutex_lock(&(philo->args->p_lock)))
		return ;
	printf(WHT "%d %d %s" reset, time, philo->id, msg);
	if (pthread_mutex_unlock(&(philo->args->p_lock)))
		return ;
}

void	mutex_destroy(t_args *args)
{
	int	i;

	i = 0;
	pthread_mutex_unlock(&(args->p_lock));
	pthread_mutex_destroy(&(args->p_lock));
	pthread_mutex_destroy(&(args->wr_lock));
	while (i < args->num_of_philos)
	{
		pthread_mutex_destroy(&((*args->philos_arr).fork));
		i++;
	}
}
