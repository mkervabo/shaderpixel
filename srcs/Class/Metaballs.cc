#include "Metaballs.hpp"

Metaballs::Metaballs()
{
    this->size = 1.0;
    this->velocity = 1.2;
    this->max_size = 0.5;
    this->min_size = 0.1;
    this->nb_balls = 9;
}

void    Metaballs::setSize(float new_size)
{
    this->size = new_size;
}

void    Metaballs::setVelocity(float new_velocity)
{
    this->velocity = new_velocity;
}

void    Metaballs::setMaxSize(float new_max_size)
{
    this->max_size = new_max_size;
}

void   Metaballs::setMinize(float new_min_size)
{
    this->min_size = new_min_size;
}

void    Metaballs::setNbBalls(unsigned int new_nb_balls)
{
    this->nb_balls = new_nb_balls;
}

float Metaballs::getSize()
{
    return (this->size);
}

float Metaballs::getVelocity()
{
    return (this->velocity);
}

float Metaballs::getMaxSize()
{
    return (this->max_size);
}

float Metaballs::getMinSize()
{  
    return (this->min_size);
}

unsigned int Metaballs::getNbBalls()
{
    return (this->nb_balls);
}

void    Metaballs::addSize(float new_size)
{
    this->size += new_size;
}

void    Metaballs::addVelocity(float new_velocity)
{
    this->velocity += new_velocity;
}

void    Metaballs::addMaxSize(float new_max_size)
{
    this->max_size += new_max_size;
}

void   Metaballs::addMinize(float new_min_size)
{
    this->min_size += new_min_size;
}

void    Metaballs::addNbBalls(int new_nb_balls)
{
    this->nb_balls += new_nb_balls;
}


Metaballs::~Metaballs()
{
}