# Colors
RED			= "\033[1;31m"
GREEN		= "\033[1;32m"
YELLOW		= "\033[1;33m"
BLUE		= "\033[1;34m"
NOCOLOR		= "\033[0m"

# Compiling MACROS
CXX			= g++
CC			= gcc
LIBS 		= -lSDL2 -lGL -lGLU -lGLEW
RM			= rm -f
RMR			= rm -rf
OBJECTS		= stb_image.o obj_loader.o display.o shader.o mesh.o texture.o main.o
COMPILE_CC 	= $(CC) -c $*.c
COMPILE_CXX	= $(CXX) -c $*.cpp

# Target
TARGET		= BVoxel

all: prompt $(TARGET) end

prompt:
	@echo $(YELLOW)Building Object Files ...$(NOCOLOR)

$(TARGET): $(OBJECTS)
	@echo $(YELLOW)
	@echo Linking Files ...$(NOCOLOR)
	$(CXX) $(OBJECTS) $(LIBS) -o $@
	@echo $(GREEN)
	@echo Successfully Compiled and Linked!
	@echo $(NOCOLOR)

stb_image.o: stb_image.c
	$(COMPILE_CC)

obj_loader.o: obj_loader.cpp
	$(COMPILE_CXX)

display.o: display.cpp
	$(COMPILE_CXX)

shader.o: shader.cpp
	$(COMPILE_CXX)

mesh.o: mesh.cpp
	$(COMPILE_CXX)

texture.o: texture.cpp
	$(COMPILE_CXX)

main.o: main.cpp
	$(COMPILE_CXX)

end:
	@echo $(BLUE)Cleaning and Moving Executable$(NOCOLOR)
	mv $(TARGET) ../
	$(RMR) *.o

clean:
	@echo $(BLUE)Cleaning and Removing Executable$(NOCOLOR)
	$(RMR) *.o
	$(RM) ../$(TARGET)
