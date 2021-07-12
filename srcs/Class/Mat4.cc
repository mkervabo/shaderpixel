/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mat4.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiwenn <maiwenn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:47:02 by gperez            #+#    #+#             */
/*   Updated: 2021/06/17 17:07:17 by maiwenn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mat4.hpp"
# include "Mat.hpp"

Mat4::Mat4()
{
	*this = Mat4((float[4][4]){
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}
	});
}

Mat4::Mat4(float mat[4][4])
{
	this->m[0][0] = mat[0][0];
	this->m[0][1] = mat[0][1];
	this->m[0][2] = mat[0][2];
	this->m[0][3] = mat[0][3];
	this->m[1][0] = mat[1][0];
	this->m[1][1] = mat[1][1];
	this->m[1][2] = mat[1][2];
	this->m[1][3] = mat[1][3];
	this->m[2][0] = mat[2][0];
	this->m[2][1] = mat[2][1];
	this->m[2][2] = mat[2][2];
	this->m[2][3] = mat[2][3];
	this->m[3][0] = mat[3][0];
	this->m[3][1] = mat[3][1];
	this->m[3][2] = mat[3][2];
 	this->m[3][3] = mat[3][3];
}

void			Mat4::setM(float mat[4][4])
{
	this->m[0][0] = mat[0][0];
	this->m[0][1] = mat[0][1];
	this->m[0][2] = mat[0][2];
	this->m[0][3] = mat[0][3];
	this->m[1][0] = mat[1][0];
	this->m[1][1] = mat[1][1];
	this->m[1][2] = mat[1][2];
	this->m[1][3] = mat[1][3];
	this->m[2][0] = mat[2][0];
	this->m[2][1] = mat[2][1];
	this->m[2][2] = mat[2][2];
	this->m[2][3] = mat[2][3];
	this->m[3][0] = mat[3][0];
	this->m[3][1] = mat[3][1];
	this->m[3][2] = mat[3][2];
	this->m[3][3] = mat[3][3];
}

float			Mat4::get(int x, int y) const
{
	return (this->m[y][x]);
}

static float	determinant(float cofac[9])
{

	float a = cofac[0] * cofac[4] * cofac[8];
	float b = cofac[1] * cofac[5] * cofac[6];
	float c = cofac[2] * cofac[3] * cofac[7];

	float d = cofac[2] * cofac[4] * cofac[6];
	float e = cofac[1] * cofac[3] * cofac[8];
	float f = cofac[0] * cofac[5] * cofac[7];

	return(a + b + c - d - e - f);
} 

static float	cofactor(float mat[4][4])
{
	float a[9] = {
	mat[1][1], mat[1][2], mat[1][3], 
	mat[2][1], mat[2][2], mat[2][3], 
	mat[3][1], mat[3][2], mat[3][3]};
	float b[9] = {
	mat[0][1], mat[0][2], mat[0][3], 
	mat[2][1], mat[2][2], mat[2][3], 
	mat[3][1], mat[3][2], mat[3][3]};
	float c[9] = {
	mat[0][1], mat[0][2], mat[0][3], 
	mat[1][1], mat[1][2], mat[1][3], 
	mat[3][1], mat[3][2], mat[3][3]};
	float d[9] = {
	mat[0][1], mat[0][2], mat[0][3], 
	mat[1][1], mat[1][2], mat[1][3], 
	mat[2][1], mat[2][2], mat[2][3]};
	return (
	(mat[0][0] * determinant(a)) 
	- (mat[1][0] * determinant(b)) 
	+ (mat[2][0] * determinant(c)) 
	-  (mat[3][0] * determinant(d))
	);
}

static Mat4		adjugate(Mat4 mat)
{
	float adju[16][9] = {
	{mat[1][1], mat[1][2], mat[1][3], mat[2][1], mat[2][2], mat[2][3], mat[3][1] , mat[3][2], mat[3][3]},
	{mat[1][0], mat[1][2], mat[1][3], mat[2][0], mat[2][2], mat[2][3], mat[3][0] , mat[3][2], mat[3][3]},
	{mat[1][0], mat[1][1], mat[1][3], mat[2][0], mat[2][1], mat[2][3], mat[3][0] , mat[3][1], mat[3][3]},
	{mat[1][0], mat[1][1], mat[1][2], mat[2][0], mat[2][1], mat[2][2], mat[3][0] , mat[3][1], mat[3][2]},

	{mat[0][1], mat[0][2], mat[0][3], mat[2][1], mat[2][2], mat[2][3], mat[3][1] , mat[3][2], mat[3][3]},
	{mat[0][0], mat[0][2], mat[0][3], mat[2][0], mat[2][2], mat[2][3], mat[3][0] , mat[3][2], mat[3][3]},
	{mat[0][0], mat[0][1], mat[0][3], mat[2][0], mat[2][1], mat[2][3], mat[3][0] , mat[3][1], mat[3][3]},
	{mat[0][0], mat[0][1], mat[0][2], mat[2][0], mat[2][1], mat[2][2], mat[3][0] , mat[3][1], mat[3][2]},

	{mat[0][1], mat[0][2], mat[0][3], mat[1][1], mat[1][2], mat[1][3], mat[3][1] , mat[3][2], mat[3][3]},
	{mat[0][0], mat[0][2], mat[0][3], mat[1][0], mat[1][2], mat[1][3], mat[3][0] , mat[3][2], mat[3][3]},
	{mat[0][0], mat[0][1], mat[0][3], mat[1][0], mat[1][1], mat[1][3], mat[3][0] , mat[3][1], mat[3][3]},
	{mat[0][0], mat[0][1], mat[0][2], mat[1][0], mat[1][1], mat[1][2], mat[3][0] , mat[3][1], mat[3][2]},

	{mat[0][1], mat[0][2], mat[0][3], mat[1][1], mat[1][2], mat[1][3], mat[2][1] , mat[2][2], mat[2][3]},
	{mat[0][0], mat[0][2], mat[0][3], mat[1][0], mat[1][2], mat[1][3], mat[2][0] , mat[2][2], mat[2][3]},
	{mat[0][0], mat[0][1], mat[0][3], mat[1][0], mat[1][1], mat[1][3], mat[2][0] , mat[2][1], mat[2][3]},
	{mat[0][0], mat[0][1], mat[0][2], mat[1][0], mat[1][1], mat[1][2], mat[2][0] , mat[2][1], mat[2][2]},
	};
	
	Mat4 determinants((float[4][4]){ 
	{determinant(adju[0]), -determinant(adju[4]), determinant(adju[8]), -determinant(adju[12])},
	{-determinant(adju[1]), determinant(adju[5]), -determinant(adju[9]), determinant(adju[13])},
	{determinant(adju[2]), -determinant(adju[6]), determinant(adju[10]), -determinant(adju[14])},
	{-determinant(adju[3]), determinant(adju[7]), -determinant(adju[11]), determinant(adju[15])}
	});

   return (determinants);
}

Mat4			Mat4::inverse()
{
	Mat4   	inverse;
	float   deter = cofactor(this->m);
	Mat4   	adju = adjugate(*this);
	for (size_t i = 0; i < 4; i++)
	{
	for(size_t j = 0; j < 4; j++)
	{
	inverse[i][j] = (1 / deter) * adju[i][j];
	}
	}
	return(inverse);
}

Mat4			Mat4::translate(Vec3 trans)
{
	Mat4 mat = (float[4][4]){   
	{1.0, 0.0, 0.0, },
	{0.0, 1.0, 0.0, },
	{0.0, 0.0, 1.0, },
	{trans.getX(), trans.getY(), trans.getZ(), 1.0}
	};
	return(*this * mat);
}

Mat4			perspective(float fov, float ar, float near, float far)
{
	float tan_h_fov = tanf(radians(fov / 2));

	Mat4 res = (float[4][4]){
	{1.0f / (ar * tan_h_fov), 0.0f, 0.0f, 0.0f},
	{0.0f, 1.0f / tan_h_fov, 0.0f, 0.0f},
	{0.0f, 0.0f,  - (far + near) / (far - near), -1.0f},
	{0.0f, 0.0f,  (-2 * far * near) / (far - near), 0.0f}
	};
	return(res);
}

Mat4			Mat4::operator*(Mat4 b)
{
	size_t  i;
	size_t  j; 
	Mat4   	res = Mat4();

	i = 0;
	while (i < 4)
	{
	j = 0;
	while (j < 4)
	{
			res.m[i][j] = b.m[i][0] * this->m[0][j]
				+ b.m[i][1] * this->m[1][j]
				+ b.m[i][2] * this->m[2][j]
				+ b.m[i][3] * this->m[3][j];
	j++;
	} 
	i++;
	}
	return(res);
}

Mat4			Mat4::operator+(Mat4 b)
{
	return(Mat4((float[4][4]){
	{this->m[0][0] + b[0][0], this->m[0][1] + b[0][1], this->m[0][2] + b[0][2], this->m[0][3] + b[0][3]},
	{this->m[1][0] + b[1][0], this->m[1][1] + b[1][1], this->m[1][2] + b[1][2], this->m[1][3] + b[1][3]},
	{this->m[2][0] + b[2][0], this->m[2][1] + b[2][1], this->m[2][2] + b[2][2], this->m[2][3] + b[2][3]},
	{this->m[3][0] + b[3][0], this->m[3][1] + b[3][1], this->m[3][2] + b[3][2], this->m[3][3] + b[3][3]}
	}));
}
float			*Mat4::operator[](int i)
{
	return(this->m[i]);
}

std::ostream	&operator<<(std::ostream &os, const Mat4 &mat)
{
	for (unsigned int y = 0; y < 4; y++)
	{
		for (unsigned int x = 0; x < 4; x++)
			os << mat.get(x, y) << " ";
		os << "\n";
	}
	return (os);
}