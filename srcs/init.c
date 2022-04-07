/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 08:38:32 by pforesti          #+#    #+#             */
/*   Updated: 2022/04/06 10:52:18 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_tphilo(t_philo *p, int ac, char **av)
{
	p->must_eat_flag = 0;
	if (ac == 6)
	{
		p->must_eat_flag = 1;
		p->must_eat_full = 0;
		p->must_eat = ft_atoi(av[5]);
	}
	p->threads_ready = 0;
	p->philo_died = 0;
	p->amount = ft_atoi(av[1]);
	p->tt_die = ft_atoi(av[2]);
	p->tt_eat = ft_atoi(av[3]);
	p->tt_sleep = ft_atoi(av[4]);
}

static void	init_ph(t_philo *philo, t_sopher *e)
{
	e->prev = NULL;
	e->next = NULL;
	e->threads_ready = &philo->threads_ready;
	e->afork = &philo->afork;
	e->must_eat = philo->must_eat;
	e->must_eat_flag = philo->must_eat_flag;
	e->must_eat_full = &philo->must_eat_full;
	e->have_eat = 0;
	e->tv_lsteat = 0;
	e->philo_died = &philo->philo_died;
	e->tt_die = philo->tt_die;
	e->tt_eat = philo->tt_eat;
	e->tt_sleep = philo->tt_sleep;
	e->mutex_display = &philo->mutex_display;
	sophadd_back(&philo->asoph, e);
	pthread_mutex_init(&e->mutex_eat, NULL);
	e->fork_a = lst_findn(e->afork, e->n);
	e->fork_b = lst_findn(e->afork, e->n + 1);
}

int	create_ph(t_philo *philo)
{
	size_t			i;
	pthread_t		th;
	t_sopher		*e;

	philo->asoph = NULL;
	i = 0;
	while (i++ < philo->amount)
	{
		e = malloc(sizeof(t_sopher));
		if (!e)
			return (-1);
		e->n = i;
		init_ph(philo, e);
		pthread_create(&th, NULL, &routine, (void *)e);
	}
	e->next = philo->asoph;
	philo->asoph->prev = e;
	(*e->threads_ready) = 1;
	return (0);
}

int	create_forks(t_philo *philo)
{
	size_t	i;
	t_lst	*e;

	philo->afork = NULL;
	i = 0;
	while (i++ < philo->amount)
	{
		e = malloc(sizeof(t_lst));
		if (!e)
			return (-1);
		e->n = i;
		pthread_mutex_init(&e->fork, NULL);
		e->prev = NULL;
		e->next = NULL;
		e->is_available = true;
		lstadd_back(&philo->afork, e);
	}
	e->next = philo->afork;
	philo->afork->prev = e;
	return (0);
}

int	join_ph(t_philo *philo)
{
	t_sopher	*v;
	size_t		i;

	i = 0;
	v = philo->asoph;
	while (i++ < philo->amount)
	{
		pthread_join(v->thid, NULL);
		v = v->next;
	}
	return (0);
}
