# tool macros
CXX ?= c++
CXXFLAGS :=
DBGFLAGS := -g
OBJFLAGS := $(CFLAGS) -c

# path macros
BIN_PATH := build/bin
OBJ_PATH := build/obj
DBG_PATH := build/debug
SRC_PATH := src

# compile macros
TARGET_NAME := uttt

TARGET := $(BIN_PATH)/$(TARGET_NAME)
TARGET_DEBUG := $(DBG_PATH)/$(TARGET_NAME)

# src files & obj files
SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*, .cpp*)))
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
OBJ_DEBUG := $(addprefix $(DBG_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

# clean files list
DISTCLEAN_LIST := $(OBJ) \
                  $(OBJ_DEBUG)

CLEAN_LIST := $(TARGET) \
	      $(TARGET_DEBUG) \
	      $(DISTCLEAN_LIST)

# default rule
default: makedir all debug dist

# non-phony targets
$(TARGET): $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp*
	$(CC) $(OBJFLAGS) -o $@ $<

$(DBG_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CC) $(OBJFLAGS) $(DBGFLAGS) -o $@ $<

$(TARGET_DEBUG): $(OBJ_DEBUG)
	$(CC) $(CFLAGS) $(DBGFLAGS) $(OBJ_DEBUG) -o $@


.PHONY: makedir
makedir:
	@mkdir -p $(BIN_PATH) $(OBJ_PATH) $(DBG_PATH) $(DIST_PATH)

.PHONY: all
all: $(TARGET)

.PHONY: debug
debug: $(TARGET_DEBUG)

.PHONY: clean
clean:
	@echo CLEAN $(CLEAN_LIST)
	@rm -f $(CLEAN_LIST)

.PHONY: distclean
distclean:
	@echo CLEAN $(DISTCLEAN_LIST)
	@rm -f $(DISTCLEAN_LIST)


# Access to additional python scripts
VENV = .venv
PYTHON = $(VENV)/bin/python3
PIP = $(VENV)/bin/pip

COMMANDS := $(foreach x, $(wildcard scripts/commands/*.py), $(notdir $(basename $(x))))
PYCLEAN_LIST := scripts/commands/__pycache__

$(VENV):
	python -m venv $(VENV)

setup:
	$(PIP) install --upgrade -r scripts/requirements.txt

$(COMMANDS): $(VENV)/bin/activate
	@mkdir -p build/dist
	$(PYTHON) scripts/run.py $@

pyclean:
	@echo CLEAN $(PYCLEAN_LIST)
	@rm -rf $(PYCLEAN_LIST)
