/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:30:39 by ajana             #+#    #+#             */
/*   Updated: 2022/08/09 22:43:48 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	get_argv(char **av, t_args *args)
{
	args->num_of_philos = atoi(av[1]);
	args->time_to_die = atoi(av[2]);
	args->time_to_eat = atoi(av[3]);
	args->time_to_sleep = atoi(av[4]);
	if (av[5])
		args->num_of_meals = atoi(av[5]);
	else
		args->num_of_meals = -1;
}

void	*philos_init(t_args *args)
{
	int	i;

	i = 0;
	args->forks = sem_open("forks", O_CREAT, 777, args->num_of_philos);
	args->print_sem = sem_open("print_sem", O_CREAT, 777, 1);
	gettimeofday(&(args->start), NULL);
	while (i < args->num_of_philos)
	{
		(args->philos_arr[i]).id = i + 1;
		(args->philos_arr[i]).meals = args->num_of_meals;
		(args->philos_arr[i]).args = args;
		(args->philos_arr[i]).pid = fork();
		if ((args->philos_arr[i]).pid == 0)
			routine(&(args->philos_arr[i]));
		i++;
	}
	return (NULL);
}
