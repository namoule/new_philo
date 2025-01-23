CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
# CFLAGS += -fsanitize=thread
OBJ_DIR = obj
SRC_DIR = src
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/init.c $(SRC_DIR)/utils.c $(SRC_DIR)/thread.c $(SRC_DIR)/routine.c $(SRC_DIR)/supervisor.c $(SRC_DIR)/do_the_dishes.c $(SRC_DIR)/safe_init.c $(SRC_DIR)/time.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET = philo

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

debug : $(OBJS)
	$(CC) $(CFLAGS) -D DEBUGlgrind =1 -o $@ $^

clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

fclean: clean
	rm -rf $(TARGET)

re: fclean all

.PHONY: all clean fclean re
