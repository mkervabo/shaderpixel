/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MandelboxMesh.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:07:26 by gperez            #+#    #+#             */
/*   Updated: 2021/10/26 13:07:27 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MANDELBOX_MESH_HPP__
# define __MANDELBOX_MESH_HPP__

#include "Mesh.hpp"

class MandelboxMesh : public Mesh
{
	public:
		MandelboxMesh();
		virtual void	render(Camera &cam, float timeS, std::vector<Mesh*> &lights, Vec2 resolution);
		virtual ~MandelboxMesh();
};

#endif