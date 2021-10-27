#ifndef __TETRAHEDRON_MESH_HPP__
# define __TETRAHEDRON_MESH_HPP__

#include "Mesh.hpp"

class TetrahedronMesh : public Mesh
{
	public:
		TetrahedronMesh();
		virtual void	render(Camera &cam, float timeS, std::vector<Mesh*> &lights, Vec2 resolution);
		virtual ~TetrahedronMesh();
};

#endif