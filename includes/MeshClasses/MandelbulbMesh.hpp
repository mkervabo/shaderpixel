#ifndef __MANDELBULB_MESH_HPP__
# define __MANDELBULB_MESH_HPP__

#include "Mesh.hpp"

class MandelbulbMesh : public Mesh
{
	private:
		Mat		modelMat;

	public:
		MandelbulbMesh();
		virtual void	render(Camera &cam, float timeS, Vec3 &lightPos, Vec2 resolution);
		virtual ~MandelbulbMesh();
};

#endif