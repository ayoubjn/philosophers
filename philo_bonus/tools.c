/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:38:09 by ajana             #+#    #+#             */
/*   Updated: 2022/08/09 22:39:13 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		usleep(100);
}

void	print_lock(t_philo *philo, char *msg)
{
	int	time;

	time = get_time(philo->args->start);
	if (sem_wait(philo->args->print_sem))
		return ;
	printf(WHT "%d %d %s" reset, time, philo->id, msg);
	if (sem_post(philo->args->print_sem))
		return ;
}
