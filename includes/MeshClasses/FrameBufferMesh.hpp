#ifndef __RENDER_BUFFER_MESH_HPP__
# define __RENDER_BUFFER_MESH_HPP__

# include "Mesh.hpp"
//# include "MeshEntry.hpp"

# define PATH_FRAMEBUFFER_TEXTURE "shader/frameBuffer/img1.png"
# define PATH_FRAMEBUFFER_BUFFER_A "shader/frameBuffer/buffera.glsl"
# define PATH_FRAMEBUFFER_VERTEX_BUFFER_A "shader/frameBuffer/vertexBufferA.glsl"

class FrameBufferMesh: public Mesh
{
	private:
		Mesh bufferA;
		GLuint frame;
		GLuint frameTexture;
		GLuint renderBuffer;
		Material texture; 
	public:
		FrameBufferMesh();
		virtual bool	loadMesh(t_objPath pathMesh, std::string pathVertex, std::string pathFragment);
		virtual void	render(Camera &cam, float timeS, Vec3 &lightPos, Vec2 resolution);
		virtual ~FrameBufferMesh();
};

#endif