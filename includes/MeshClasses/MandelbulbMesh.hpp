/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MandelbulbMesh.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:07:20 by gperez            #+#    #+#             */
/*   Updated: 2021/10/26 13:07:21 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MANDELBULB_MESH_HPP__
# define __MANDELBULB_MESH_HPP__

#include "Mesh.hpp"

class MandelbulbMesh : public Mesh
{
	private:
		Mat		modelMat;

	public:
		MandelbulbMesh();
		virtual void	render(Camera &cam, float timeS, std::vector<Mesh*> &lights, Vec2 resolution);
		virtual ~MandelbulbMesh();
};

#endif