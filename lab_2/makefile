COMPILER_NAME := g++
CPPFLAGS := -std=c++20 -Wall -Wextra -Wpedantic

app.exe: main.cpp list/list.h list/list.hpp list/base_list.h list/base_list.hpp list/node.hpp list/list_concepts.h exception/exceptions.cpp exception/exceptions.h  iterator/base_iterator.h iterator/base_iterator.hpp iterator/const_iterator.h iterator/const_iterator.hpp iterator/iterator.h iterator/iterator.hpp
	$(COMPILER_NAME) $(CPPFLAGS) main.cpp exception/exceptions.cpp -o app.exe

.PHONY: clean

clean:
	rm -f *.o
	rm -f *.exe