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

NAME			=		minishell

CC				=		cc

CFLAGS			=		-Wall -Wextra -Werror -I libft/includes/ -I includes/ -g3

HEADER			=		includes/minishell.h \
						includes/builtins.h \
						includes/execute.h \
						includes/parsing.h \
						includes/utils.h \

LIB_H			=		libft/include/libft.h

LIB_A			=		libft/libft.a

# ************************************************** #

SRCS_D			=		srcs/

PARSING_D		=		${SRCS_D}parsing/

UTILS_D			=		${SRCS_D}utils/

CHECK_D			=		${SRCS_D}check/

BUILTINS_D		=		${SRCS_D}builtins/

SIGNALS_D		=		${SRCS_D}signals/

EXECUTION_D		=		${SRCS_D}execute/

OBJS_D			=		.objs/

# ************************************************** #

SRCS			=		${SRCS_D}minishell.c \

PARSING			=		${PARSING_D}tokeniser.c \
						${PARSING_D}lst_into_bloc.c \
						${PARSING_D}parsing.c \
						${PARSING_D}remove_quotes.c \
						${PARSING_D}expand.c \

UTILS			=		${UTILS_D}builtins_utils.c 				\
						${UTILS_D}env_utils.c 					\
						${UTILS_D}envp_lst_utils.c 				\
						${UTILS_D}envp_utils.c 					\
						${UTILS_D}error.c						\
						${UTILS_D}free.c 						\
						${UTILS_D}init.c 						\
						${UTILS_D}token_lst_utils.c				\
						${UTILS_D}token_utils.c 				\
						${UTILS_D}tokeniser_into_lst_utils.c	\
						${UTILS_D}utils.c 						\


CHECK			=		${CHECK_D}syntax.c \

BUILTINS		=		${BUILTINS_D}pwd.c		\
						${BUILTINS_D}cd.c 		\
						${BUILTINS_D}cd_utils.c	\
						${BUILTINS_D}env.c		\
						${BUILTINS_D}unset.c 	\
						${BUILTINS_D}export.c	\
						${BUILTINS_D}exit.c		\
						${BUILTINS_D}echo.c		\

SIGNALS			=		${SIGNALS_D}signals.c \

EXECUTION		=		${EXECUTION_D}builtins.c		\
						${EXECUTION_D}command.c 		\
						${EXECUTION_D}envp_to_array.c	\
						${EXECUTION_D}error_handling.c	\
						${EXECUTION_D}execute_utils.c 	\
						${EXECUTION_D}execute.c 		\
						${EXECUTION_D}file.c 			\
						${EXECUTION_D}free_exec.c 		\
						${EXECUTION_D}heredoc.c			\
						${EXECUTION_D}open_files.c		\
						${EXECUTION_D}parse_data.c		\
						${EXECUTION_D}parse_utils.c		\
						${EXECUTION_D}path.c 			\
						${EXECUTION_D}tmp_file.c		\

# ************************************************** #

OBJS_SRCS		=		${patsubst ${SRCS_D}%.c, ${OBJS_D}%.o, ${SRCS}}

OBJS_PARSING	=		${patsubst ${PARSING_D}%.c, ${OBJS_D}%.o, ${PARSING}}

OBJS_UTILS		=		${patsubst ${UTILS_D}%.c, ${OBJS_D}%.o, ${UTILS}}

OBJS_CHECK		=		${patsubst ${CHECK_D}%.c, ${OBJS_D}%.o, ${CHECK}}

OBJS_BUILTINS	=		${patsubst ${BUILTINS_D}%.c, ${OBJS_D}%.o, ${BUILTINS}}

OBJS_SIGNALS	=		${patsubst ${SIGNALS_D}%.c, ${OBJS_D}%.o, ${SIGNALS}}

OBJS_EXECUTION	=		${patsubst ${EXECUTION_D}%.c, ${OBJS_D}%.o, ${EXECUTION}}

# ************************************************** #

${NAME} :				${LIB_A} ${OBJS_D} ${OBJS_SRCS} ${OBJS_PARSING} ${OBJS_UTILS} ${OBJS_CHECK} ${OBJS_BUILTINS} ${OBJS_SIGNALS} ${OBJS_EXECUTION} ${HEADER} Makefile
	@${MAKE} -C libft/ --no-print-directory
	${CC} ${CFLAGS} ${OBJS_SRCS} ${OBJS_PARSING} ${OBJS_UTILS} ${OBJS_CHECK} ${OBJS_BUILTINS} ${OBJS_SIGNALS} ${OBJS_EXECUTION} ${LIB_A} -o $@ -lreadline

${OBJS_D}%.o :			${SRCS_D}%.c ${HEADER} Makefile
	@${CC} ${CFLAGS} -c $< -o $@

${OBJS_D}%.o :			${PARSING_D}%.c ${HEADER} Makefile
	@${CC} ${CFLAGS} -c $< -o $@

${OBJS_D}%.o :			${UTILS_D}%.c ${HEADER} Makefile
	@${CC} ${CFLAGS} -c $< -o $@

${OBJS_D}%.o :			${CHECK_D}%.c ${HEADER} Makefile
	@${CC} ${CFLAGS} -c $< -o $@

${OBJS_D}%.o :			${BUILTINS_D}%.c ${HEADER} Makefile
	@${CC} ${CFLAGS} -c $< -o $@

${OBJS_D}%.o :			${SIGNALS_D}%.c ${HEADER} Makefile
	@${CC} ${CFLAGS} -c $< -o $@

${OBJS_D}%.o :			${EXECUTION_D}%.c ${HEADER} Makefile
	@${CC} ${CFLAGS} -c $< -o $@

${OBJS_D}:
	@mkdir -p $@

${LIB_A}: FORCE
	${MAKE} -C libft/ --no-print-directory

FORCE:


# ************************************************** #

all :					${NAME}

clean :
	${MAKE} clean -C libft --no-print-directory
	rm -rf ${OBJS_D}

fclean : clean
	${MAKE} fclean -C libft --no-print-directory
	rm -rf ${NAME}

re :	fclean all

# ************************************************** #

.PHONY :		all clean fclean re FORCE

# ************************************************** #