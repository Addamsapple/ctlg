COMPILER = g++

HDR_DIR = ~
LIB_DIR = ~

BIN_DIR = bin
SRC_DIR = src
TMP_DIR = tmp

COMPILER_FLAG = -std=c++20 -Wall -O3

HDR_FLAG = -I "$(HDR_DIR)"
LIB_FLAG = -L "$(LIB_DIR)" -lncurses

ctlg: $(BIN_DIR) $(TMP_DIR) $(BIN_DIR)/ctlg

$(BIN_DIR) $(TMP_DIR):
	mkdir -p $@

$(BIN_DIR)/ctlg: $(TMP_DIR)/main.o $(TMP_DIR)/interface.o $(TMP_DIR)/render.o $(TMP_DIR)/navigate.o $(TMP_DIR)/resize.o  $(TMP_DIR)/io.o $(TMP_DIR)/processor.o $(TMP_DIR)/matcher.o $(TMP_DIR)/token.o $(TMP_DIR)/commands.o $(TMP_DIR)/command_proc.o $(TMP_DIR)/catalogue.o $(TMP_DIR)/item.o $(TMP_DIR)/type_proc.o $(TMP_DIR)/field.o $(TMP_DIR)/number.o
	$(COMPILER) $^ -o $@ $(LIB_FLAG) $(COMPILER_FLAG)

$(TMP_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(COMPILER) -c $< -o $@ $(HDR_FLAG) $(COMPILER_FLAG)
