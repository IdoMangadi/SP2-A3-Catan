#!make -f
# ID: 315310250
# EMAIL: IDOIZHAR.Mangadi@msmail.ariel.ac.il
# GMAIL: idomangadi@gmail.com

CXX = g++
CXXFLAGS = -std=c++11 -Werror -Wsign-conversion
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES = Player.cpp Card.cpp Board.cpp Controller.cpp Catan.cpp BoardElements.cpp Pieces.cpp
OBJECTS = $(subst .cpp,.o,$(SOURCES))

catan: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

valgrind: catan
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./catan 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o catan

cps:
	git commit -a -m "$(m)"
	git push
	git status