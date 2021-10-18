/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RefractMesh.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiwenn <maiwenn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:43:33 by gperez            #+#    #+#             */
/*   Updated: 2021/10/18 10:54:21 by maiwenn          ###   ########.fr       */
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
		virtual ~RefractMesh();
};

#endif