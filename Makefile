# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/09 13:26:22 by mfischer          #+#    #+#              #
#    Updated: 2019/11/10 01:41:32 by mfischer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include		Makefiles/default_vars.mk

ifdef RELEASE
CFLAGS += -O3
else
CFLAGS += -g
endif

.PHONY:		install_dep obj clean fclean all GEN_SOURCES test check

all: install_dep mfGUI.a $(OBJS) $(NAME)

$(OBJS):	| obj

mfGUI.a:
	make -C mfGUI/.

obj:
	@echo "$(_BLUE)Creating object directories...$(_END)"
	@mkdir -p $@ $(SRC_DIR)

-include $(DEPS)

obj/%.o: src/%.cpp
	@echo "$(_YELLOW)Compiling $(notdir $<)...$(_END)"
	$(CC) $(CFLAGS) $(INC_DIRS) $(INCLUDES) -MMD -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(_BLUE)Linking binary...$(_END)"
	$(AR) $@ $^ $(LIBDEP) 
	$(RAN) $(NAME)
	@echo "$(_GREEN)Done!$(_END)"

ifeq ($(UNAME), Linux)
install_dep:
	@echo "$(_BLUE)Fetching dependencies...$(_END)"
	@sudo apt-get install libsfml-dev
endif

test:	all
	./$(NAME)

clean:
	@echo "$(_YELLOW)Cleaning OBJs...$(_END)"
	rm -rf obj

fclean: clean
	@echo "$(_YELLOW)Deleting executable...$(_END)"
	rm -rf $(NAME)

re: fclean all

GEN_SOURCES:
	@echo "${_BLUE}Generating source list...${_END}"
	@-rm .srcs
	@find . -type f | grep "\.cpp$$" $(foreach V, $(BLACK_LIST_SRCS), | grep -v "$(V)") | cut -f2- -d/ | grep -v " " | sed "s/$$/ \\\\/" | sed "1s/^       //" | sed "$$ s/..$$//" >> .srcs
	@echo "${_GREEN}Done!${_END}"

check:
	cppcheck --enable=all $(INCLUDES) $(SRCS)