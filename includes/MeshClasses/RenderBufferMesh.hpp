/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RenderBufferMesh.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiwenn <maiwenn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:10:16 by gperez            #+#    #+#             */
/*   Updated: 2021/10/28 16:51:59 by maiwenn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RENDER_BUFFER_MESH_HPP__
# define __RENDER_BUFFER_MESH_HPP__

# include "Mesh.hpp"

# define PATH_RENDERBUFFER_FRAGMENT_BUFFER_A "shader/renderBuffer/buffera.glsl"
# define PATH_RENDERBUFFER_VERTEX_BUFFER_A "shader/renderBuffer/vertexBufferA.glsl"

class RenderBufferMesh : public Mesh
{
	private:
		Mesh	bufferA;
		GLuint	frameBufferInput;
		GLuint	renderBufferInput;
		GLuint	frameBufferOutput;
		GLuint	bufferTexture;
	public:
		RenderBufferMesh();
		virtual bool	loadMesh(t_objPath pathMesh, std::string pathVertex, std::string pathFragment);
		virtual void	render(Camera &cam, float timeS, std::vector<Mesh*> &lights, Vec2 resolution);
		virtual ~RenderBufferMesh();
};

#endif