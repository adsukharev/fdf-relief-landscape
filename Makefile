NAME = fdf
SRC = src/*.c
LIBLINK = -L./libft -lft
MLXLINK = -L./minilibx_macos -lmlx -framework OpenGL -framework Appkit
MATHLINK = -lm
GFLAGS = -Wall -Wextra -Werror

$(NAME):
	#make -C libft
	gcc $(GFLAGS) $(SRC) $(MLXLINK) $(LIBLINK) $(MATHLINK) -o $(NAME)

all: $(NAME)

clean:
	/bin/rm -f libft/*.o
	/bin/rm -f minilibx/*.o

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all