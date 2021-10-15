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
		float			size;
		float			velocity;
		float			max_size;
		float			min_size;
		unsigned int	nb_balls;
		Receiver 		receiver;
		ISoundEngine*	engine;
		GLuint			songText;
		float			songData[512];
		// unsigned int	dataSize;

	public:
		MetaballsMesh();
		virtual void	render(Camera &cam, float timeS, Vec3 &lightPos);
		virtual bool	loadMesh(t_objPath pathMesh, std::string pathVertex, std::string pathFragment);
		void			setSize(float new_size);
		void			setVelocity(float new_velocity);
		void			setMaxSize(float new_max_size);
		void			setMinize(float new_min_size);
		void			setNbBalls(unsigned int new_nb_balls);
		void			addSize(float new_size);
		void			addVelocity(float new_velocity);
		void			addMaxSize(float new_max_size);
		void			addMinize(float new_min_size);
		void			addNbBalls(int new_nb_balls);
		void			doubleToFloat();
		virtual			~MetaballsMesh();
};

#endif

	// if (glfwGetKey(this->window, GLFW_KEY_T) == GLFW_PRESS)
	// 	this->meshes[0].meta.addSize(0.1);
	// if (glfwGetKey(this->window, GLFW_KEY_Y) == GLFW_PRESS)
	// 	this->meshes[0].meta.addSize(-0.1);
	// if (glfwGetKey(this->window, GLFW_KEY_U) == GLFW_PRESS)
	// 	this->meshes[0].meta.addaxSize(0.1);
	// if (glfwGetKey(this->window, GLFW_KEY_I) == GLFW_PRESS)
	// 	this->meshes[0].meta.addMaxSize(-0.1);
	// if (glfwGetKey(this->window, GLFW_KEY_O) == GLFW_PRESS)
	// 	this->meshes[0].meta.addMinSize(0.1);
	// if (glfwGetKey(this->window, GLFW_KEY_P) == GLFW_PRESS)
	// 	this->meshes[0].meta.addMinSize(-0.1);
	// if (glfwGetKey(this->window, GLFW_KEY_H) == GLFW_PRESS)
	// 	this->meshes[0].meta.addVelocity(0.1);
	// if (glfwGetKey(this->window, GLFW_KEY_J) == GLFW_PRESS)
	// 	this->meshes[0].meta.addVelocity(-0.1);
	// if (glfwGetKey(this->window, GLFW_KEY_K) == GLFW_PRESS
	// 	&& this->meshes[0].meta.getNbBalls() < 20)
	// 	this->meshes[0].meta.addBalls(1);
	// if (glfwGetKey(this->window, GLFW_KEY_L) == GLFW_PRESS
	// 	&& this->meshes[0].meta.getNbBalls() > 0)
	// 	this->meshes[0].meta.addBalls(-1);	