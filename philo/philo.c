/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:25:39 by ajana             #+#    #+#             */
/*   Updated: 2022/08/29 19:09:04 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_cond(t_args *args, t_philo *philo)
{
	int	hunger;
	int	cond;

	cond = 0;
	pthread_mutex_lock(&args->wr_lock);
	hunger = get_time(args->start) - philo->last_meal;
	if (philo->meals == 0)
		cond = 2;
	if ((hunger >= args->time_to_die) && (!philo->is_eating))
		cond = 1;
	pthread_mutex_unlock(&args->wr_lock);
	return (cond);
}

int	police_man(t_args *args)
{
	int	i;
	int	count;
	int	check;

	i = 0;
	count = 0;
	check = 0;
	while (i < args->num_of_philos)
	{
		check = death_cond(args, &(args->philos_arr[i]));
		if (check == 1)
		{
			print_lock(&(args->philos_arr[i]), RED "died\n");
			mutex_destroy(args);
			return (args->num_of_philos);
		}
		else if (check == 2)
			count++;
		i++;
	}
	return (count);
}

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
	while (police_man(args) < args->num_of_philos)
		;
	free(args);
	return (0);
}
