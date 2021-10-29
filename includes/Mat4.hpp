/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mat4.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiwenn <maiwenn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:47:07 by gperez            #+#    #+#             */
/*   Updated: 2021/10/28 16:54:09 by maiwenn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT4_HPP
# define MAT4_HPP

# include <math.h>
# include <iostream>

#define PREC 0.00001

class Mat4
{
    public:  
    Mat4(float mat[4][4]);
    Mat4();
    void				setM(float mat[4][4]);
    
    Mat4				inverse();
    Mat4				translate(class Vec3 trans);
	float				get(int x, int y) const;

    Mat4				operator*(Mat4 b);
    Mat4				operator+(Mat4 b);
    float				*operator[](int i);
	friend std::ostream	&operator<<(std::ostream &os, const Mat4 &mat);


    private:
    float       m[4][4];
};

Mat4    perspective(float fov, float ar, float near, float far);

#endif