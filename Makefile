CC = gcc

CFLAGS = -Werror -Wextra -Wall

NAME = getnextline.a

SOURCE = get_next_line.c

OBJ_O = $(SOURCE:.c=.o)

$(NAME): $(OBJ_O) 
		 ar -crs $@ $(OBJ_O)

all: $(NAME)

clean:
	rm -f $(OBJ_O)

fclean: clean 
	rm -f $(NAME)

re: fclean all