/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FieldMesh.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 22:35:50 by gperez            #+#    #+#             */
/*   Updated: 2021/10/07 09:27:21 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FIELD_MESH__HPP__
# define __FIELD_MESH__HPP__

# include "Mesh.hpp"

class FieldMesh : public Mesh
{
private:
	Mat		matInField;
public:
	FieldMesh();
	virtual void	render(Camera &cam, float timeS, Vec3 &lightPos);
	virtual void	translate(e_axes axe, float speed);
	virtual ~FieldMesh();
};

#endif