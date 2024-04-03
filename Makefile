#------ TARGET ------#
NAME		:= philo
#------ WFLAGS ------#
D_FLAGS		= -Wall -Wextra -Werror
INCLUDES	+= -I include/
#------ SRC FILES & DIRECTORIES ------#
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
#------ DEBUG ------#
D			= 0
#------ Sanitizer ------#
S			= -1
#------ DEBUG UTILS ------#
MAKEFLAGS	+= --no-print-directory
VALGRIND	:= valgrind -s --leak-check=yes --show-leak-kinds=all
HELGRIND	:= valgrind -q --tool=helgrind
MAC_LEAKS	:= leaks -atExit --
BUILD_DIR	:= .build/
DEBUG_DIR	:= $(NAME).dSYM
#------ ADDING DEBUG FLAGS ------#
ifneq ($(D), 0)
D_FLAGS		+= -g3 -D D_PHI=$(D)
endif
ifeq ($(S), -1)
#MAKEFLAGS	+= --debug
OBJS		:= $(addprefix $(SRCS_DIR), $(SRCS))
else
#------CODE FOR OBJECT FILES------#
SRCS		:= $(SRCS:%=$(SRC_DIR)%)
OBJS		:= $(SRCS:$(SRC_DIR)%.c=$(BUILD_DIR)%.o)
DEPS		:= $(OBJS:.o=.d)
endif
#------ Include flags for Sanitizer ------#
ifeq ($(S), 1)
D_FLAGS		+= -O0 -g3 -pthread -fsanitize=thread,undefined,integer -fno-optimize-sibling-calls
endif
ifeq ($(S), 0)
D_FLAGS		+= -O0 -g3 -pthread -fsanitize=address,undefined,integer -fno-optimize-sibling-calls
endif

#------ RULES ------#
all: $(NAME)

$(NAME): $(OBJS)
ifneq ($(S), -1)
	@printf "$(LF)\n🚀 $(P_BLUE)Successfully Created $(P_YELLOW)$(NAME)'s Object files 🚀$(FG_TEXT)\n"
endif
	@printf "\n"
	@printf "$(LF)📚 $(P_BLUE)Create $(P_GREEN)$@ 📚\n"
	@echo $(GREEN)
	@printf "$(CC) $(D_FLAGS) $(INCLUDES) $^ -o $@ \n\n";
	@$(CC) $(D_FLAGS) $(INCLUDES) -pthread  $^ -o $(NAME)
	@printf "\n$(LF)🎉 $(P_BLUE)Successfully Created $(P_GREEN)$@! 🎉\n$(P_NC)"
	@echo $(PHILO_BANNER)

ifneq ($(S), -1)
$(OBJS): $(BUILD_DIR)%.o : $(SRCS_DIR)%.c | $(BUILD_DIR)
	@$(CC) $(D_FLAGS) $(INCLUDES) -MMD -MP -c $< -o $@
#	@printf "$(LF)🚧 $(P_BLUE)Creating $(P_YELLOW)$@ $(P_BLUE)from $(P_YELLOW) $< $(FG_TEXT)"

$(BUILD_DIR):
	@mkdir -p $@
endif
# $(if [ -d "$(DEBUG_DIR)" ], rm -rf $(DEBUG_DIR))
clean:
	@echo $(RED)
	@if [ -d "$(BUILD_DIR)" ]; then	\
		rm -rf $(BUILD_DIR); 		\
		printf "$(LF)🧹🗑️ $(P_RED) Clean $(P_YELLOW)$(NAME)'s Object files$(P_NC)\n"; \
	fi
	@if [ -d "$(DEBUG_DIR)" ]; then	\
		rm -rf $(DEBUG_DIR); 		\
	fi
	@printf  "\n$(P_NC)"

fclean:clean
		@printf "$(LF)🧹🗑️ $(P_RED) Clean $(P_GREEN)$(NAME)\n"
		@rm -rf $(NAME)
		@echo $(TRASH_BANNER)
		@printf "\n$(P_NC)"

re: fclean all
# $(MAKE) fclean
# $(MAKE) all

.PHONY: all clean fclean re

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
	@printf "$(P_GREEN)norminette ./src ./include $(NC)\n"
	@norminette ./src ./include | grep "Error" --color || echo $(GREEN)OK$(E_NC)

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
E_NC	= "\033[m"
CYAN = "\033[0;1;36m"
PHILO_BANNER = "$$PHILO"
TRASH_BANNER = "$$TRASH"

#------------- TEST UTILS -----------------------------------#
start: $(NAME)
	@echo $(GREEN)./$(NAME) $(arg) $(E_NC)
	$(if $(arg), -./$(NAME) $(arg), \
		@printf "Input Example: \n\t make val arg=\"2 410 200 200\"\n")
val: $(NAME)
	@echo $(RED) $(VALGRIND) ./$(NAME) $(arg) $(E_NC)
	$(if $(arg), -$(VALGRIND) ./$(NAME) $(arg), \
		@printf "Input Example: \n\t make val arg=\"2 410 200 200\"\n")
hel: $(NAME)
	@echo $(BLUE) $(HELGRIND) ./$(NAME) $(arg) $(E_NC)
	$(if $(arg), -$(HELGRIND) ./$(NAME) $(arg), \
		@printf "Input Example: \n\t make hel arg=\"2 410 200 200\"\n")
leaks: $(NAME)
	@echo $(YELLOW) $(MAC_LEAKS) ./$(NAME) $(arg) $(E_NC)
	$(if $(arg), -$(MAC_LEAKS) ./$(NAME) $(arg), \
		@printf "Input Example: \n\t make hel arg=\"2 410 200 200\"\n")

debug:
	@make re -C . D=$d S=$s
test_eval: $(NAME)
	-bash test/test_cases.sh
#------------- TEST CASES -----------------------------------#
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
	$(eval PHILO=$(shell seq 11 300 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval NUM = $(shell echo $$(($(PHILO) + 1)) 800 200 100))
	@echo ./philo n die eat sleep
	./philo $(NUM)
	@echo ./philo $(NUM)
rbig1_e:$(NAME)
	$(eval PHILO=$(shell seq 11 300 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval NUM = $(shell echo $$(($(PHILO) + 1)) 800 200 100 10))
	@echo ./philo n die eat sleep
	./philo $(NUM)
	@echo ./philo $(NUM)
rbig2:$(NAME)
	$(eval PHILO=$(shell seq 5 300 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval NUM = $(shell echo $$(($(PHILO) * 2)) 800 200 100))
	@echo ./philo n die eat sleep
	./philo $(NUM)
	@echo ./philo $(NUM)
rbig2_e:$(NAME)
	$(eval PHILO=$(shell seq 5 300 | sort -R | tail -n 1 | tr '\n' ' '))
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
exn1: $(NAME)
	$(eval EXN=$(shell echo $n 800 200 200 $m))
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
