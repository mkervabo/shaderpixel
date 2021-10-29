/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec3.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiwenn <maiwenn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:51:29 by gperez            #+#    #+#             */
/*   Updated: 2021/10/28 16:58:43 by maiwenn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_HPP
#define VEC3_HPP

#include <math.h>
# include "Mat4.hpp"

enum	e_axis {E_X, E_Y, E_Z};

class Vec3
{
    public: 
        constexpr   Vec3(): x(0), y(0), z(0) {};
        constexpr   Vec3(float x, float y, float z): x(x), y(y), z(z) {};
        void        setX(float x);
        void        setY(float y);
        void        setZ(float z);
        void        setVec3(float x, float y, float z);
        void		setVec3(Vec3 v);
        float       getX() const;
        float       getY() const;
        float       getZ() const;
        float       getVec3Axis(e_axis axis);
        
        float       lenght();
        float       dot(Vec3 b);
        Vec3        norm();
        Vec3        cross(Vec3 b);
        Vec3        oppose();
        Vec3		toRadians(void) const;
        
        Vec3        operator+(Vec3 b) const;
        Vec3        operator-(Vec3 b);
        Vec3        operator*(Vec3 b) const;
        Vec3        operator*(float v);
        Vec3        operator*(class Mat4 b);
        Vec3        operator/(float v);
     
    private:
        float       x; 
        float       y;
        float       z;
};

float		radians(float angle);

#endif

