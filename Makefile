# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gperez <gperez@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/06 13:36:11 by gperez            #+#    #+#              #
#    Updated: 2021/10/06 13:04:48 by gperez           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Shaderpixel

FLAGCPP = -std=c++11

FLAG = -Wall -Werror -Wextra -g

FLAG_OPENGL = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -lz

APP = -framework AppKit

SRC =	srcs/main.cc \
		srcs/Class/Shaderpixel.cc \
		srcs/Class/Error.cc \
		srcs/Class/Mat.cc \
		srcs/Class/Mat4.cc \
		srcs/Class/Vec3.cc \
		srcs/Class/Vec2.cc \
		srcs/Class/Camera.cc \
		srcs/Class/Shader.cc \
		srcs/Class/TimeMs.cc \
		srcs/Class/Mesh.cc \
		srcs/Class/MeshEntry.cc \
		srcs/Class/Texture.cc \
		srcs/Class/Material.cc \
		srcs/Class/Hud.cc \
		srcs/Class/HudElement.cc \
		srcs/ShaderClasses/ShaderCloud.cc \

NC = \033[0m
BOLD =\033[1m
DIM =\033[2m
ITALIC =\033[3m
UNDER =\033[4m
BLINK =\033[5m

RS_BO = \033[21m
RS_D = \033[22m
RS_I = \033[23m
RS_U =\033[24m
RS_BL = \033[25m

WHITE = \033[37m
BLUE = \033[38;5;37m
CYAN = \033[38;5;117m
GREEN = \033[38;5;120m
MAGENTA = \033[38;5;135m
RED = \033[38;5;203m

COLOR1 = \033[38;5;75m
COLOR2 = \033[38;5;178m

LIB_G = libs/glfw_mac/lib-macos/libglfw3.a

LIB_ASSIMP =	libs/assimp/lib/libassimp.a

LIBS_H =	libs/includes/ \
			libs/glfw_mac/include/GLFW \
			libs/glad/include/glad \
			libs/ \
			libs/stb/ \
			includes/ \
			libs/assimp/include/ \
			includes/ShaderClasses \

LIBS = $(addprefix -I,$(LIBS_H))

INC =	includes/Shaderpixel.hpp \
		includes/Mat.hpp \
		includes/Mat4.hpp \
		includes/Vec3.hpp \
		includes/Shader.hpp \
		includes/TimeMs.hpp \
		includes/Mesh.hpp \
		includes/MeshEntry.hpp \
		includes/Texture.hpp \
		includes/Material.hpp \
		includes/Hud.hpp \
		includes/HudElement.hpp \
		includes/ShaderClasses/ShaderCloud.hpp \

OBJ = $(SRC:.cc=.o)

.PHONY : all
all : $(LIB_ASSIMP) $(NAME)

$(NAME) : $(OBJ)
	@gcc $(FLAG) -o srcs/glad.o -c libs/glad/src/glad.c
	@g++ $(FLAG) $(FLAGCPP) $(FLAG_OPENCL) $(FLAG_OPENGL) $(LIB_G) $(LIB_ASSIMP) srcs/glad.o $^ -o $(NAME)
	@printf "$(BOLD)$(COLOR1)%20s : $(RS_BL)$(RS_BO)$(GREEN)succesfuly made!$(NC)%20s\n" $(NAME)

libs/assimp/CMakeLists.txt :
	git clone https://github.com/assimp/assimp.git libs/assimp --depth 1

$(LIB_ASSIMP) : libs/assimp/CMakeLists.txt
	cmake libs/assimp/CMakeLists.txt -D BUILD_SHARED_LIBS=OFF
	cmake --build libs/assimp/.  #build faster

%.o : %.cc $(INC)
	@printf "$(BOLD)$(COLOR1)%20s : $(RS_BO)$(COLOR2)%20s$(WHITE) ...$(NC)" $(NAME) $(<F)
	@g++ $(FLAG) $(FLAGCPP) $(LIBS) -o $@ -c $<
	@printf "\r"

.PHONY : clean
clean :
	@/bin/rm -rf srcs/*.o
	@/bin/rm -rf srcs/Class/*.o

.PHONY : fclean
fclean : clean
	@/bin/rm -rf $(NAME)

.PHONY : re
re : fclean all