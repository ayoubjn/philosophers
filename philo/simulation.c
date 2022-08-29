/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 10:27:26 by ajana             #+#    #+#             */
/*   Updated: 2022/08/29 10:55:13 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_lock(int *var, int value, pthread_mutex_t *lock)
{
	if (pthread_mutex_lock(lock))
		return ;
	*var = value;
	if (pthread_mutex_unlock(lock))
		return ;
}

void	msleep(int time_ms)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	while (get_time(now) < time_ms)
		usleep(100);
}

void	sleep_think(t_philo *philo)
{
	print_lock(philo, YEL "is sleeping\n");
	msleep(philo->args->time_to_sleep);
	print_lock(philo, YEL "is thinking\n");
}

int	eat(t_philo *philo, t_philo *next_philo)
{
	t_args	*args;

	args = philo->args;
	if (pthread_mutex_lock(&(philo->fork)))
		return (0);
	print_lock(philo, BLU "has taken a fork\n");
	if (pthread_mutex_lock(&(next_philo->fork)))
		return (0);
	print_lock(philo, BLU "has taken a fork\n");
	print_lock(philo, GRN "is eating\n");
	write_lock(&(philo->last_meal), get_time(args->start), &(args->wr_lock));
	write_lock(&(philo->is_eating), 1, &args->wr_lock);
	msleep(args->time_to_eat);
	write_lock(&(philo->is_eating), 0, &args->wr_lock);
	if (pthread_mutex_unlock(&(philo->fork)))
		return (0);
	if (pthread_mutex_unlock(&(next_philo->fork)))
		return (0);
	return (1);
}

void	*routine(void *a)
{
	int		i;
	t_philo	*philo;
	t_args	*args;
	t_philo	*next_philo;

	philo = (t_philo *)a;
	i = philo->id;
	args = philo->args;
	next_philo = &(args->philos_arr[i % (args->num_of_philos)]);
	while (philo->meals && eat(philo, next_philo))
	{
		write_lock(&philo->meals, philo->meals - 1, &args->wr_lock);
		sleep_think(philo);
	}
	return (NULL);
}
