SHELL = /bin/sh
CXX := g++ -std=c++11 
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
INC_DIR := .
OUTPUTS_DIR := outputs
RESULTS_DIR := results


EXE := $(BIN_DIR)/movinghouse
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
#OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))


# let us check the operating system (Linux, Mac-Darwinuname) to define libs for linker
SYSTEM_UNAME := $(shell uname -s)
ifeq ($(SYSTEM_UNAME),Linux)
	LDLIBS := -lm -lGLU -lGL -lGLEW -lglfw 
endif
ifeq ($(SYSTEM_UNAME),Darwin)
	LDLIBS := -lm -framework OpenGL -L/opt/local/lib/ -lglm -lGLEW -lglfw
endif

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR) 
	$(CXX) $(CXXFLAGS) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR) $(OUTPUTS_DIR)/*.* $(RESULTS_DIR)/*.*

-include $(OBJ:.o=.d)

