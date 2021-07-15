# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gperez <gperez@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/06 13:36:11 by gperez            #+#    #+#              #
#    Updated: 2021/07/15 15:22:31 by gperez           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Shaderpixel

FLAGCPP = -std=c++11

FLAG = -Wall -Werror -Wextra -g

FLAG_OPENGL = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

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

LIB_ASSIMP =	libs/assimp/bin/libassimp.5.0.1.dylib \
				libs/assimp/bin/libassimp.5.dylib \
				libs/assimp/bin/libassimp.dylib \

LIBS_H =	libs/includes/ \
			libs/glfw_mac/include/GLFW \
			libs/glad/include/glad \
			libs/ \
			includes/ \
			libs/assimp/include/assimp/ \

LIBS = $(addprefix -I,$(LIBS_H))

INC =	includes/Shaderpixel.hpp \
		includes/Mat.hpp \
		includes/Mat4.hpp \
		includes/Vec3.hpp \
		includes/TimeMs.hpp \
		includes/Mesh.hpp \
		includes/MeshEntry.hpp \

OBJ = $(SRC:.cc=.o)

COND1 := $(shell [ -f libs/assimp/bin/assimp ] && echo 1 || echo 0)
COND_CLONE_ASSIMP := $(shell [ -f libs/assimp ] && echo 1 || echo 0)
COND2 := $(shell [ -f libs/assimp/bin/unit ] && echo 1 || echo 0)

all : assimp $(NAME)

$(NAME) : $(OBJ)
	@gcc $(FLAG) -o srcs/glad.o -c libs/glad/src/glad.c
	@g++ $(FLAG) $(FLAGCPP) $(FLAG_OPENCL) $(FLAG_OPENGL) $(LIB_G) $(LIB_ASSIMP) srcs/glad.o $^ -o $(NAME)
	@printf "$(BOLD)$(COLOR1)%20s : $(RS_BL)$(RS_BO)$(GREEN)succesfuly made!$(NC)%20s\n" $(NAME)

assimp :
ifeq ($(COND1), 0)
ifeq ($COND_CLONE_ASSIMP, 1)
	rm -rf libs/assimp
endif
	git clone https://github.com/assimp/assimp.git libs/assimp
	cmake libs/assimp/CMakeLists.txt
	cmake --build libs/assimp/.
endif
ifeq ($(COND2), 0)
ifeq ($(COND1), 1)
ifeq ($COND_CLONE_ASSIMP, 1)
	rm -rf libs/assimp
endif
	git clone https://github.com/assimp/assimp.git libs/assimp
	cmake libs/assimp/CMakeLists.txt
	cmake --build libs/assimp/.
endif
endif

%.o : %.cc $(INC)
	@printf "$(BOLD)$(COLOR1)%20s : $(RS_BO)$(COLOR2)%20s$(WHITE) ...$(NC)" $(NAME) $(<F)
	@g++ $(FLAG) $(FLAGCPP) $(LIBS) -o $@ -c $<
	@printf "\r"

clean :
	@/bin/rm -rf srcs/*.o
	@/bin/rm -rf srcs/Class/*.o

fclean : clean
	@/bin/rm -rf $(NAME)

re : fclean all