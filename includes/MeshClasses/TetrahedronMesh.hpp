/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TetrahedronMesh.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 10:03:45 by gperez            #+#    #+#             */
/*   Updated: 2021/10/28 10:21:04 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TETRAHEDRON_MESH_HPP__
# define __TETRAHEDRON_MESH_HPP__

#include "Mesh.hpp"

class TetrahedronMesh : public Mesh
{
	private:
		Mat		modelMat;
	public:
		TetrahedronMesh();
		virtual void	render(Camera &cam, float timeS, std::vector<Mesh*> &lights, Vec2 resolution);
		virtual ~TetrahedronMesh();
};

#endif