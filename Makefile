NAME = inaweek

CC = cc

CFLAGS 			= -Wextra -Wall -Werror
CFLAGS 			+= -Iinclude -Isrc -O3 -Wunreachable-code -Ofast
# CFLAGS 			+= -DDEBUG=1

LIBS			= -ldl -lglfw -pthread -lm

OBJ_DIR			= obj/
SRC_DIR			= src/

INCLUDE			+= -I ./include 

SRCS 			= $(addprefix $(SRC_DIR), main.c utils.c vec3.c color.c ray.c sphere.c hittable.c interval.c camera.c \
material.c texture.c rtw_stb_image.c quad.c disk.c box.c translated.c rotated.c) 
OBJS 			= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
HDRS 			= $(addprefix include/, box.h utils.h vec3.h color.h sphere.h ray.h hittable.h hittable_list.h \
rtweekend.h interval.h camera.h material.h texture.h rtw_stb_image.h external/stb_image.h external/stb_image_write.h \
quad.h disk.h translated.h rotated.h) 

all: $(NAME)

# Static pattern rule for compilation - adding the .o files in the obj folder 
# with includes for the libft that will allow the <libft.h> notation 
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE)  -c $< -o $@


build:
	@mkdir -p build


$(NAME): $(OBJS) $(HDRS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(INCLUDE) -o $(NAME)

# %.o: %.c
# 	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE) && printf "Compiling: $(notdir $<)"

clean:
	rm -f $(OBJECTS) *~
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)
	rm -rf build

re: fclean all

.PHONY: all clean fclean re libmlx


