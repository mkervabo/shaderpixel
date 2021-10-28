#ifndef __METABALLS_MESH_HPP__
# define __METABALLS_MESH_HPP__

# include <iostream>
# include <irrKlang.h>
# include <ik_ISoundMixedOutputReceiver.h>
using namespace irrklang;

# include "Mesh.hpp"
# include "Receiver.hpp"

class MetaballsMesh : public Mesh
{
	private:
		Receiver 		receiver;
		ISoundEngine*	engine;
		ISound*			vol;
		GLuint			songText;

	public:
		MetaballsMesh();
		virtual void	render(Camera &cam, float timeS, std::vector<Mesh*> &lights, Vec2 resolution);
		virtual bool	loadMesh(t_objPath pathMesh, std::string pathVertex, std::string pathFragment);
		virtual			~MetaballsMesh();
};

#endif