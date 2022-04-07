/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 15:01:24 by pforesti          #+#    #+#             */
/*   Updated: 2022/04/07 11:14:27 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ph_died(t_sopher *v)
{
	v->tv_death = time_get();
	display(v, "died", v->tv_death, true);
	(*v->philo_died) = 1;
	return (-1);
}

static int	wait_threads(t_philo *philo)
{
	t_sopher	*v;

	v = philo->asoph;
	while (!philo->philo_died && philo->must_eat_full != philo->amount)
	{
		if (v->tv_lsteat)
		{
			pthread_mutex_lock(&v->mutex_eat);
			if (time_diff(v->tv_lsteat, time_get()) >= v->tt_die)
				if (ph_died(v) == -1)
					return (-1);
			pthread_mutex_unlock(&v->mutex_eat);
		}
		v = v->next;
	}
	return (0);
}

/*
void	exit_philo(t_philo *philo)
{
	t_sopher	*v;
	t_sopher	*tofree;

	v = philo->asoph;
	while (v)
	{
		pthread_mutex_destroy(&v->fork_a->fork);
		free(v->fork_a);
		tofree = v;
		v = v->next;
		pthread_mutex_destroy(&tofree->mutex_eat);
		free(tofree);
	}
	pthread_mutex_destroy(&philo->mutex_display);
}
*/

int	main(int ac, char **av)
{
	t_philo	philo;

	pthread_mutex_init(&philo.mutex_display, NULL);
	if (ac == 5 || ac == 6)
	{
		init_tphilo(&philo, ac, av);
		if (philo.amount < 1 || !philo.tt_die || !philo.tt_eat \
			|| !philo.tt_sleep || (philo.must_eat_flag && !philo.must_eat))
			return (-1);
		create_forks(&philo);
		create_ph(&philo);
		join_ph(&philo);
		wait_threads(&philo);
	}
	else
		printf("philo: error: wrong arguments\n");
	return (0);
}
