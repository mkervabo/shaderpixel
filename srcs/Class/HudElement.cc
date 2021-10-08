/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HudElement.cc                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 21:35:48 by gperez            #+#    #+#             */
/*   Updated: 2021/10/03 20:12:31 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "HudElement.hpp"

HudElement::HudElement()
{
	Mat();
	this->vbo = 0;
	this->vao = 0;
	this->offsetTxt = 0;
}

void			HudElement::setVbo(unsigned int v)
{
	this->vbo = v;
}

unsigned int	HudElement::getVbo(void)
{
	return (this->vbo);
}

void			HudElement::setVao(unsigned int v)
{
	this->vao = v;
}

unsigned int	HudElement::getVao(void)
{
	return (this->vao);
}

void			HudElement::setOffsetTxt(char offset)
{
	this->offsetTxt = offset;
}

char			HudElement::getOffsetTxt(void)
{
	return (this->offsetTxt);
}

HudElement::~HudElement()
{
	if (this->vbo)
		glDeleteBuffers(1, &(this->vbo));
}