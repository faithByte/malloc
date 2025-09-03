HOSTTYPE ?= $(shell uname -m)_$(shell uname -s)

NAME = libft_malloc_$(HOSTTYPE).so
LIB_NAME = libft_malloc.so

SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

CC		= gcc #-g -fsanitize=address
CFLAGS	= -I$(INCLUDE_DIR) #-Wall -Wextra -Werror


r:
	gcc -g -fsanitize=address *.c -o test
	./test

val: fclean $(NAME) 
# 	@rm out 2> /dev/null
	$(CC) -o malloc main.c -I./include -L. -lft_malloc 
	export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH LD_PRELOAD=./libft_malloc.so && \
	valgrind --tool=memcheck --track-origins=yes --leak-check=full -s ./malloc 

run:
	@$(CC) -o malloc main.c -I./include -L. -lft_malloc 
	@export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH LD_PRELOAD=./libft_malloc.so && ./malloc

all: $(NAME) run

$(NAME) : $(OBJ)
	@$(CC) -shared -o $@ $(OBJ)
	@rm -f $(LIB_NAME)
	@ln -s $(NAME) $(LIB_NAME)

# 	@$(CC) $(CFLAGS) $^ -o malloc
# 	@$(CC) -shared $(OBJ) -o $(NAME)
# 	@ln -fs $(NAME) $(NA)
	
# 	@$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
# 	@$(CC) $(CFLAGS) -o $@ -c $<
# 	$(CC) -c -o $@ $(FLAGS_CC) $^ -O0 -g -I $(PATH_INC)
	@$(CC) $(CFLAGS) -fPIC -o $@ -c $<

clean:
	@rm -rf *.o
	@rm -rf ./build/*.o

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(NA)
	@rm -rf ./build
	@rm -rf malloc

re: fclean

.PHONY: all clean fclean re