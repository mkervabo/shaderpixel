/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 23:49:41 by gperez            #+#    #+#             */
/*   Updated: 2021/08/02 17:57:59 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_HPP
# define CAMERA_HPP

# include "Mat.hpp"
# include "Vec2.hpp"
# define FOV 45.0f
# define SPEED 0.002f
# define SENSITIVITY 0.075f

class	Camera : public Mat
{
	private:
		Mat4	projection;
		Mat4	inverseProjection;
	public:
		Camera(Vec3 p = Vec3(),
			Vec3 r = Vec3(),
			Mat4 proj = Mat4());
		void	resetCam(float dist);
		Mat4	getProjMatrix(void);
		void	setProjMatrix(Mat4 mat);
		Mat4	getInverseProjection(void);
		Vec3	createRay(Vec2 pos, float width, float height);
		~Camera();
};

#endif
