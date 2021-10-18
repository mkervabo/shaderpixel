/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CloudMesh.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiwenn <maiwenn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:41:52 by gperez            #+#    #+#             */
/*   Updated: 2021/10/18 10:53:51 by maiwenn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CLOUD_MESH_HPP__
# define __CLOUD_MESH_HPP__

#include "Mesh.hpp"

#define CLOUD_TEXTURE_PATH "Textures/cloudTexture.jpg"

class CloudMesh : public Mesh
{
	private:
		Material	textureCloud;
	public:
		CloudMesh();
		virtual bool	loadMesh(t_objPath pathMesh, std::string pathVertex, std::string pathFragment);
		virtual void	render(Camera &cam, float timeS, Vec3 &lightPos, Vec2 resolution);
		virtual ~CloudMesh();
};

#endif