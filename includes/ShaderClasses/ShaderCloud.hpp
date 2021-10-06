/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShaderCloud.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:41:52 by gperez            #+#    #+#             */
/*   Updated: 2021/10/06 13:00:45 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SHADER_CLOUD_HPP__
# define __SHADER_CLOUD_HPP__

#include "Mesh.hpp"

#define CLOUD_TEXTURE_PATH "Textures/cloudTexture.jpg"

class ShaderCloud : public Mesh
{
	private:
		Material	textureCloud;
	public:
		ShaderCloud();
		virtual bool	loadMesh(t_objPath pathMesh, std::string pathVertex, std::string pathFragment);
		virtual void	render(Camera &cam, float timeS, Vec3 &lightPos, Mat &modelMat);
		virtual ~ShaderCloud();
};

#endif