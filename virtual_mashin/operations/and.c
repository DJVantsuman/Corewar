/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 20:43:26 by itsuman           #+#    #+#             */
/*   Updated: 2017/07/07 20:43:28 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
 * В зависимости от param (dir,ind или reg) возвращает считанные данные
 */
unsigned int    get_dir_ind_reg(t_program *program, t_process *process, int param, int dir_size, int *shift)
{
	char            val[4];
	int             i;

	i = 0;
	// считывает номер регистра
	if (param == 1)
		return (unsigned int) (program->map[process->position + *shift++]);
	else if (param == 2)
	{
		//считывает из директа в зависимости от dir_size и возвращает значение
		while (i < dir_size)
			val[i] = program->map[process->position + *shift + i++];
		(*shift) += dir_size;
		return (unsigned int)(val[0] << 24) + (val[1] << 16) + (val[2] << 8) + val[3];
	}
	else if (param == 3)
	{
		//считывает адрес индиректа
		val[0] = program->map[process->position + *shift];
		val[1] = program->map[process->position + *shift + 1];
		// считывает данные по адресу и возвращает значение
		val[2] = program->map[process->position + (unsigned int)((val[0] << 8) + val[1])];
		val[3] = program->map[process->position + (unsigned int)((val[0] << 8) + val[1]) + 1];
		(*shift) += 2;
		return (unsigned int)((val[2] << 8) + val[3]);
	}
	return (0);
}

/*
 * разбирает кодирующий байт
 */
void    decode_byte(char byte, char **param)
{
	*param[0] = (char)(byte & 192) >> 6;
	*param[1] = (char)(byte & 48) >> 4;
	*param[2] = (char)(byte & 12) >> 2;
}

void    and(t_program *program, t_process *process)
{
	char            *param;
	unsigned int    val[3];
	int             i;
	int             shift;

	i = 3;
	shift = 1;
	decode_byte(program->map[process->position + 1], &param);
	if (process->flag == 1)
	{
		/*
		 * если 3 параметр == 01 (reg)
		 * и регистр существует
		 */
		if (param[2] == 1)
		{
			while (i--)
				val[i] = get_dir_ind_reg(program, process, param[i], 4, &shift);
			process->position += shift + 1;
			if (val[2] <= REG_NUMBER && val[2] > 0)
				program->registers[val[2] - 1] = val[0] & val[1];
			program->carry = program->carry == 0 ? 1 : 0;
		}
		process->flag = 0;
	}
	else
		process->delay = 6;
}