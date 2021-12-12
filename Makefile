# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/01 23:22:06 by plouvel           #+#    #+#              #
#    Updated: 2021/12/10 17:25:29 by plouvel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS_DIR	=	objs/

SRCS_DIR	=	srcs/

SRCS		=	ft_printf.c			\
				printf_apply.c		\
				printf_compute.c	\
				printf_conversion.c	\
				printf_parsing.c	\
				printf_puts.c		\
				printf_utils.c

OBJS		=	$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

CFLAGS		=	-Wall -Werror -Wextra -I $(INC) -I $(LIB_DIR)/$(INC)

CC			=	cc

NAME		=	libftprintf.a

RM			=	rm -rf

LIB_DIR		=	libft

INC			=	includes

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c
				@mkdir -p $(OBJS_DIR)
				$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME)

makeft:
			$(MAKE) -C libft all

cleanft:
			$(MAKE) -C libft clean

fcleanft:
			$(MAKE) -C libft fclean

$(NAME): 	makeft $(OBJS)
			cp libft/libft.a $(NAME)
			ar rc $(NAME) $(OBJS)
			ranlib ${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean fcleanft
			${RM} ${OBJS_DIR}
			${RM} ${NAME}

re:			fclean all

bonus:		$(ALL)

.PHONY:		makeft cleanft fcleanft all clean fclean re
