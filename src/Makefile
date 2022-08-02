# ------------------------- #
# Some helpful commands:    #
# ------------------------- #
# brew install cppcheck     #
# brew install check        #
# brew install lcov         #
# ------------------------- #

CFGFILE="CPPLINT.cfg"

LIB_NAME   = s21_string.a

SRCS       = s21_string.c \
             s21_sprintf.c \
             s21_sprintf_c.c \
             s21_sprintf_d.c \
             s21_sprintf_u.c \
             s21_sprintf_o.c \
             s21_sprintf_x.c \
             s21_sprintf_f.c \
             s21_sprintf_e.c \
             s21_sprintf_g.c \
             s21_sprintf_s.c \
             s21_sprintf_p.c \
             s21_sscanf.c \
             s21_utils.c \
             s21_itoa.c \
             s21_ftoa.c

T_NAME     = tests/unit.check

T_SRCS     = tests/*.c

REPORT_DIR = report
LCOV_INFO  = coverage.info

HEADER     = s21_string.h

OBJ_       = $(SRCS:%.c=%.o)

CC         = gcc -std=c11
gcov  : CC = gcc -std=c11 --coverage
debug : CC = gcc -std=c11 -g
san   : CC = gcc -g -std=c11 -ggdb3 -fsanitize=address
vg    : CC = gcc -std=c11 -ggdb3
CFLAGS     = -I. -Wall -Wextra -Werror
LIBCHECK   = -lcheck

TEMP_FILES   = *.o *.a $(T_NAME) tests/*.dSYM \
               report tests/coverage** coverage** valgrind*.* \
               *.gcno */*.gcno *.gcda */*.gcda *.gcov */*.gcov 


OS = $(shell uname)
ifeq ($(OS), Linux)
	LINUX_LIBS=-lrt -lpthread -lm
endif


.PHONY : all  re clean clear indocker \
         cpplint cppcheck leaks vg \
         test gcov_report

# all: cpplint cppcheck $(LIB_NAME) test
all: $(LIB_NAME) test

re: clean all

gcov: re

debug: re

san: re

gcov_report:
	@make -i gcov
	@lcov -o $(LCOV_INFO) -c -d .
	@genhtml -o $(REPORT_DIR) $(LCOV_INFO)
	@open  $(REPORT_DIR)/index.html

$(LIB_NAME): $(OBJ_) $(HEADER)
	@ar -rcs $(LIB_NAME) $?
	@ranlib $@
	@cp $@ lib$@
	@echo "build $(LIB_NAME)"

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

# # на случай проблем с линковкой на маке
# BREW_HOME = $(shell brew config | grep HOMEBREW_PREFIX | cut -d" " -f2)
# $(T_NAME): $(LIB_NAME) $(T_SRCS)
# 	$(CC) $(T_SRCS) $(LIBCHECK) -o $(T_NAME) $(LINUX_LIBS) -L. -I. -lcheck -ls21_string -I${BREW_HOME}/include -L${BREW_HOME}/Cellar/check/0.15.2/lib 
# 	@echo "✅"

$(T_NAME): $(LIB_NAME) $(T_SRCS)
	@$(CC) $(T_SRCS) $(LIBCHECK) -o $(T_NAME) $(LINUX_LIBS) -L. -ls21_string

test: $(T_NAME)
	@echo "run unit tests"
	@./$(T_NAME)

leaks: clean $(T_NAME)
	@echo "\n══════════ check leaks ══════════ \n\n"
	CK_FORK=no leaks --atExit -- ./$(T_NAME)

vg: $(T_NAME)
	CK_FORK=no valgrind \
				--leak-check=full  --show-leak-kinds=all \
				--track-origins=yes --verbose \
				--log-file=valgrind.txt ./$(T_NAME)


clean:
	@rm -rf $(TEMP_FILES)
	@echo "all cleaned"

clear: clean

cpplint:
	@echo "run cpplint.py"
	@cp $(CFGFILE) .
	@python3 ../materials/linters/cpplint.py  --extension=c $(SRCS) $(T_SRCS) *.c */*.c

cppcheck:
	@echo "run cppcheck"
	@cppcheck --enable=all --suppress=missingIncludeSystem $(SRCS) $(T_SRCS) *.c */*.c
