#ifndef __RENDER_BUFFER_MESH_HPP__
# define __RENDER_BUFFER_MESH_HPP__

# include "Mesh.hpp"
//# include "MeshEntry.hpp"

# define PATH_RENDER_BUFFER_TEXTURE "shader/renderBuffer/img1.png"
# define PATH_RENDER_BUFFER_BUFFER_A "shader/renderBuffer/buffera.glsl"
# define PATH_RENDER_BUFFER_VERTEX_BUFFER_A "shader/renderBuffer/vertexBufferA.glsl"

class RenderBufferMesh: public Mesh
{
	private:
		Mesh bufferA;
		GLuint frame;
		GLuint frameTexture;
		GLuint renderBuffer;
		Material texture; 
	public:
		RenderBufferMesh();
		virtual bool	loadMesh(t_objPath pathMesh, std::string pathVertex, std::string pathFragment);
		virtual void	render(Camera &cam, float timeS, Vec3 &lightPos);
		virtual ~RenderBufferMesh();
};

#endif