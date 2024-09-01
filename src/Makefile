CXX = g++
STD = -std=c++17
CXXFLAGS = -Wall -Werror -Wextra
LINKER_OPTIONS = -lgtest

WSL_LINK_FLAGS = -lsubunit `pkg-config --cflags --libs check`

S21_LIB = s21_calc.a
PATH_BACK = smart_calc/back/
PATH_FRONT = smart_calc/front/
PATH_SMART_CALC = smart_calc/
CC_FILES = $(wildcard smart_calc/back/s21_*.cc)
OBJ_FILES = $(patsubst %.cc, %.o, $(CC_FILES))

TEST_CC_FILES = $(wildcard tests.cc)
TEST_OBJ_FILES = $(patsubst %.cc, %.o, $(TEST_CC_FILES))

TRASH = $(wildcard *.o *.a *.gc* *.out *.tar Documentation html latex tests test.info report $(PATH_BACK)*.o )


all: install

install: $(S21_LIB)
	rm -rf calc_app
	mkdir calc_app
	cd calc_app; cmake ../smart_calc
	cd calc_app && make

uninstall: clean
	rm -rf smart_calc/CMakeLists.txt.user
	rm -rf smart_calc/build
	rm -rf calc_app

dist: clean uninstall
	rm -rf archive_calc
	mkdir archive_calc
	mkdir archive_calc/src
	cp -r ../*.md Makefile tests.cc Doxyfile smart_calc archive_calc/src
	cd ../ && cp -r materials src/archive_calc
	tar cvzf archive_calc.tar archive_calc/
	rm -rf archive_calc

dvi:
	rm -rf Documentation
	doxygen
	open Documentation/html/index.html

open:
	./calc_app/smart_calc.app/Contents/MacOS/smart_calc

clean:
	rm -rf $(TRASH)

rebuild: clean all

$(S21_LIB): $(OBJ_FILES)
	ar rc $(S21_LIB) $(OBJ_FILES)
	ranlib $(S21_LIB)
	rm -f $(BACK_P)*.o

tests: clean $(S21_LIB)
ifeq ($(shell uname -s), Linux)
	$(CXX) $(STD) $(CXXFLAGS) -c $(TEST_CC_FILES) $(LINKER_OPTIONS) $(WSL_LINK_FLAGS) -lm
	$(CXX) $(STD) $(CXXFLAGS) $(TEST_OBJ_FILES) $(S21_LIB) -o tests $(LINKER_OPTIONS) $(WSL_LINK_FLAGS) -lm
	./tests
else
	$(CXX) $(STD) $(CXXFLAGS) $(TEST_CC_FILES) $(S21_LIB) $(LINKER_OPTIONS) -o tests
	./tests
endif

gcov_report:
ifeq ($(shell uname -s), Linux)
	$(CXX) $(STD) --coverage $(CC_FILES) $(S21_LIB) $(TEST_CC_FILES) $(LINKER_OPTIONS) $(WSL_LINK_FLAGS) -o tests
else
	$(CXX) $(STD) --coverage $(CC_FILES) $(S21_LIB) $(TEST_CC_FILES) $(LINKER_OPTIONS) -o tests
endif
	./tests
	lcov -t "test" --no-external -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

check_style:
	cp ../materials/linters/.clang-format ../src
	clang-format -n -style=google *.cc $(PATH_BACK)*.cc $(PATH_BACK)*.h $(PATH_FRONT)*.cc $(PATH_FRONT)*.h $(PATH_SMART_CALC)*.cc $(PATH_SMART_CALC)*.h
	rm -rf .clang-format

correct_style:
	cp ../materials/linters/.clang-format ../src
	clang-format -i -style=google *.cc $(PATH_BACK)*.cc $(PATH_BACK)*.h $(PATH_FRONT)*.cc $(PATH_FRONT)*.h  $(PATH_SMART_CALC)*.cc $(PATH_SMART_CALC)*.h
	rm -rf .clang-format


check_leaks: clean tests
ifeq ($(shell uname -s), Linux)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./tests
else
	leaks -atExit -- ./tests
endif
