# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phtruong <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/05 21:46:13 by phtruong          #+#    #+#              #
#    Updated: 2019/05/27 14:06:03 by phtruong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
DEFAULT:=\033[39m
BLACK:=\033[30m
RED:=\033[31m
GREEN:=\033[32m
YELLOW:=\033[33m
BLUE:=\033[34m
MAGENTA:=\033[35m
CYAN:=\033[36m
LGRAY:=\033[37m
DGRAY:=\033[90m
LRED:=\033[91m
LGREEN:=\033[92m
LYELLOW:=\033[93m
LBLUE:=\033[94m
LMAGENTA:=\033[95m
LCYAN:=\033[96m
WHITE:=\033[97m
NC:=\033[0m
CC := gcc
NAME := libftprintf.a
CFLAGS := -Werror -Wall -Wextra

src :=	ft_putstr.c ft_putstr_fd.c ft_strlen.c ft_putchar.c ft_putchar_fd.c ft_strchr.c \
		ft_isdigit.c ft_atoi.c ft_isspace.c ft_strcspn.c ft_printf_util.c print_nbr_driver.c \
		print_nbr_util_1.c print_nbr_util_2.c print_nbr_size_1.c print_nbr_size_2.c \
		print_unbr_size_1.c print_unbr_size_2.c print_unbr_util_1.c print_unbr_util_2.c print_unbr_driver.c print_binary_driver.c print_octal_driver.c print_string.c print_collector.c main.c
no_files := $(words ${src})
obj := ${src:.c=.o}
HEADER := NO
X := 1
Y := 231
DIFF := $(shell echo ${Y} - ${X} + 1| bc)
COLOR_NUM := $(shell echo ${X} + $$RANDOM % ${DIFF} | bc)
COUNT := 1
all:	$(NAME)

$(NAME): $(obj)
	@echo "${LCYAN}Compiling🍩:${NC} \033[0K${GREEN}Completed${NC}\r\c"
	@echo
	@echo "Total file compiled: ${no_files}"
	@ar rc $(NAME) $(obj)

%.o: %.c
	@if [ "$(HEADER)" = "NO" ]; then \
		printf "\n🍩🍩🍩🍩♨o(>_<)o♨🍩🍩🍩🍩\n";\
		echo "${GREEN}";\
		echo "██╗     ██╗██████╗ ███████╗████████╗";\
		echo "██║     ██║██╔══██╗██╔════╝╚══██╔══╝";\
		echo "██║     ██║██████╔╝█████╗     ██║   ";\
		echo "██║     ██║██╔══██╗██╔══╝     ██║   ";\
		echo "███████╗██║██████╔╝██║        ██║   ";\
		echo "╚══════╝╚═╝╚═════╝ ╚═╝        ╚═╝   ";\
		echo "${NC}"; \
		$(eval HEADER = YES) \
	fi
	@$(CC) $(CFLAGS) -c $< -o  $@ -I.
	$(eval COLOR_NUM = $(shell echo ${X} + $$RANDOM % ${DIFF} | bc))
	@echo "${LCYAN}Compiling🍩:${NC}   \033[38;5;${COLOR_NUM}m\033[0K[$<]${NC} \
	Progress: ${COUNT} out of ${no_files}"
	$(eval COUNT = $(shell echo ${COUNT}+1 | bc))
.PHONY: clean
clean:
	@rm -rf $(obj)

.PHONY: fclean
fclean: clean
	@rm -rf $(NAME)

re: fclean all
