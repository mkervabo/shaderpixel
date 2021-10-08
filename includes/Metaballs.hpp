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