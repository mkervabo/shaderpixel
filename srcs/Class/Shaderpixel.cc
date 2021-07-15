/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shaderpixel.cc                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiwenn <maiwenn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:39:27 by gperez            #+#    #+#             */
/*   Updated: 2021/06/21 09:36:10 by maiwenn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Shaderpixel.hpp"

Shaderpixel::Shaderpixel()
{
	this->firstMoove = true;
	for (unsigned int i = 0; i < GLFW_KEY_END; i++)
		this->keys[i] = KEY_RELEASE;
}


void				Shaderpixel::setMouseLastPos(Vec2 pos)
{
	this->mouseLastPos = pos;
}

Vec2				Shaderpixel::getMouseLastPos(void)
{
	return (this->mouseLastPos);
}

unsigned int		Shaderpixel::getState(unsigned int k)
{
	if (k > GLFW_KEY_END)
		return (KEY_RELEASE);
	return (this->keys[k]);
}

GLFWwindow			*Shaderpixel::getWindow(void)
{
	return (this->window);
}

Camera				&Shaderpixel::getCam(void)
{
	return (this->cam);
}

void				Shaderpixel::setFirst(bool isFirst)
{
	this->firstMoove = isFirst;
}

static void			mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	Shaderpixel		*engine = (Shaderpixel*)glfwGetWindowUserPointer(window);
	Vec2		offsetMouse;
	Vec2		lastMousePos;

	if (!engine)
		return ;
	if (engine->isFirst())
	{
		engine->setMouseLastPos(Vec2(xpos, ypos));
		engine->setFirst(false);
	}
	lastMousePos = engine->getMouseLastPos();
	offsetMouse.setY(xpos - lastMousePos.getX());
	offsetMouse.setX(ypos - lastMousePos.getY());
	engine->setMouseLastPos(Vec2(xpos, ypos));
	offsetMouse = offsetMouse * SENSITIVITY;
	engine->getCam().rotate(Vec3(offsetMouse.getX(), offsetMouse.getY(), 0.0));
}

void				Shaderpixel::initWindow(void)
{
	if (!glfwInit())
	{
		throw (Error(E_FAIL_INIT_GLFW, FAIL_INIT_GLFW, 1));
		return;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	this->window = glfwCreateWindow(WIDTH, HEIGHT, (char*)PROG_NAME, NULL, NULL);
	if (this->window == NULL)
	{
		throw (Error(E_FAIL_CREATE_WINDOW, FAIL_CREATE_WINDOW, 1));
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(this->window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw (Error(E_FAIL_INIT_GLFW, FAIL_INIT_GLAD, 1));
		return ;
	}
	glfwSetCursorPosCallback(this->window, mouse_callback);
	glfwSetWindowUserPointer(this->window, this);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSwapInterval(VSYNC_OFF);
}

bool				Shaderpixel::init(void)
{
	if (this->mesh.loadMesh(PATH_TREE))
		return (1);
	// this->time.setTime();
	return (0);
}

void				Shaderpixel::update(Camera &cam)
{
	this->mesh.render(cam);
	// this->time.setTime();
}

void				Shaderpixel::inputKey(unsigned int key)
{
	if (glfwGetKey(this->window, key) == GLFW_PRESS
		&& this->keys[key] == KEY_RELEASE)
	{
		this->keys[key] = KEY_PRESS;
		this->queue.push(key);
	}
	else if (glfwGetKey(this->window, key) == GLFW_RELEASE
		&& this->keys[key] == KEY_DONE)
		this->keys[key] = KEY_RELEASE;
}

void				Shaderpixel::getKeys(void)
{
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(this->window, true);
	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
		this->cam.translate(E_FRONT, SPEED);
	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
		this->cam.translate(E_FRONT, -SPEED);
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
		this->cam.translate(E_RIGHT, SPEED);
	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
		this->cam.translate(E_RIGHT, -SPEED);
	if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS)
		this->cam.translate(E_UP, SPEED);
	if (glfwGetKey(this->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		this->cam.translate(E_UP, -SPEED);
}

void				Shaderpixel::checkKeys(void)
{
	char	i;

	while (this->queue.size())
	{
		i = this->queue.front();
		//key here
		this->keys[(int)i] = KEY_DONE;
		this->queue.pop();
	}
}

bool				Shaderpixel::isFirst(void)
{
	return (this->firstMoove);
}

Shaderpixel::~Shaderpixel()
{
	this->mesh.clear();
	glfwDestroyWindow(this->window);
	glfwTerminate();
}