NAME = philo
FLAGS = -Wall -Wextra #-Werror
D_SAN = -Wall -Wextra -fsanitize=address
INCLUDES += -I include/
CC = gcc
D = 1
SRCS_DIR = src/
SRCS =	main_philo.c	\
		philo_utils1.c		\
		philo_utils2.c	\
		check_error.c	\
		libft_1.c		\
		libft_2.c		\
		init_func.c		\
# .c		\
# .c		\

OBJS_DIR = obj/
OBJS = $(addprefix $(OBJS_DIR), $(notdir $(SRCS:.c=.o)))

all: $(NAME)
$(NAME): $(OBJS) | $(OBJS_DIR)
	@printf "$(LF)\n🚀 $(P_BLUE)Successfully Created $(P_YELLOW)$(NAME)'s Object files 🚀$(FG_TEXT)\n"
	@printf "\n"
	@printf "$(LF)📚 $(P_BLUE)Create $(P_GREEN)$@ ! 📚\n"
	@echo $(GREEN)
ifeq ($(D), 1)
	$(CC) -g $(D_FLAGS) $(D_SAN) $(INCLUDES) $^ -pthread -o $(NAME)
else
	$(CC) $(FLAGS) $(INCLUDES) $(OBJS) -pthread-o $(NAME)
endif
	@printf "\n$(LF)🎉 $(P_BLUE)Successfully Created $(P_GREEN)$@! 🎉\n$(P_NC)"
	@echo $(PHILO_BANNER)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
ifeq ($(D), 1)
	@$(CC) -g $(D_FLAGS) $(INCLUDES) -c $< -pthread -o $@
else
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -pthread -o $@
endif
	@printf "$(LF)🚧 $(FG_TEXT)$(P_BLUE)Creating $(P_YELLOW)$@ $(P_BLUE)from $(P_YELLOW)$<"

$(OBJS_DIR):
	@mkdir -p $@

clean:
	@echo $(RED)
	@rm -rf $(OBJS)
ifeq ($(D), 1)
	@rm -rf philo.dSYM
endif
	@printf "$(LF)🧹🗑️ $(P_RED) Clean $(P_YELLOW)$(NAME)'s Object files\n"
	@printf  "\n$(P_NC)"

fclean:	clean
	@printf "$(LF)🧹🗑️ $(P_RED) Clean $(P_GREEN)$(NAME)\n"
	@rm -rf $(NAME)
	@echo $(TRASH_BANNER)
	@printf "\n$(P_NC)"

reval:
	@make re -C . D=0
	@make -C . val
val:$(NAME)
	$(eval PHILO=$(shell seq 1 6 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval T_EAT=$(shell seq 5 10 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval T_SLEEP=$(shell seq 10 15 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval T_ES1=$(shell echo $$(($(T_EAT) + $(T_SLEEP))) | tr '\n' ' '))
	$(eval T_ES2=$(shell echo $$(($(T_ES1) + 2)) | tr '\n' ' '))
	$(eval T_DIE=$(shell seq $(T_ES1) $(T_ES2) | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval NUM = $(shell echo $(PHILO)$(T_DIE)$(T_EAT)$(T_SLEEP) ))
	./philo $(NUM)
resan:
	@make re -C . D=1
	@make -C . exe
exe:$(NAME)
	$(eval PHILO=$(shell seq 1 6 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval T_EAT=$(shell seq 50 60 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval T_SLEEP=$(shell seq 50 60 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval T_ES1=$(shell echo $$(($(T_EAT) + $(T_SLEEP))) | tr '\n' ' '))
	$(eval T_ES2=$(shell echo $$(($(T_ES1) + 2)) | tr '\n' ' '))
	$(eval T_DIE=$(shell seq $(T_ES1) $(T_ES2) | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval NUM = $(shell echo $(PHILO)$(T_DIE)$(T_EAT)$(T_SLEEP) ))
	./philo $(NUM)
err:$(NAME)
	$(eval PHILO=$(shell seq 1 10 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval T_EAT=$(shell seq -10 100 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval T_SLEEP=$(shell seq -10 100 | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval T_ES1=$(shell echo $$(($(T_EAT) + $(T_SLEEP) - 20)) | tr '\n' ' '))
	$(eval T_ES2=$(shell echo $$(($(T_ES1) * 2)) | tr '\n' ' '))
	$(eval T_DIE=$(shell seq $(T_ES1) $(T_ES2) | sort -R | tail -n 1 | tr '\n' ' '))
	$(eval NUM = $(shell echo $(PHILO)$(T_DIE)$(T_EAT)$(T_SLEEP) ))
	./philo $(NUM)
ex1:$(NAME)
	./philo 5 150 57 61
top:$(NAME)
	top -oth -stats command,pid,threads,cpu,state,mem,kshrd
# 	while $(shell ps | awk '/philo/ && !/awk/ {print $$1}') ; do \
# 		top -l1 -stats command,pid,threads,cpu,state,mem,kshrd -o th | grep -A3 COMMAND | awk 'NR==1 || /philo/'
# 	done ; \
# _top:
# 	top -l15 -stats command,pid,threads,cpu,state,mem,kshrd -pid $(pgrep -f philo) | grep -A1 COMMAND
t1:
	cc test/threads.c -o test/t1
	./test/t1
git:	fclean
	@echo $(GREEN)
	git add ./
	git commit -m "$m"
	@echo $(YELLOW)
	git push
# gcc -o c dining.c -pthread
re: fclean all

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

# COLORS
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
.PHONY: all clean fclean re
