/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlowMesh.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:05:00 by gperez            #+#    #+#             */
/*   Updated: 2021/10/26 13:05:00 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __GLOW_MESH_HPP__
# define __GLOW_MESH_HPP__

# include "Mesh.hpp"

class GlowMesh : public Mesh
{
	public:
		GlowMesh();
		virtual void	render(Camera &cam, float timeS, std::vector<Mesh*> &lights, Vec2 resolution);
		virtual ~GlowMesh();
};

#endif