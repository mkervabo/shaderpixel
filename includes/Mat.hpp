/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 23:29:17 by gperez            #+#    #+#             */
/*   Updated: 2021/10/18 11:01:49 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT_HPP
# define MAT_HPP

# include <iostream>
# include "Vec2.hpp"
# include "Vec3.hpp"
# include "Mat4.hpp"
# include "str_color.hpp"

enum	e_axes{E_RIGHT, E_UP, E_FRONT};
enum	e_rot{PITCH, YAW, ROLL};

class	Mat
{
	protected:
		Mat4		mat;
		Mat4		inverseMat;

		Vec3		pos;
		Vec3		rot;
		Vec3		sca;

		Vec3		vecFront;
		Vec3		vecUp;
		void		calc(void);
	public:
		Mat(Vec3 p = Vec3(),
			Vec3 r = Vec3(0.0, 90.0, 0.0),
			Vec3 s = Vec3());
		void		reset(void);
		Mat4		getMatrix(bool calculate = true);
		Mat4		getInverseMat(void);
		void		setMatrix(Mat4 m);
		Vec3		getFront(void);
		void		setFront(Vec3 front);
		Vec3		getPosition(void);
		void		setPosition(Vec3 p);
		Vec3		getRotation(void);
		void		setRotation(Vec3 r);
		float		getEuler(e_rot euler);
		Vec3		getScale(void);
		void		setScale(Vec3 s);

		void		lookAt(Vec3 look);
		void		lookAt(void);
		void		translate(e_axes axe, float speed);
		void		translate(Vec3 t);
		void		translate(float x, float y, float z);
		virtual void	rotate(Vec3 rotEuler);
		void		scale(Vec3 s);

		static void	printMatrix(Mat4 mat);
		void		printMatrix(bool calculate = true);
		virtual ~Mat();
};

#endif