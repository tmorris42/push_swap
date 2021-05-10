/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 16:52:08 by tmorris           #+#    #+#             */
/*   Updated: 2021/05/10 19:22:43 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "stack.h"

enum	e_cmd
{
	INVALID_COMMAND = -1,
	QUIT = 0,
	SWAP_A,
	SWAP_B,
	SWAP_BOTH,
	PUSH_A,
	PUSH_B,
	ROTATE_A,
	ROTATE_B,
	ROTATE_BOTH,
	REV_ROTATE_A,
	REV_ROTATE_B,
	REV_ROTATE_BOTH
};

#endif
