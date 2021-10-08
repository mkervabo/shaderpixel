/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AsteroidMesh.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 09:04:30 by gperez            #+#    #+#             */
/*   Updated: 2021/10/07 09:09:47 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ASTEROID_MESH_HPP__
# define __ASTEROID_MESH_HPP__

# include "Mesh.hpp"

class AsteroidMesh : public Mesh
{
	public:
		AsteroidMesh();
		virtual void	render(Camera &cam, float timeS, Vec3 &lightPos);
		virtual ~AsteroidMesh();
};

#endif