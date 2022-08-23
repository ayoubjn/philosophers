/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:25:39 by ajana             #+#    #+#             */
/*   Updated: 2022/08/15 22:50:04 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	read_lock(int var, pthread_mutex_t *lock)
{
	int	value;

	pthread_mutex_lock(lock);
	value = var;
	pthread_mutex_unlock(lock);
	return (value);
}

void	write_lock(int *var, int value, pthread_mutex_t *lock)
{
	if (pthread_mutex_lock(lock))
		return ;
	*var = value;
	if (pthread_mutex_unlock(lock))
		return ;
}

void	sleep_think(t_philo *philo)
{
	print_lock(philo, GRN "is sleeping\n" reset);
	msleep(philo->args->time_to_sleep);
	print_lock(philo, GRN "is thinking\n" reset);
}

int	eat(t_philo *philo, t_philo *next_philo)
{
	t_args	*args;

	args = philo->args;
	if (pthread_mutex_lock(&(philo->fork)))
		return (0);
	print_lock(philo, BLU "has taken a fork\n" reset);
	if (pthread_mutex_lock(&(next_philo->fork)))
		return (0);
	print_lock(philo, BLU "has taken a fork\n" reset);
	print_lock(philo, GRN "is eating\n" reset);
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
	while (eat(philo, next_philo))
	{
		write_lock(&philo->meals, philo->meals - 1, &args->wr_lock);
		sleep_think(philo);
	}
	return (NULL);
}

t_args	*allocate_and_init(char **av)
{
	t_args	*ret;

	ret = malloc(sizeof(t_args));
	if (!ret)
		return (NULL);
	memset(ret, 0, sizeof(t_args));
	get_argv(av, ret);
	ret->philos_arr = malloc(sizeof(t_philo) * ret->num_of_philos);
	if (!ret->philos_arr)
		return (NULL);
	return (ret);
}

int	main(int ac, char **av)
{
	t_args	*args;

	if (ac != 5 && ac != 6)
		return (0);
	args = allocate_and_init(av);
	if (!args)
		return (0);
	philos_init(args);
	while (police_man(args));
	free(args);
	return (0);
}
