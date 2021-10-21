#ifndef __MANDELBOX_MESH_HPP__
# define __MANDELBOX_MESH_HPP__

#include "Mesh.hpp"

class MandelboxMesh : public Mesh
{
	private:
		Mat		modelMat;

	public:
		MandelboxMesh();
		virtual void	render(Camera &cam, float timeS, Vec3 &lightPos, Vec2 resolution);
		virtual ~MandelboxMesh();
};

#endif