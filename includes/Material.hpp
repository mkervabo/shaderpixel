/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Material.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 14:28:48 by gperez            #+#    #+#             */
/*   Updated: 2021/07/27 15:04:27 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MATERIAL_HPP__
# define __MATERIAL_HPP__

# include "Texture.hpp"
# include "Mat.hpp"

class Material
{
	private:
		Texture *text;
		Vec3	colorD;
		bool	isText;
	public:
		Material();
		void	setTexture(Texture *t);
		Texture	*getTexture(void);
		void	setIsText(bool isT);
		bool	getIsText(void);
		void	setColor(Vec3 color);
		Vec3	getColor(void);
		void	newTexture(void);
		void	deleteTexture(void);
		void	clearMaterial(void);
		~Material();
};

#endif