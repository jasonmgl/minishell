# ********************************************************************* #
#  __   __  _______  ___   _  _______  _______  ___   ___      _______  #
# |  |_|  ||   _   ||   | | ||       ||       ||   | |   |    |       | #
# |       ||  |_|  ||   |_| ||    ___||    ___||   | |   |    |    ___| #
# |       ||       ||      _||   |___ |   |___ |   | |   |    |   |___  #
# |       ||       ||     |_ |    ___||    ___||   | |   |___ |    ___| #
# | ||_|| ||   _   ||    _  ||   |___ |   |    |   | |       ||   |___  #
# |_|   |_||__| |__||___| |_||_______||___|    |___| |_______||_______| #
#                                                                       #
# ********************************************************************* #

NAME				=	libft.a

CC					=	gcc

CFLAGS				=	-Wall -Werror -Wextra -I include/ -I ../libft/include

HEADER				=	includes/libft.h

RM					=	rm -rf

#***********************************************************************#

SRCS_D				=	srcs/

OBJS_D				=	.objs/

FT_PRINTF_D			=	ft_printf/

OBJS_FT_PRINTF_D	=	.objs_ft_printf/

GNL_D				=	get_next_line/

OBJS_GNL_D			=	.objs.get_next_line/

LST_D				=	lst/

OBJS_LST_D			=	.objs_lst/

#***********************************************************************#

SRCS				=	${SRCS_D}ft_atoi.c \
						${SRCS_D}ft_bzero.c \
						${SRCS_D}ft_calloc.c \
						${SRCS_D}ft_isalnum.c \
						${SRCS_D}ft_isalpha.c \
						${SRCS_D}ft_isascii.c \
						${SRCS_D}ft_isdigit.c \
						${SRCS_D}ft_isprint.c \
						${SRCS_D}ft_itoa.c \
						${SRCS_D}ft_memchr.c \
						${SRCS_D}ft_memcmp.c \
						${SRCS_D}ft_memcpy.c \
						${SRCS_D}ft_memmove.c \
						${SRCS_D}ft_memset.c \
						${SRCS_D}ft_putchar_fd.c \
						${SRCS_D}ft_putendl_fd.c \
						${SRCS_D}ft_putnbr_fd.c \
						${SRCS_D}ft_putstr_fd.c \
						${SRCS_D}ft_split.c \
						${SRCS_D}ft_strchr.c \
						${SRCS_D}ft_strdup.c \
						${SRCS_D}ft_striteri.c \
						${SRCS_D}ft_strjoin.c \
						${SRCS_D}ft_strlcat.c \
						${SRCS_D}ft_strlcpy.c \
						${SRCS_D}ft_strlen.c \
						${SRCS_D}ft_strmapi.c \
						${SRCS_D}ft_strncmp.c \
						${SRCS_D}ft_strnstr.c \
						${SRCS_D}ft_strrchr.c \
						${SRCS_D}ft_strtrim.c \
						${SRCS_D}ft_substr.c \
						${SRCS_D}ft_tolower.c \
						${SRCS_D}ft_toupper.c

SRCS_LST			=	${LST_D}ft_lstadd_back.c \
						${LST_D}ft_lstadd_front.c \
						${LST_D}ft_lstclear.c \
						${LST_D}ft_lstdelone.c \
						${LST_D}ft_lstlast.c \
						${LST_D}ft_lstnew.c \
						${LST_D}ft_lstsize.c \
						${LST_D}ft_lstiter.c \
						${LST_D}ft_lstmap.c

SRCS_PRINTF			=	${FT_PRINTF_D}ft_functions.c \
						${FT_PRINTF_D}ft_printf.c

SRCS_GNL			=	${GNL_D}get_next_line_utils.c \
						${GNL_D}get_next_line.c

#***********************************************************************#

OBJS				=	${patsubst ${SRCS_D}%.c, ${OBJS_D}%.o, ${SRCS}}

OBJS_FT_PRINTF		=	${patsubst ${FT_PRINTF_D}%.c, ${OBJS_FT_PRINTF_D}%.o, ${SRCS_PRINTF}}

OBJS_GNL			=	${patsubst ${GNL_D}%.c, ${OBJS_GNL_D}%.o, ${SRCS_GNL}}

OBJS_LST			=	${patsubst ${LST_D}%.c, ${OBJS_LST_D}%.o, ${SRCS_LST}}

#***********************************************************************#

all:					${NAME}

${OBJS_D}%.o:			${SRCS_D}%.c ${HEADER} Makefile
	${CC} ${CFLAGS} -c $< -o $@

${OBJS_FT_PRINTF_D}%.o:	${FT_PRINTF_D}%.c ${HEADER} Makefile
	${CC} ${CFLAGS} -c $< -o $@

${OBJS_GNL_D}%.o:		${GNL_D}%.c ${HEADER} Makefile
	${CC} ${CFLAGS} -c $< -o $@

${OBJS_LST_D}%.o:		${LST_D}%.c ${HEADER} Makefile
	${CC} ${CFLAGS} -c $< -o $@

${NAME}:				${OBJS_D} ${OBJS_FT_PRINTF_D} ${OBJS_GNL_D} ${OBJS_LST_D} ${OBJS} ${OBJS_FT_PRINTF}| ${OBJS_GNL} ${OBJS_LST} ${HEADER} Makefile
	ar rc $@ ${OBJS} ${OBJS_FT_PRINTF} ${OBJS_GNL} ${OBJS_LST}

${OBJS_D}:
	mkdir -p $@

${OBJS_FT_PRINTF_D}:
	mkdir -p $@

${OBJS_GNL_D}:
	mkdir -p $@

${OBJS_LST_D}:
	mkdir -p $@

clean:
	${RM} ${OBJS_D}
	${RM} ${OBJS_FT_PRINTF_D}
	${RM} ${OBJS_GNL_D}
	${RM} ${OBJS_LST_D}

fclean:					clean
	${RM} ${NAME}

re:						fclean all

#***********************************************************************#

.PHONY:	all clean fclean re