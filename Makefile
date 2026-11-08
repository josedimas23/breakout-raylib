# Breakout · raylib
#   make        build ./breakout
#   make run    build and launch the game
#   make clean  remove build output

CXX      ?= c++
CXXFLAGS ?= -std=c++17 -O2
RAYLIB_CFLAGS := $(shell pkg-config --cflags raylib 2>/dev/null)
RAYLIB_LIBS   := $(shell pkg-config --libs raylib 2>/dev/null || echo -lraylib)

TARGET  := breakout
SRCS    := breakout.cpp Particula.cpp ConjuntoParticulas.cpp Pintar.cpp
OBJDIR  := build
OBJS    := $(SRCS:%.cpp=$(OBJDIR)/%.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(RAYLIB_LIBS) -o $@

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(RAYLIB_CFLAGS) -MMD -MP -c $< -o $@

$(OBJDIR):
	mkdir -p $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJDIR) $(TARGET)

-include $(OBJS:.o=.d)
