/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hud.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 20:11:46 by gperez            #+#    #+#             */
/*   Updated: 2021/10/03 21:11:47 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _HUD_HPP_
# define _HUD_HPP_

# include "HudElement.hpp"
# include "Shader.hpp"
# include <vector>

# define SQUARE_PTS 4
# define VERTEX_HUD "shader/vertexHud.glsl"
# define FRAGMENT_HUD "shader/fragmentHud.glsl"

#define HUD_TEXTURE_PATH "Textures/nbTxt.png"

enum	e_cursor_color {WHITE_CURSOR, GREEN_CURSOR, RED_CURSOR};

static float	square_pt[] = {
	-1.0, 1.0,
	-1.0, -1.0,
	1.0, 1.0,
	1.0, -1.0
};

class Hud
{
	private:
		std::vector<HudElement*>	hudElements;
		Material					texture;
		Shader						shader;
		bool						isInit;
		char						cursorColor;
		void						genTexture(void);
		void						fillElements(std::vector<char> unitsValue, unsigned int units);
		void						syncFpsToElements(int fps);
	public:
		Hud();
		void						setCursorColor(char color);
		char						getCursorColor(void);
		int							init(void);
		void						newElement(void);
		void						display(int fps);
		void						deleteElement(unsigned int i);
		~Hud();
};

#endif