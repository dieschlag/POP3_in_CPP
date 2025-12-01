# Nom de l'exécutable final
TARGET = tp2

# Drapeaux du compilateur
CXX = g++
CXXFLAGS = -std=c++17 -I. -Wall -Wextra

# Tous les fichiers source .cpp
SRCS = $(wildcard *.cpp)

# Fichiers objets générés à partir des sources
OBJS = $(SRCS:.cpp=.o)

# Règle par défaut
all: $(TARGET)

# Compilation de l'exécutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilation des fichiers .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
