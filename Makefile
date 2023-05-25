COMPILER = g++

BIN_DIR = bin
SRC_DIR = src
TMP_DIR = tmp

SRC_FOLDERS = $(shell find $(SRC_DIR) -type d)
TMP_FOLDERS = $(patsubst $(SRC_DIR)%, $(TMP_DIR)%, $(SRC_FOLDERS))

SRC_FILES = $(shell find $(SRC_DIR) -name "*.cpp")
TMP_FILES = $(patsubst $(SRC_DIR)%.cpp, $(TMP_DIR)%.o, $(SRC_FILES))

BINARY = $(BIN_DIR)/ctlg

COMPILER_FLAG = -std=c++20 -Wall -fno-rtti

LIB_FLAG = -L ~
HDR_FLAG = -I ~ $(addprefix -I $(CURDIR)/, $(SRC_FOLDERS))

release: COMPILER_FLAG += -O3
release: LIB_FLAG += -lncurses -ltinfo

debug: COMPILER_FLAG += -O0 -g
debug: LIB_FLAG += -lncurses -ltinfo

release debug: $(TMP_FOLDERS) $(BIN_DIR) $(BINARY)

$(BIN_DIR) $(TMP_FOLDERS):
	mkdir -p $@

clean:
	rm -f $(BINARY)
	rm -rf $(TMP_DIR)

$(BINARY): $(TMP_FILES)
	$(COMPILER) $^ -o $@ $(LIB_FLAG) $(COMPILER_FLAG)

$(TMP_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(COMPILER) -c $< -o $@ $(HDR_FLAG) $(COMPILER_FLAG)
