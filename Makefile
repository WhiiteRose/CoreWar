CC	:= cc
CFLAGS	:= -Wall -Wextra -Werror -std=c11
CPPFLAGS	:= -Iinclude
ASM_NAME	:= asm
COREWAR_NAME	:= corewar
ASM_SRCS	:= src/cli/asm_main.c
COREWAR_SRCS	:= src/cli/corewar_main.c
ASM_OBJS	:= $(ASM_SRCS:.c=.o)
COREWAR_OBJS	:= $(COREWAR_SRCS:.c=.o)
COMMON_SRCS	:= src/vm/arena.c \
	src/vm/process.c	\
	src/vm/vm.c
COMMON_OBJS	:= $(COMMON_SRCS:.c=.o)
TEST_NAME	:= unit_test
TEST_SRCS	:= \
	tests/unit/test_process.c \
	tests/unit/test_arena.c	\
	tests/unit/test_vm.c
TEST_OBJS	:= $(TEST_SRCS:.c=.o)
CRITERION_FLAGS	:= -lcriterion
.PHONY: all clean fclean re test
all: $(ASM_NAME) $(COREWAR_NAME) 
$(ASM_NAME): $(ASM_OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^
$(COREWAR_NAME): $(COREWAR_OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^
test: $(TEST_NAME)
	./$(TEST_NAME)
$(TEST_NAME): $(TEST_OBJS) $(COMMON_OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(CRITERION_FLAGS)
%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
clean:
	rm -f $(ASM_OBJS) $(COREWAR_OBJS) $(TEST_OBJS) $(COMMON_OBJS)
fclean: clean
	rm -f $(ASM_NAME) $(COREWAR_NAME) $(TEST_NAME)
re: fclean all