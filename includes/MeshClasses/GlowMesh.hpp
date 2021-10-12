#ifndef __GLOW_MESH_HPP__
# define __GLOW_MESH_HPP__

# include "Mesh.hpp"

class GlowMesh : public Mesh
{
	public:
		GlowMesh();
		virtual void	render(Camera &cam, float timeS, Vec3 &lightPos);
		virtual ~GlowMesh();
};

#endif