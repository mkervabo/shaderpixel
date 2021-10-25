/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RenderBufferMesh.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:10:16 by gperez            #+#    #+#             */
/*   Updated: 2021/10/20 14:15:11 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RENDER_BUFFER_MESH_HPP__
# define __RENDER_BUFFER_MESH_HPP__

# include "Mesh.hpp"

# define PATH_RENDERBUFFER_BUFFER_A "shader/renderBuffer/buffera.glsl"
# define PATH_RENDERBUFFER_VERTEX_BUFFER_A "shader/renderBuffer/vertexBufferA.glsl"

class RenderBufferMesh : public Mesh
{
	private:
		Mesh bufferA;
		GLuint frameBuffer;
		GLuint frameBufferTexture;
		GLuint renderBuffer;
	public:
		RenderBufferMesh();
		virtual bool	loadMesh(t_objPath pathMesh, std::string pathVertex, std::string pathFragment);
		virtual void	render(Camera &cam, float timeS, Vec3 &lightPos, Vec2 resolution);
		virtual ~RenderBufferMesh();
};

#endif