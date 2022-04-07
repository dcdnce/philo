/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:16:18 by pforesti          #+#    #+#             */
/*   Updated: 2022/04/06 10:53:22 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ph_eat_enough(t_sopher *v)
{
	pthread_mutex_t	m;

	if (v->must_eat_flag && v->have_eat == v->must_eat)
	{
		pthread_mutex_init(&m, NULL);
		pthread_mutex_lock(&m);
		(*v->must_eat_full) += 1;
		pthread_mutex_unlock(&m);
		pthread_mutex_destroy(&m);
		return (1);
	}
	return (0);
}

static int	ph_eat(t_sopher *v)
{
	pthread_mutex_lock(&v->fork_a->fork);
	if (!display(v, "has taken a fork", time_get(), false))
		return (0);
	pthread_mutex_lock(&v->fork_b->fork);
	if (!display(v, "has taken a fork", time_get(), false))
		return (0);
	pthread_mutex_lock(&v->mutex_eat);
	v->tv_lsteat = time_get();
	if (!display(v, "is eating", time_get(), false))
		return (0);
	pthread_mutex_unlock(&v->mutex_eat);
	wait_time(v->tt_eat, time_get());
	pthread_mutex_unlock(&v->fork_a->fork);
	pthread_mutex_unlock(&v->fork_b->fork);
	v->have_eat += 1;
	return (1);
}

static int	ph_sleep(t_sopher *v)
{
	if (!display(v, "is sleeping", time_get(), false))
		return (0);
	wait_time(v->tt_sleep, time_get());
	return (1);
}

/*	Routine of the philosophers - threads					*/
void	*routine(void *phil)
{
	t_sopher	*v;

	v = (t_sopher *)phil;
	while (!(*v->threads_ready))
		usleep(1);
	v->tv_b = time_get();
	if (!(v->n % 2))
		usleep(1000);
	v->tv_lsteat = v->tv_b;
	while (!(*v->philo_died))
	{
		if (!ph_eat(v))
			break ;
		if (ph_eat_enough(v))
			break ;
		if (!ph_sleep(v))
			break ;
		if (!display(v, "is thinking", time_get(), false))
			break ;
	}
	return (NULL);
}
