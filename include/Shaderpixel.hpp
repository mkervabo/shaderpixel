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

extern "C"
{
	# include "glad.h" // Implementation OpenGl
}

# include <iostream>
# include "glfw3.h" // Load fenetre
# include "Error.hpp"
# include "Camera.hpp"
# include "Shader.hpp"
# include <queue>
# include "Vec2.hpp"
#include "TimeMs.hpp"

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



static Vec3 g_vbo[8] = {
	{Vec3(-0.5, -0.5, -0.5)},
	{Vec3(-0.5, 0.5, -0.5)},
	{Vec3(0.5, -0.5, -0.5)},
	{Vec3(0.5, 0.5, -0.5)},
	{Vec3(-0.5, -0.5, 0.5)},
	{Vec3(-0.5, 0.5, 0.5)},
	{Vec3(0.5, -0.5, 0.5)},
	{Vec3(0.5, 0.5, 0.5)}
};

static unsigned int g_ebo[] = {
	0, 1, 2,		2, 3, 0,
	3, 2, 6,		6, 7, 3,
	7, 6, 5,		5, 4, 7,
	4, 5, 1,		1, 0, 4,
	4, 0, 3,		3, 7, 4,
	1, 5, 6,		6, 2, 1};

class Shaderpixel
{
	private:
		GLFWwindow					*window;
		Camera						cam;
		Shader						shader;
		Vec2						mouseLastPos;
		bool						firstMoove;
		char						keys[GLFW_KEY_END];
		std::queue<char>			queue;
		void						setKey(unsigned int key, char state);
		void						inputKey(unsigned int key);
		int							vbo;
		int							vao;
		int							ebo;
		TimeMs						time;				
	public:
		Shaderpixel();
		void						initWindow(void);
		void						init(void);
		void						update(void);	
		void						checkKeys(void);
		void 						loadVBO();

		void						getKeys(void);
		unsigned int				getState(unsigned int k);
		GLFWwindow					*getWindow(void);
		Camera						&getCam(void);
		Shader						&getShader(void);
		unsigned int				getVao(void);
		unsigned int				getBuffer(unsigned int b);
		Vec2						getMouseLastPos(void);

		void						setMouseLastPos(Vec2 pos);
		void						setFirst(bool isFirst);
		
		void						generateBuffers(void);
		
		bool						isFirst(void);
		~Shaderpixel();
};

#endif