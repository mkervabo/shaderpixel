/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HudElement.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 21:33:58 by gperez            #+#    #+#             */
/*   Updated: 2021/10/03 20:15:34 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _HUDELEMENT_HPP_
# define _HUDELEMENT_HPP_

# include "Material.hpp"

class HudElement : public Mat
{
	private:
		unsigned int	vbo;
		unsigned int	vao;
		char			offsetTxt;
	public:
		HudElement();
		void			setVbo(unsigned int v);
		unsigned int	getVbo(void);
		void			setVao(unsigned int v);
		unsigned int	getVao(void);
		void			setOffsetTxt(char offset);
		char			getOffsetTxt(void);
		~HudElement();
};

#endif