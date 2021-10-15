/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiwenn <maiwenn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:29:41 by gperez            #+#    #+#             */
/*   Updated: 2021/10/12 17:25:15 by maiwenn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Shaderpixel.hpp"

void	exec(Shaderpixel &env)
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	env.getKeys();
	env.checkKeys();
	env.update(env.getCam());
	env.calcTime();
	env.displayHud();
	glfwSwapBuffers(env.getWindow());
	glfwPollEvents();
}

int		main(void)
{
	Shaderpixel			env;
	Camera				&cam = env.getCam();

	// Init //
	try{
		env.initWindow();}
	catch (Error const &e)
	{
		std::cout << e.what() << "\n";
		return (1);
	}
	cam.setProjMatrix(perspective(FOV, RATIO, (float)NEAR_Z, (float)FAR_Z));
	cam.translate(0. , 2., 3.);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glViewport(0, 0, WIDTH, HEIGHT);
	
	if (env.init())
	{
		std::cout << "Error in the initialization\n";
		return (1);
	}

	// Boucle Exec //
	while(!glfwWindowShouldClose(env.getWindow()))
	{
		try {
			exec(env);}
		catch (Error const &e)
		{
			std::cout << e.what() << std::endl;
			glfwSetWindowShouldClose(env.getWindow(), true);
			return (1);
		}
		GLenum err;
		while((err = glGetError()) != GL_NO_ERROR){
			std::cout << "Error " << err << '\n';
		} 
	}
	return (0);
}
