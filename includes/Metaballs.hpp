#ifndef __METABALLS_HPP__
# define __METABALLS_HPP__

# include <iostream>
# include <irrKlang.h>
# include <ik_ISoundMixedOutputReceiver.h>
using namespace irrklang;

class Metaballs
{
	private:
		float size;
		float velocity;
		float max_size;
		float min_size;
		unsigned int nb_balls;
		// ISoundEngine* engine;
	public:
		Metaballs();
		void setSize(float new_size);
		void setVelocity(float new_velocity);
		void setMaxSize(float new_max_size);
		void setMinize(float new_min_size);
		void setNbBalls(unsigned int new_nb_balls);
		float getSize();
		float getVelocity();
		float getMaxSize();
		float getMinSize();
		unsigned int getNbBalls();
		void addSize(float new_size);
		void addVelocity(float new_velocity);
		void addMaxSize(float new_max_size);
		void addMinize(float new_min_size);
		void addNbBalls(int new_nb_balls);
		
		~Metaballs();
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