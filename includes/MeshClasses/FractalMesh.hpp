/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FractalMesh.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiwenn <maiwenn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:58:54 by gperez            #+#    #+#             */
/*   Updated: 2021/10/18 10:54:48 by maiwenn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FRACTAL_MESH_HPP__
# define __FRACTAL_MESH_HPP__

#include "Mesh.hpp"

class FractalMesh : public Mesh
{
	private:
		Mat		modelMat;

	public:
		FractalMesh();
		virtual void	render(Camera &cam, float timeS, Vec3 &lightPos, Vec2 resolution);
		virtual ~FractalMesh();
};

#endif