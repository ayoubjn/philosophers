/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:30:39 by ajana             #+#    #+#             */
/*   Updated: 2022/08/23 06:12:57 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	get_argv(char **av, t_args *args)
{
	// aywa
	args->num_of_philos = atoi(av[1]);
	args->time_to_die = atoi(av[2]);
	args->time_to_eat = atoi(av[3]);
	args->time_to_sleep = atoi(av[4]);
	if (av[5])
		args->num_of_meals = atoi(av[5]);
	else
		args->num_of_meals = -1;
}

void	parent_wait(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->num_of_philos)
		waitpid((args->philos_arr[i]).pid, NULL, 0);
}

void	philos_init(t_args *args)
{
	int			i;
	pthread_t	thread;

	i = 0;
	args->print_sem = open_sem("print_sem", 1);
	args->forks = open_sem("forks", args->num_of_philos);
	args->died = open_sem("died", 0);
	gettimeofday(&(args->start), NULL);
	pthread_create(&thread, NULL, finish, args);
	while (i < args->num_of_philos)
	{
		(args->philos_arr[i]).id = i + 1;
		(args->philos_arr[i]).meals = args->num_of_meals;
		(args->philos_arr[i]).args = args;
		((args->philos_arr[i]).last_meal) = 0;
		(args->philos_arr[i]).pid = fork();
		if ((args->philos_arr[i]).pid == 0)
			routine(&(args->philos_arr[i]));
		i++;
	}
	parent_wait(args);
}
