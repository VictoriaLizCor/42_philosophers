NAME		:= philo
FLAGS		:= -Wall -Wextra #-Werror
INCLUDES	+= -I include/
SRCS_DIR	:= src/
SRCS		:=	main_philo.c		\
				philo_utils1.c		\
				philo_utils2.c		\
				philo_utils3.c		\
				philo_utils4.c		\
				check_error.c		\
				libft_1.c			\
				libft_2.c			\
				sync_functions.c	\
				debug1.c			
SRCS		:= $(addprefix $(SRCS_DIR), $(SRCS))
MAKEFLAGS	+= --no-print-directory
VALGRIND	:= valgrind -q --leak-check=yes --show-leak-kinds=all
HELGRIND	:= valgrind -q --tool=helgrind
LDLIBS		:= -lpthread
DEBUG_DIR	:= $(NAME).dSYM
# CC			= cc
#------ DEBUG ------#
D			:= 0
#------ Sanitizer ------#
S			:= 1
ifneq ($(D), 0)
D_FLAGS		+= -O0 -g3
endif	
ifeq ($(S), 1)
D_FLAGS		+= -D D_PHI=$(D) -pthread $(FLAGS) -fsanitize=thread,undefined,integer -fno-optimize-sibling-calls
MAKEFLAGS	+= --debug
else
D_FLAGS		:= -pthread $(FLAGS) -fsanitize=address,undefined,integer -fno-optimize-sibling-calls
endif

all: $(NAME)
$(NAME): $(SRCS)
	@printf "\n$(LF)📚 $(P_BLUE)Create $(P_GREEN)$@ ! 📚\n"
	@echo $(GREEN)
	@printf "$(CC) $(D_FLAGS) $(INCLUDES) $^ -o $@ \n\n";
	@$(CC) $(D_FLAGS) $(INCLUDES) $^ -o $@
	@printf "\n$(LF)🎉 $(P_BLUE)Successfully Created $(P_GREEN)$@! 🎉\n$(P_NC)"
	@echo $(PHILO_BANNER)

clean:
	@echo $(RED)
#	$(if [ -d "$(DEBUG_DIR)" ], rm -rf $(DEBUG_DIR))
	@if [ -d "$(DEBUG_DIR)" ]; then	\
		rm -rf philo.dSYM; 		\
	fi
	@printf  "\n$(P_NC)"

fclean:	clean
		@printf "$(LF)🧹🗑️ $(P_RED) Clean $(P_GREEN)$(NAME)\n"
		@rm -rf $(NAME)
		@echo $(TRASH_BANNER)
		@printf "\n$(P_NC)"

re: fclean all

.PHONY: all clean fclean re

# use mode: make error r="rule" #
# try to catch error
# $(if $(arg), -./$(NAME) $(arg), \
# 	@printf "Input Example: \n\t make run arg=\"2 410 200 200\"\n")
error:
# bash -c "trap 'trap $(MAKE) $r - SIGINT SIGTERM ERR; \
# exit 1' SIGINT SIGTERM ERR;\
# printf \"$(P_RED) INTERRUPTED $(P_NC)\n\""
#bash -c "trap '$(MAKE) $r' - SIGINT SIGTERM ERR; printf \"$(P_RED) INTERRUPTED $(P_NC)\n\""
	@echo ECXIT $$EC
	$(if $(EC), \
		@printf "EXIT CODE $(EC)\n" \
		@printf "$(P_RED) INTERRUPTED $(P_NC)\n")
	
# @bash -c "trap 'trap - SIGINT SIGTERM ERR; exit 1' SIGINT SIGTERM ERR; $(MAKE) error_msg"


define PHILO

🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛
🏛$(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠛⠛⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)🏛
🏛$(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠨⠒⠁⠌⡐⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠫⠉⠘⠉⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)🏛
🏛$(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡷⡈⠐⠉⢠⡎⠼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢻⢣⢿⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠄⠀⠀⣹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)🏛
🏛$(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⢛⣡⣶⣿⣏⡊⠁⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⣼⢸⣼⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣄⢵⡅⠠⣴⣘⢻⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)🏛
🏛$(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢓⣽⣿⣟⢿⣿⣋⠉⠁⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⣿⠀⣿⡇⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢟⡴⠣⢤⡘⣛⠛⢃⢁⡭⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)🏛
🏛$(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣡⠀⣿⣿⣿⠌⣻⣿⡖⣳⡜⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠷⠈⠾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣼⠐⠁⣰⣣⣿⣭⢿⡆⠡⡃⢽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)🏛
🏛$(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⣿⡤⢻⣿⣿⡘⣿⢿⣇⡇⣳⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⠀⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣇⣻⡎⢀⡅⣿⢟⡭⡢⡘⠃⢁⠄⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)🏛
🏛$(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣇⢇⡜⡜⣿⣿⣧⢹⣻⢥⠉⡻⣏⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢱⣳⡿⣻⢙⣮⠚⠢⠋⡀⠌⡋⠈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)🏛
🏛$(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡰⠰⢜⠽⣿⣿⣬⣧⣭⣒⣃⣈⣸⣽⣍⢑⣉⠙⢿⣿⣿⣿⣿⣿⣿⣿⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣃⣸⣭⣈⣠⡄⠄⠐⠕⠋⠀⢔⣷⠷⡘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)🏛
🏛$(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⠀⠡⣿⠹⠿⢿⡧⠿⠿⡿⡟⠋⡿⠇⠀⠛⠈⠹⣿⣿⣿⣿⣿⣿⣿⠀⣿⣿⣿⣿⣿⣿⡿⢿⠛⠋⠁⠀⢠⠁⠙⠻⣿⡿⣿⣤⡄⠈⠡⠠⣠⠁⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)🏛
🏛$(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠰⣴⢌⢧⣤⠎⠄⢆⣴⣡⡉⣹⣷⣶⣦⣄⡀⠀⠹⣿⣿⣿⣿⣿⣿⠀⣿⣿⣿⣿⣿⡏⡴⣀⡠⡄⡤⡄⢾⢀⣧⡰⠈⢷⡤⡹⣷⡴⡀⡀⠼⢶⣶⡄⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)🏛
🏛$(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡩⡟⡬⠦⢕⠺⡿⠗⣁⡠⠞⣫⣿⣿⣿⡼⡇⠀⣾⣿⣿⣿⣿⣿⠀⣿⣿⣿⣿⣿⢿⡟⠦⠑⢔⠟⢰⢸⠘⣾⡿⡎⢈⢙⣶⣜⠹⢢⠨⠪⡳⡻⡇⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)🏛
🏛$(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣥⢍⡀⣀⢃⠀⠂⡁⢀⡊⠺⢿⣿⡏⢟⣁⣇⢠⣿⣿⣿⣿⣿⣿⠀⣿⣿⣿⣿⣿⣸⡓⠠⡕⣡⣞⡏⢻⢀⢹⣵⣷⣤⡄⡉⠊⣁⣀⡠⢑⣃⣑⠸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)🏛
🏛$(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⣿⣼⣑⣭⣾⣾⣾⣶⣾⡟⣇⢣⣫⣺⣵⣿⣷⢺⣿⣿⣿⣿⣿⣿⠀⣿⣿⣿⣿⡇⢹⢲⣶⠘⢛⣤⣰⣆⡄⠈⠛⢛⣫⠊⣰⡆⠀⠀⢀⠔⣤⣵⣿⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)🏛
🏛$(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⢻⡿⣱⣿⣿⣿⣿⣿⣿⡇⡟⠀⢿⣿⣿⣿⢹⣸⣿⣿⣿⣿⣿⣿⠀⣿⣿⣿⣿⣿⣾⣼⢃⣼⣭⣽⣻⣿⢜⣔⠀⠈⠻⡃⢸⣇⠀⠸⣳⣿⣿⣿⣿⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)🏛
🏛$(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢸⡇⣿⣿⣿⣿⣿⣿⣿⣦⡲⠂⣨⣛⢛⣿⡋⣃⣿⣿⣿⣿⣿⣿⠀⣿⣿⣿⣿⠟⠻⠎⣸⣿⣿⣿⣿⣿⣷⠮⡅⠠⠰⡬⡍⣿⣧⠀⣹⣿⣿⣿⣿⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)🏛
🏛$(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢸⡧⣿⣿⣿⣿⣿⣿⣿⣿⡇⢐⣽⣟⢬⢿⡿⠘⠿⣿⣿⣿⣿⣿⣼⣿⠿⢟⡏⠤⣀⡄⠸⠿⠿⢿⣟⣣⡈⣀⣐⣀⣄⡴⡾⠙⠁⠀⢿⣶⣾⡟⠇⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)🏛
🏛$(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢸⣷⢹⣿⣿⣿⣿⣿⣿⣿⣧⠊⠃⢉⣛⠠⠹⣦⡶⡌⠉⠉⣿⣿⣿⣄⡉⢉⣠⣬⣭⣥⣬⣽⣶⣾⣿⣮⣻⠈⢀⣉⡇⠁⠀⠀⢠⢴⣷⣿⣿⣿⡇⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)🏛
🏛$(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢟⣿⣻⣾⣿⣿⣿⣿⣿⣿⣿⣷⣼⣿⣿⣟⣿⣗⣒⣶⣖⣲⡆⣿⣿⣿⣿⣷⠸⣷⣾⣶⣦⣲⢲⡆⠉⠙⠛⡛⢛⣛⣛⣛⢀⣀⣠⣤⣵⣯⣥⣿⠛⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)🏛
🏛$(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣀⣐⣢⣤⣢⣐⣒⣒⣒⣒⣒⣒⣒⣒⣒⣒⣒⣒⣒⣒⣒⣒⣒⣒⣸⣿⣿⣿⣿⣿⣿⡿⣶⣾⣷⣶⣶⣦⣐⣺⣻⣷⣯⣭⣺⣟⣒⣚⣫⣭⣦⣬⣭⣵⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)🏛
🏛$(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)🏛
🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛🏛

endef
export PHILO
define TRASH

	   $(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)
	   $(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠟⣛⣛⣛⣛⣛⣛⣛⠻⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)
	   $(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⣋⡙⡆⢪⢩⠔⡒⡆⡇⡖⢒⢢⢩⠇⡞⡨⣙⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)
	   $(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢋⠵⣊⢤⠱⡘⡌⡦⠥⠇⡇⡇⣇⠣⠬⠜⡘⡰⢡⠢⢝⠢⡙⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)
	   $(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢏⠔⠧⡘⢄⢢⠔⡣⠜⣒⠭⣭⡀⣓⠀⣩⠭⢑⠣⢍⡲⢊⠜⡡⢊⠢⡙⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)
	   $(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢁⠌⡴⠦⡀⢄⠠⢆⠤⢠⠈⡀⢉⣄⣹⣠⡀⢀⣀⣄⠠⡀⢆⠄⡠⢀⢠⡰⡌⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)
	   $(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⢎⡘⠄⡱⢨⢆⢕⠱⡩⣠⣷⣿⣿⣿⣿⣿⣿⣿⣶⣴⡙⡨⠣⡘⣄⢇⢚⡥⠞⣈⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)
	   $(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⣙⡒⠬⢕⣡⢃⠢⠌⣪⣾⣿⣿⡟⠻⠿⣛⡛⢿⣿⣿⣿⣿⣆⠎⣞⠌⢦⠕⣒⡩⠴⡘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)
	   $(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢸⢠⠬⢉⢂⠇⠦⣁⣳⣿⣿⣿⣿⣿⣿⣶⣶⣬⣍⣙⢻⣿⣿⣿⣯⠳⠚⡘⡌⣆⡒⡇⢇⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)
	   $(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⡜⠸⠬⣙⣸⢸⡘⠃⣿⣿⣿⣿⣿⡇⠀⡄⢠⠀⡤⠀⣾⣿⣿⣿⣿⣤⢤⠇⠧⠅⠒⣚⣸⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)
	   $(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠗⢒⣒⣒⢂⢸⠚⠃⣿⣿⣿⣿⣿⣷⠀⡇⢸⠀⡇⠀⣿⣿⣿⣿⣿⠧⣴⡌⡍⠭⠭⢭⢹⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)
	   $(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⢸⢸⢐⠲⡘⡌⡵⢴⢻⣿⣿⣿⣿⣿⠀⣷⢸⠀⡇⢰⣿⣿⣿⣿⡿⢌⣁⢃⠇⡏⠥⡎⡜⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)
	   $(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡌⡦⠥⢒⡣⠵⡰⡢⡁⣻⣿⣿⣿⣿⣇⣈⣈⣀⣁⣼⣿⣿⣿⡿⠡⠚⠌⡜⡢⠭⣑⡒⢃⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)
	   $(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡖⣊⠥⢒⢣⡱⡐⢅⢂⠝⡻⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⢫⢔⠥⢋⠜⡴⠩⣑⢢⠍⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)
	   $(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠹⡀⡆⠼⣁⢄⡌⠠⡠⢁⢀⡉⣹⠿⠿⠿⣿⠉⣀⢆⢀⠌⣀⢄⠠⣀⢀⠇⡌⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)
	   $(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡙⢌⢚⡵⢫⢎⢝⠢⢅⡂⠵⠄⣀⣀⣐⠁⠦⢑⣊⠵⣊⢬⠣⡙⢮⣡⢊⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)
	   $(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡙⢄⡳⢌⡄⡹⢰⢩⠭⣑⢲⢸⢰⢊⠭⠥⡘⡜⣄⢢⠔⡩⢞⣵⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)
	   $(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣍⡒⠴⢡⠃⡎⣔⣘⣸⢸⠸⣌⣂⠇⢣⠹⡘⢖⣩⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)
	   $(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣯⣬⣕⣒⣒⡒⠚⢒⣒⣒⣊⣭⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)
	   $(RAN)⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿$(NC)
endef
export TRASH

#--------------------UTILS----------------------------#
git:	fclean
		@echo $(CYAN) && git add ./
		@echo $(GREEN) && git commit -e
		@echo $(YELLOW) && git push

norm:
	@norminette ./src | grep -v "OK" || true

#--------------------COLORS----------------------------#
CL_BOLD = \e[1m
RAN = \033[48;5;237m\033[38;5;255m
NC = \033[m

P_RED = \e[1;91m
P_GREEN = \e[1;32m
P_BLUE = \e[0;34m
P_YELLOW = \e[1;33m
P_CCYN = \e[0;1;36m
P_NC = \e[0m
LF = \e[1K\r$(P_NC)
CRLF= \n$(LF)
FG_TEXT = $(P_NC)\e[38;2;189;147;249m

CROSS = "\033[8m"
RED = "\033[1;91m"
GREEN = "\033[1;32m"
BLUE = "\033[1;34m"
YELLOW = "\033[1;33m"
NOCOLOR	= "\033[m"
CYAN = "\033[0;1;36m"
PHILO_BANNER = "$$PHILO"
TRASH_BANNER = "$$TRASH"

#------------- TEST CASES -----------------------------------#
start: $(NAME)
	$(if $(arg), -./$(NAME) $(arg), \
		@printf "Input Example: \n\t make run arg=\"2 410 200 200\"\n")
d0:
	@make re -C . D=0 S=1
d1:
	@make re -C . D=1 S=1
d2:
	@make re -C . D=2 S=1
S0:
	@make re -C . D=0 S=0
r1:$(NAME)
	$(eval PHILO=$(shell seq 1 10 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval NUM = $(shell echo $$(($(PHILO) + 1)) 800 200 100))
	@echo ./philo n die eat sleep
	./philo $(NUM)
r2:$(NAME)
	$(eval PHILO=$(shell seq 5 10 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval NUM = $(shell echo $$(($(PHILO) * 2)) 800 200 200))
	@echo ./philo n die eat sleep
	./philo $(NUM)
r21:$(NAME)
	$(eval PHILO=$(seq 5 10 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval NUM = $(shell echo $$(($(PHILO) * 2)) 410 200 200))
	@echo ./philo n die eat sleep
	./philo $(NUM)
rbig1:$(NAME)
	$(eval PHILO=$(shell seq 11 100 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval NUM = $(shell echo $$(($(PHILO) + 1)) 800 200 100))
	@echo ./philo n die eat sleep
	./philo $(NUM)
	@echo ./philo $(NUM)
rbig1_e:$(NAME)
	$(eval PHILO=$(shell seq 11 100 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval NUM = $(shell echo $$(($(PHILO) + 1)) 800 200 100 10))
	@echo ./philo n die eat sleep
	./philo $(NUM)
	@echo ./philo $(NUM)
rbig2:$(NAME)
	$(eval PHILO=$(shell seq 5 100 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval NUM = $(shell echo $$(($(PHILO) * 2)) 800 200 100))
	@echo ./philo n die eat sleep
	./philo $(NUM)
	@echo ./philo $(NUM)
rbig2_e:$(NAME)
	$(eval PHILO=$(shell seq 5 100 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval NUM = $(shell echo $$(($(PHILO) * 2)) 800 200 100 10))
	@echo ./philo n die eat sleep
	./philo $(NUM)
ifeq ($(INTERRUPTED), 1)
	@echo ./philo $(NUM)
endif
ran1:$(NAME)
	$(eval PHILO=$(shell seq 6 10 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval T_EAT=$(shell seq 100 300 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval T_SLEEP=$(shell seq 100 300 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval T_ES1=$(shell echo $$(($(T_EAT) + $(T_SLEEP) + 1)) | tr '\n' ' '))
	$(eval T_ES2=$(shell echo $$(($(T_ES1) * 2)) | tr '\n' ' '))
	$(eval T_DIE=$(shell seq $(T_ES1) $(T_ES2) | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval NUM = $(shell echo $(PHILO)$(T_DIE)$(T_EAT)$(T_SLEEP) ))
	@echo ./philo n die eat sleep
	./philo $(NUM)
	echo ./philo $(NUM)
ran2:$(NAME)
	$(eval PHILO=$(shell seq 1 6 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval M_EAT=$(shell seq 1 6 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval T_EAT=$(shell seq 100 120 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval T_SLEEP=$(shell seq 100 120 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval T_ES1=$(shell echo $$(($(T_EAT) + $(T_SLEEP))) | tr '\n' ' '))
	$(eval T_ES2=$(shell echo $$(($(T_ES1) + 2)) | tr '\n' ' '))
	$(eval T_DIE=$(shell seq $(T_ES1) $(T_ES2) | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval NUM = $(shell echo $(PHILO)$(T_DIE)$(T_EAT)$(T_SLEEP)$(M_EAT)))
	@echo ./philo n die eat sleep
	./philo $(NUM)
	@echo ./philo $(NUM)
ran_err:$(NAME)
	$(eval PHILO=$(shell seq 1 10 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval T_EAT=$(shell seq -10 100 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval T_SLEEP=$(shell seq -10 100 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval T_ES1=$(shell echo $$(($(T_EAT) + $(T_SLEEP) - 20)) | tr '\n' ' '))
	$(eval T_ES2=$(shell echo $$(($(T_ES1) * 2)) | tr '\n' ' '))
	$(eval T_DIE=$(shell seq $(T_ES1) $(T_ES2) | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval NUM = $(shell echo $(PHILO)$(T_DIE)$(T_EAT)$(T_SLEEP) ))
	@echo ./philo n die eat sleep
	./philo $(NUM)
	@echo ./philo $(NUM)
ex1:$(NAME)
	@echo ./philo n die eat sleep
	./philo 1 210 100 100
ex1_e:$(NAME)
	@echo ./philo n die eat sleep
	./philo 1 210 100 100 2
ex2:$(NAME)
	@echo ./philo n die eat sleep
	./philo 2 310 200 100
ex21:$(NAME)
	@echo ./philo n die eat sleep
	./philo 2 400 200 100
ex2_1:$(NAME)
	@echo ./philo n die eat sleep
	./philo 2 401 200 100
ex2_1e:$(NAME)
	@echo ./philo n die eat sleep
	./philo 2 401 200 100 3
ex2_1e1:$(NAME)
	@echo ./philo n die eat sleep
	./philo 2 401 200 50 3
ex22:$(NAME)
	@echo ./philo n die eat sleep
	./philo 2 410 200 200
ex22_e:$(NAME)
	@echo ./philo n die eat sleep
	./philo 2 410 200 200 2
ex23:$(NAME)
	@echo ./philo n die eat sleep
	./philo 2 310 200 100
ex24:$(NAME)
	@echo ./philo n die eat sleep
	./philo 2 800 100 200
ex25:$(NAME)
	@echo ./philo n die eat sleep
	./philo 2 400 100 101
ex3:$(NAME)
	@echo ./philo n die eat sleep
	./philo 3 410 200 200
ex32:$(NAME)
	@echo ./philo n die eat sleep
	./philo 3 800 200 200
ex31:$(NAME)
	@echo ./philo n die eat sleep
	./philo 3 900 300 100
ex32_e:$(NAME)
	@echo ./philo n die eat sleep
	./philo 3 800 200 200 2
ex4:$(NAME)
	@echo ./philo n die eat sleep
	./philo 4 310 200 100
ex41:$(NAME)
	@echo ./philo n die eat sleep
	./philo 4 400 200 100
ex4_1:$(NAME)
	@echo ./philo n die eat sleep
	./philo 4 401 200 100
ex42:$(NAME)
	@echo ./philo n die eat sleep
	./philo 4 410 200 200
ex42_e:$(NAME)
	@echo ./philo n die eat sleep
	./philo 4 410 200 200 2
ex43:$(NAME)
	@echo ./philo n die eat sleep
	./philo 4 410 300 100
ex5:$(NAME)
	@echo ./philo n die eat sleep
	./philo 5 800 200 200
ex5_e:$(NAME)
	@echo ./philo n die eat sleep
	./philo 5 800 200 200 2
	@echo ./philo 5 800 200 200 2
ex10:$(NAME)
	@echo ./philo n die eat sleep
	./philo 10 600 300 100
ex101:$(NAME)
	@echo ./philo n die eat sleep
	./philo 10 410 300 100
	@echo ./philo 10 410 300 100
ex102:$(NAME)
	@echo ./philo n die eat sleep
	./philo 10 410 200 200
	@echo ./philo 10 410 200 200
ex103:$(NAME)
	@echo ./philo n die eat sleep
	./philo 10 410 300 100
	@echo ./philo 10 410 300 100
ex10_e:$(NAME)
	$(eval EAT=$(shell seq 1 3 | sort -R | tail -n 1 | tr '\n' ' '))
	@echo ./philo n die eat sleep
	./philo 10 800 200 200 $(EAT)
	echo ./philo 10 800 200 200 $(EAT)
ex_11:$(NAME)
	@echo ./philo n die eat sleep
	./philo 11 600 300 100
ex1001:$(NAME)
	@echo ./philo n die eat sleep
	./philo 100 410 200 200
ex3001:$(NAME)
	@echo ./philo n die eat sleep
	./philo 300 410 200 200
exnt: $(NAME)
	@echo ./philo n die eat sleep
	./philo $n 61 10 50
exn: $(NAME)
	@echo ./philo n die eat sleep
	./philo $n $d 200 200
exn1: $(NAME)
	$(eval EXN=$(shell echo $n 800 200 100 $m))
	@echo ./philo n die eat sleep
	./philo $(EXN)
	@echo ./philo $(EXN)
exn2: $(NAME)
	@echo ./philo n die eat sleep
	$(eval EXN=$(shell echo $n 800 200 100 $m))
	./philo $(EXN)
	@echo ./philo $(EXN)
exn3: $(NAME)
	@echo ./philo n die eat sleep
	$(eval EXN=$(shell echo $n 800 200 150 $m))
	./philo $(EXN)
	@echo ./philo $(EXN)
exn4: $(NAME)
	@echo ./philo n die eat sleep
	$(eval EXN=$(shell echo $n 800 100 200 $m))
	./philo $(EXN)
	@echo ./philo $(EXN)
exn5: $(NAME)
	@echo ./philo n die eat sleep
	$(eval EXN=$(shell echo $n 800 100 150 $m))
	./philo $(EXN)
	@echo ./philo $(EXN)
exn6: $(NAME)
	@echo ./philo n die eat sleep
	$(eval EXN=$(shell echo $n 800 150 200 $m))
	./philo $(EXN)
	@echo ./philo $(EXN)
exin: $(NAME)
	@echo ./philo n die eat sleep
	./philo $n $d $e $s $m
top:$(NAME)
	top -opid -stats command,pid,threads,cpu,state,mem,kshrd
# 	while $(shell ps | awk '/philo/ && !/awk/ {print $$1}') ; do \
# 		top -l1 -stats command,pid,threads,cpu,state,mem,kshrd -o th | grep -A3 COMMAND | awk 'NR==1 || /philo/'
# 	done ; \
# _top:
# 	top -l15 -stats command,pid,threads,cpu,state,mem,kshrd -pid $(pgrep -f philo) | grep -A1 COMMAND

# finish standard input with Ctl+D
#git commit -F -<<EOF
# use mode: make git m="msg" #
# git:	fclean
# 	@echo $(GREEN)
# 	git add ./
# 	git commit -m "$m"
# 	@echo $(YELLOW)
# 	git push 
# git log --pretty="%C(Yellow)%h  %C(reset)%ad (%C(Green)%cr%C(reset)) %C(Cyan)%an: %C(reset)%s" --date=short

#------CODE FOR OBJECT FILES------#
# OBJS_DIR = obj/
# OBJS = $(addprefix $(OBJS_DIR), $(notdir $(SRCS:.c=.o)))
## OBJS = $(patsubst %.c,$(OBJDIR)%.o, $(addprefix $(SRCS_DIR),$(SRCS)))
## $(addprefix $(SRCS_DIR), $(SRCS))

#$(NAME): $(OBJS)
#	@printf "$(LF)\n🚀 $(P_BLUE)Successfully Created $(P_YELLOW)$(NAME)'s Object files 🚀$(FG_TEXT)\n"
#	@printf "\n"
#	@printf "$(LF)📚 $(P_BLUE)Create $(P_GREEN)$@ ! 📚\n"
#	@echo $(GREEN)
#	$(CC) -g $(D_SAN) $(INCLUDES) $^ -pthread -o $(NAME)
#	@printf "\n$(LF)🎉 $(P_BLUE)Successfully Created $(P_GREEN)$@! 🎉\n$(P_NC)"
#	@echo $(PHILO_BANNER)

## creating object files
## $(OBJS): $(OBJDIR)/%.o: %.c | $(objdirs)
##	$(CC) -c $< -o $@

# $(OBJS): $(OBJS_DIR)%.o : $(SRCS_DIR)%.c | $(OBJS_DIR)
# 	@$(CC) -g $(D_SAN) $(INCLUDES) -c $< -pthread -o $@
# 	@printf "$(LF)🚧 $(P_BLUE)Creating $(P_YELLOW)$@ $(P_BLUE)from $(P_YELLOW)$< $(FG_TEXT)"

# $(OBJS_DIR):
# 	@mkdir -p $@
#------------#