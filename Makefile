# Programs
CC     	= g++
RM 	= rm
ECHO	= echo
######################################
# Project Name (generate executable with this name)
TARGET = room

# Project Paths
PROJECT_DIR=./
TEXTURE_DIR=$(PROJECT_DIR)/textures 
SRC_DIR=$(PROJECT_DIR)/src
#Libraries
LIBS = -lglut -lGLU -lGL #-lsfml-audio -lsfml-system

SRC := $(wildcard $(SRC_DIR)/*.cpp)

all: $(PROJECT_DIR)/$(TARGET)

$(PROJECT_DIR)/$(TARGET): $(SRC) $(TEXTURE_DIR)/*
	@$(CC) -o $(TARGET) $(SRC_DIR)/main.cpp $(LIBS)	
	
clean:
	@$(ECHO) -n "Cleaning..."
	@$(RM) -rf $(TARGET) *~
	@$(ECHO) "Done"
