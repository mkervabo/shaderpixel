/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Material.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 14:28:48 by gperez            #+#    #+#             */
/*   Updated: 2021/10/19 11:56:01 by gperez           ###   ########.fr       */
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
		float	specular;
	public:
		Material();
		bool	asTexture(void);
		void	setTexture(Texture *t);
		bool	load(GLenum target, char *txt);
		void	bind(GLenum textureUnit);
		void	setIsText(bool isT);
		bool	getIsText(void);
		void	setColor(Vec3 color);
		Vec3	getColor(void);
		void	setSpecularCoef(float spec);
		float	getSpecularCoef(void);
		void	newTexture(void);
		void	deleteTexture(void);
		void	clearMaterial(void);
		~Material();
};

#endif