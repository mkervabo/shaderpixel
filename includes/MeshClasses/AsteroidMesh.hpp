/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AsteroidMesh.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiwenn <maiwenn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 09:04:30 by gperez            #+#    #+#             */
/*   Updated: 2021/10/18 10:53:30 by maiwenn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ASTEROID_MESH_HPP__
# define __ASTEROID_MESH_HPP__

# include "Mesh.hpp"

class AsteroidMesh : public Mesh
{
	public:
		AsteroidMesh();
		virtual void	render(Camera &cam, float timeS, Vec3 &lightPos, Vec2 resolution);
		virtual ~AsteroidMesh();
};

#endif