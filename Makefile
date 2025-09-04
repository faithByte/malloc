HOSTTYPE ?= $(shell uname -m)_$(shell uname -s)

NAME = libft_malloc_$(HOSTTYPE).so
LIB_NAME = libft_malloc.so

SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include

SRC := $(wildcard $(SRC_DIR)/*.c)
SRC += $(wildcard $(SRC_DIR)/utils/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

CC		= gcc #-g -fsanitize=address
CFLAGS	= -I$(INCLUDE_DIR) #-Wall -Wextra -Werror

LDFLAGS := -L./ -lft_malloc


val: fclean all
	./run.sh \
	valgrind --tool=memcheck --track-origins=yes --leak-check=full -s ./run.sh ./malloc 

run: 
	./run.sh ./malloc 

all: $(NAME)
	$(CC) -o malloc main.c -I./include $(LDFLAGS) -lpthread -lm

$(NAME) : $(OBJ)
	@$(CC) -shared -o $@ $(OBJ)
	@rm -f $(LIB_NAME)
	@ln -s $(NAME) $(LIB_NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/utils
	@$(CC) $(CFLAGS) -fPIC -MMD -MT $@ -c $< -o $@

clean:
	@rm -rf *.o
	@rm -rf ./build/*.o

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(NA)
	@rm -rf ./build
	@rm -rf malloc

re: fclean all run

.PHONY: all clean fclean re