NAME	=	server
NAME1	=	client

CC		=	gcc

CFLAGS	=	-Wall -Werror -Wextra

LFPATH	=	./libft

SRCDIR  = ./srcs/

SRCNAME_SERVER	=	server
SRCNAME_CLIENT	=	client

SRCS_SERVER	=	$(addsuffix .c, $(addprefix srcs/, $(SRCNAME_SERVER)))
SRCS_CLIENT	=	$(addsuffix .c, $(addprefix srcs/, $(SRCNAME_CLIENT)))

OBJS_SERVER	=	$(SRCS_SERVER:.c=.o)
OBJS_CLIENT	=	$(SRCS_CLIENT:.c=.o)

.PHONY: all
all	:	$(NAME) $(NAME1)

$(NAME)	:	${OBJS_SERVER}
			@echo "\n\033[0;32mCompilation..."
			$(MAKE) -C libft/.
			$(CC) -g ${OBJS_SERVER} ${LFPATH}/libft.a $(CFLAGS) -o ${NAME}
			@echo "Complete\033[0m"

$(NAME1)	:	${OBJS_CLIENT}
			@echo "\n\033[0;32mCompilation..."
			$(MAKE) -C libft/.
			$(CC) -g ${OBJS_CLIENT} ${LFPATH}/libft.a $(CFLAGS) -o ${NAME1}
			@echo "Complete\033[0m"

.PHONY: clean
clean	:	
			@echo "\033[0;33mNettoyage..."
			$(MAKE) clean -C libft/.
			$(RM) $(OBJS_CLIENT)
			$(RM) $(OBJS_SERVER)
			@echo "\033[0m"

.PHONY: fclean
fclean	:	clean 
			@echo "\033[0;33mSuppression des exécutables..."
			$(MAKE) fclean -C libft/.
			$(RM) $(NAME)
			$(RM) $(NAME1)
			@echo "\033[0m"

.PHONY: re
re	:	fclean all 

.PHONY: bonus
bonus: $(NAME) $(NAME1) 

.PHONY: test1
test_script	: 

.PHONY: help
help	: 
	@grep -E '^[a-zA-Z1-9_-]+	:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'
