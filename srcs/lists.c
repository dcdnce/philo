/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 08:40:55 by pforesti          #+#    #+#             */
/*   Updated: 2022/03/29 14:18:15 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lstadd_back(t_lst **afork, t_lst *elem)
{
	t_lst	*v;

	if (!*afork)
	{
		*afork = elem;
		return ;
	}
	v = *afork;
	while (v->next)
		v = v->next;
	v->next = elem;
	elem->prev = v;
}

t_lst	*lst_findn(t_lst **afork, size_t n)
{
	t_lst	*v;
	size_t	i;

	v = *afork;
	i = 0;
	while (++i < n)
		v = v->next;
	return (v);
}

void	sophadd_back(t_sopher **asoph, t_sopher *elem)
{
	t_sopher	*v;

	if (!*asoph)
	{
		*asoph = elem;
		return ;
	}
	v = *asoph;
	while (v->next)
		v = v->next;
	v->next = elem;
	elem->prev = v;
}
