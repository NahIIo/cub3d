.PHONY: all re clean fclean

NAME	= cub3D

BONUS = 0

CC		= cc
CFLAGS	= -Werror -Wextra -Wall -o3 #-fsanitize=address

MLX_PATH	= minilibx-linux/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)

LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

SRC_PATH = ./sources/
SRC		= 	main.c \
			error.c \
			init/init_data.c \
			init/init_mlx.c \
			init/init_textures.c \
			parsing/check_args.c \
			parsing/parse_data.c \
			parsing/get_file_data.c \
			parsing/create_game_map.c \
			parsing/check_textures.c \
			parsing/check_map.c \
			parsing/check_map_borders.c \
			parsing/fill_color_textures.c \
			parsing/parsing_utils.c \
			movement/input_handler.c \
			movement/player_dir.c \
			movement/player_pos.c \
			movement/player_move.c \
			movement/player_rotate.c \
			render/raycasting.c \
			render/render.c \
			render/texture.c \
			render/image_utils.c \
			exit/exit.c \
			exit/free_data.c \

SRCS	= $(addprefix $(SRC_PATH), $(SRC))

OBJ_PATH	= ./objects/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

INC			=	-I ./includes/\
				-I ./libft/\
				-I ./minilibx-linux/

all: $(OBJ_PATH) $(MLX) $(LIBFT) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)/init
	mkdir -p $(OBJ_PATH)/parsing
	mkdir -p $(OBJ_PATH)/movement
	mkdir -p $(OBJ_PATH)/render
	mkdir -p $(OBJ_PATH)/exit

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -DBONUS=$(BONUS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -DBONUS=$(BONUS) $(OBJS) -o $@ $(INC) $(LIBFT) $(MLX) -lXext -lX11 -lm

$(LIBFT):
	make -sC $(LIBFT_PATH)

$(MLX):
	make -sC $(MLX_PATH) 2>/dev/null

clean:
	rm -rf $(OBJ_PATH)
	make -C $(LIBFT_PATH) clean
	make -C $(MLX_PATH) clean

bonus:
	make all BONUS=1

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all
