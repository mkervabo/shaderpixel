/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FractalMesh.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:58:54 by gperez            #+#    #+#             */
/*   Updated: 2021/10/06 22:24:38 by gperez           ###   ########.fr       */
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
		virtual void	render(Camera &cam, float timeS, Vec3 &lightPos);
		virtual ~FractalMesh();
};

#endif