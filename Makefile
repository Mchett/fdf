NAME = fdf
FLAGS = -Wall -Wextra -Werror -I includes/ -g
LIBFLAGS = -L./libft -lft -L./minilibx -lmlx -framework OpenGL -framework AppKit
FILES = main.c read_map.c get_next_line.c color.c image.c line.c mouse.c rotate.c key.c	line_list.c mlx.c
INCFILES = includes/fdf.h includes/get_next_line.h
SRCS = $(addprefix src/, $(FILES))
OBJ = $(addprefix objectives/, $(FILES:.c=.o))


all: $(NAME)

$(NAME):$(OBJ) $(INCFILES) | lib
	@gcc $(FLAGS) $(LIBFLAGS) -o $(NAME) $(OBJ)

objectives/%.o: src/%.c | objectives
	@gcc $(FLAGS) -o $@ -c $^

re: fclean all

lib:
	@make -C ./libft
	@make -C ./minilibx

clean:
	@rm -rf objectives/
	@make clean -C ./libft
	@make clean -C ./minilibx

fclean: clean
	@make fclean -C ./libft
	@rm -rf $(NAME)

objectives:
	@mkdir objectives/