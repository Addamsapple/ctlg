COMPILER = g++

HDR_DIR = ~
LIB_DIR = ~

BIN_DIR = bin
SRC_DIR = src
TMP_DIR = tmp

COMPILER_FLAG = -std=c++20 -Wall -O3

HDR_FLAG = -I "$(HDR_DIR)"
LIB_FLAG = -L "$(LIB_DIR)"

SRC_FILES = $(shell find $(SRC_DIR) -name "*.cpp" ! -name "*_t.cpp")
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(TMP_DIR)/%.o, $(SRC_FILES))

release: LIB_FLAG += -lncurses -ltinfo

debug: COMPILER_FLAG += -g
debug: LIB_FLAG += -lncurses_g -ltinfo_g

release debug: $(BIN_DIR) $(TMP_DIR) $(BIN_DIR)/ctlg

$(BIN_DIR) $(TMP_DIR):
	mkdir -p $@

$(BIN_DIR)/ctlg: $(OBJ_FILES)
	$(COMPILER) $^ -o $@ $(LIB_FLAG) $(COMPILER_FLAG)

#$(OBJ_FILES): $(SRC_DIR)/%.cpp
$(TMP_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(COMPILER) -c $< -o $@ $(HDR_FLAG) $(COMPILER_FLAG)
