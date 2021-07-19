/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shaderpixel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiwenn <maiwenn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:39:31 by gperez            #+#    #+#             */
/*   Updated: 2021/06/18 18:34:18 by maiwenn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SHADERPIXEL_HPP__
# define __SHADERPIXEL_HPP__

# include <iostream>
# include "Error.hpp"
# include <queue>
# include "Vec2.hpp"
# include "TimeMs.hpp"
# include "Mesh.hpp"
# include "glfw3.h" // Load fenetre

# define WIDTH 1024
# define HEIGHT 768
# define RATIO (float)WIDTH / (float)HEIGHT
# define PROG_NAME "Shaderpixel"
# define RENDER_DIST 100
# define FRAME_RATE 1.0f / 30.0f

# define VBO_SIZE 24
# define EBO_SIZE 36

enum	e_vsync {VSYNC_OFF, VSYNC_ON};
enum	e_stateKey {KEY_PRESS, KEY_DONE, KEY_RELEASE};

class Shaderpixel
{
	private:
		GLFWwindow					*window;
		Camera						cam;
		Vec2						mouseLastPos;
		bool						firstMoove;
		char						keys[GLFW_KEY_END];
		std::queue<char>			queue;
		void						setKey(unsigned int key, char state);
		void						inputKey(unsigned int key);
		Mesh						mesh;
		// TimeMs						time;
	public:
		Shaderpixel();
		void						initWindow(void);
		bool						init(void);
		void						update(Camera &cam);	
		void						checkKeys(void);
		void 						loadVBO();

		void						getKeys(void);
		unsigned int				getState(unsigned int k);
		GLFWwindow					*getWindow(void);
		Camera						&getCam(void);
		Vec2						getMouseLastPos(void);

		void						setMouseLastPos(Vec2 pos);
		void						setFirst(bool isFirst);
		
		void						generateBuffers(void);
		
		bool						isFirst(void);
		~Shaderpixel();
};

#endif