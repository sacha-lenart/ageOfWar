CC = g++
CXXFLAGS = -std=c++11 -Wall
EXEC_NAME = ageOfWar
#SRC= $(wildcard *.cpp)
SRC = src/Archer.cpp src/Catapulte.cpp src/Configuration.cpp src/Fantassin.cpp src/Humain.cpp src/Joueur.cpp src/Plateau.cpp src/Soldat.cpp
CLASSES = $(SRC:.cpp=)
SRC += src/main.cpp
OBJ_FILES = $(SRC:.cpp=.o)

all : $(EXEC_NAME)

clean :
	rm $(OBJ_FILES)

mrproper : clean
	rm $(EXEC_NAME)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES)

%.o : %.cpp %.hpp
	$(CC) $(CXXFLAGS) -o $@ -c $<
