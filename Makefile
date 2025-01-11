NAME = so_long

CC = cc

CFLAGS = -Wall -Werror -Wextra -g


SRCDIR = src

OBJDIR = obj

LIBFTDIR = utils/libft

MLXDIR = minilibx-linux

SRC = $(SRCDIR)/main.c \
      $(SRCDIR)/map.c \
      $(SRCDIR)/validate.c \
      $(SRCDIR)/validate_2.c \
      $(SRCDIR)/input.c \
	  $(SRCDIR)/validate_path.c\
      $(SRCDIR)/render.c

OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)


LIBFT = $(LIBFTDIR)/libft.a

MLX = $(MLXDIR)/libmlx.a

LIBS = -L$(LIBFTDIR) -lft -L$(MLXDIR) -lmlx -lXext -lX11

MLXFLAGS = -I$(MLXDIR)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(MLXFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

$(MLX):
	@$(MAKE) -C $(MLXDIR)

clean:
	@rm -rf  $(OBJDIR)
	@$(MAKE) -C $(LIBFTDIR) clean
	@$(MAKE) -C $(MLXDIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re val
