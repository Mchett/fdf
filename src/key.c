/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 11:23:09 by mchett            #+#    #+#             */
/*   Updated: 2019/09/18 13:08:32 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	key_hook(int keycode, void *param)
{
	(void)param;
	if (keycode == 53)
		exit(EXIT_SUCCESS);
	return (0);
}
