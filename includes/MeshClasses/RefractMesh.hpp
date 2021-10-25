/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RefractMesh.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:43:33 by gperez            #+#    #+#             */
/*   Updated: 2021/10/25 19:54:03 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __REFRACT_MESH_HPP__
# define __REFRACT_MESH_HPP__

#include "Mesh.hpp"

class RefractMesh : public Mesh
{
	private:
		bool isDiffuse;
		bool isSpecular;
	public:
		RefractMesh();
		virtual void	render(Camera &cam, float timeS, Vec3 &lightPos, Vec2 resolution);
		void	switchDiffuse(void);
		void	switchSpecular(void);
		virtual ~RefractMesh();
};

#endif