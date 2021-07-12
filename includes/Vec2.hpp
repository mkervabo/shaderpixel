/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec2.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 09:20:11 by gperez            #+#    #+#             */
/*   Updated: 2021/06/17 09:23:26 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC2_HPP
#define VEC2_HPP

#include <math.h>

class Vec2
{
	public: 
	constexpr	Vec2(): x(0), y(0) {}
	constexpr	Vec2(float x, float y): x(x), y(y) {}
	void		setX(float x);
	void		setY(float y);
	void		setVec2(float x, float y);
	float		getX() const;
	float		getY() const;

	Vec2		operator*(float v);

	private:
	float x; 
	float y;
};
#endif
