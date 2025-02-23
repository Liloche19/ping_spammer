SRC	=	src/main.c

OBJ	=	$(SRC:.c=.o)

NAME	=	ping_spammer

# Colors
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
PURPLE=\033[0;35m
CYAN=\033[0;36m
WHITE=\033[0;37m
DEFAULT=\033[0m

all:	$(OBJ)
	@echo ""
	@echo -e "$(YELLOW)Compiling the program...$(DEFAULT)"
	@echo ""
	@gcc -o $(NAME) $(OBJ)
	@echo -e "$(GREEN)Program compiled !$(DEFAULT) For more informations : ./$(NAME) -h"
	@echo ""

clean:
	@echo ""
	@echo -e "$(CYAN)Removing objects files...$(DEFAULT)"
	@rm -f $(OBJ)
	@echo -e "$(GREEN)All objects files removed !$(DEFAULT)"
	@echo ""

%.o: %.c
	@gcc -c $< -o $@

fclean:	clean
	@echo -e "$(CYAN)Removing all binaries files...$(DEFAULT)"
	@rm -f $(NAME)
	@echo -e "$(GREEN)All objects files removed !$(DEFAULT)"
	@echo ""

re:	fclean all
