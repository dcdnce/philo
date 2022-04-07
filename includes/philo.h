/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:57:06 by pforesti          #+#    #+#             */
/*   Updated: 2022/04/07 11:07:49 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>

# define F_DEATH 	0x1
# define F_NO_DEATH	0x2

typedef struct s_lst
{
	struct s_lst	*prev;
	struct s_lst	*next;
	pthread_mutex_t	fork;
	bool			is_available;
	size_t			n;
}				t_lst;

typedef struct s_sopher
{
	struct s_sopher	*prev;
	struct s_sopher	*next;
	size_t			n;
	pthread_t		thid;
	int				*threads_ready;
	t_lst			**afork;
	t_lst			*fork_a;
	t_lst			*fork_b;
	long			tv_b;
	long			tv_lsteat;
	long			tv_death;
	long			tt_die;
	long			tt_eat;
	long			tt_sleep;
	size_t			have_eat;
	size_t			must_eat;
	short			must_eat_flag;
	size_t			*must_eat_full;
	int				*philo_died;
	pthread_mutex_t	*mutex_display;
	pthread_mutex_t	mutex_eat;
}				t_sopher;

typedef struct s_philo
{
	t_lst			*afork;
	t_sopher		*asoph;
	pthread_mutex_t	mutex_display;
	int				threads_ready;
	size_t			amount;
	long			tt_die;
	long			tt_eat;
	long			tt_sleep;
	size_t			must_eat;
	short			must_eat_flag;
	size_t			must_eat_full;
	int				philo_died;
}				t_philo;

/*	init.c			*/
void	init_tphilo(t_philo *p, int ac, char **av);
int		create_ph(t_philo *philo);
int		create_forks(t_philo *philo);
int		join_ph(t_philo *philo);

/*	routine.c		*/
void	*routine(void *phil);

/*	time.c			*/
int		wait_time(int n, long start);
long	time_diff(long tv_b, long tv_n);
long	time_sum(long time, long tt_thing);
long	time_get(void);

/*	display.c		*/
int		display(t_sopher *v, char *act, long tv_n, bool died);

/*	lists.c			*/
void	lstadd_back(t_lst **afork, t_lst *elem);
t_lst	*lst_findn(t_lst **afork, size_t n);
void	sophadd_back(t_sopher **asoph, t_sopher *elem);

/*	utils.c			*/
int		ft_atoi(const char *nptr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
#endif
