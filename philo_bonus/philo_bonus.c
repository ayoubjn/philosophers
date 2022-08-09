/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:25:39 by ajana             #+#    #+#             */
/*   Updated: 2022/08/09 04:20:41 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	sleep_think(t_philo *philo)
{
	print_lock(philo, GRN "is sleeping\n" reset);
	msleep(philo->args->time_to_sleep);
	print_lock(philo, GRN "is thinking\n" reset);
}

int	eat(t_philo *philo)
{
	t_args	*args;

	args = philo->args;
	if (sem_wait(args->forks))
		return (0);
	print_lock(philo, BLU "has taken a fork\n" reset);
	if (sem_wait(args->forks))
		return (0);
	print_lock(philo, BLU "has taken a fork\n" reset);
	print_lock(philo, GRN "is eating\n" reset);
	philo->last_meal = get_time(args->start);
	msleep(args->time_to_eat);
	if (sem_post(args->forks))
		return (0);
	if (sem_post(args->forks))
		return (0);
	return (1);
}

void	routine(t_philo *philo)
{
	while (philo->meals && eat(philo))
	{
		(philo->meals)--;
		sleep_think(philo);
	}
	exit (0);
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
