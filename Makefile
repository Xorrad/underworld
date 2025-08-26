################################
#        Configuration         #
################################

# Enable multi-threading
MAKEFLAGS += -j4

# Compiler flags
CXX      := g++
CXXFLAGS := -std=c++20 -pedantic-errors -Wall -Wno-format-security -Wno-sign-compare -Wno-unused-but-set-variable

# Build type (default, debug, release)
BUILD_TYPE := debug
ifeq ($(BUILD_TYPE),debug)
    CXXFLAGS += -O0 -DDEBUG -g
else ifeq ($(BUILD_TYPE),release)
    CXXFLAGS += -O3 -DNDEBUG
endif

# Executables to build (each must have a corresponding src/<name>.cpp)
TARGETS := main tests

# Directories
SRC_DIR     := src
INCLUDE_DIR := src
VENDOR_DIR  := vendor
BIN_DIR     := bin
OBJ_DIR     := bin/obj
INCLUDE     := -I$(INCLUDE_DIR) -I$(VENDOR_DIR)

# Sources and objects
SRC          := $(shell find $(SRC_DIR)/*/ -type f -name '*.cpp')
PCH_HEADER   := $(SRC_DIR)/pch.hpp
PCH        	 := $(OBJ_DIR)/pch.hpp.gch
OBJECTS        := $(SRC:%.cpp=$(OBJ_DIR)/%.o)
DEPENDENCIES   := $(OBJECTS:.o=.d) $(TARGETS:%=$(OBJ_DIR)/$(SRC_DIR)/%.d)

# Libraries
LDFLAGS :=  -L$(VENDOR_DIR)/fmt -lfmt \
			-L$(VENDOR_DIR)/backward/ -lbackward \
			-L/usr/lib -lstdc++ -lbfd -ldl -ldw

################################
#            Rules             #
################################

.PHONY: all clean
all: $(TARGETS:%=$(BIN_DIR)/%)

# Ensure build directory exists
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Ensure objects files are not automatically deleted by make
.SECONDARY: $(OBJECTS) $(TARGETS:%=$(OBJ_DIR)/$(SRC_DIR)/%.o)

# Precompiled header
$(PCH): $(PCH_HEADER) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -x c++-header $< -MMD -MP -o $@

# Compile src/**/*.cpp into obj/**/*.o
$(OBJ_DIR)/%.o: %.cpp $(PCH)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -MP -o $@ -include $(PCH_HEADER)
	
-include $(DEPENDENCIES)

# Compile target executables
$(BIN_DIR)/%: $(OBJ_DIR)/$(SRC_DIR)/%.o $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Alias for each target executable
$(TARGETS): % : $(BIN_DIR)/%
	@clear
	@./$^
	
################################
#          Utilities           #
################################

clean:
	@rm -rvf $(OBJ_DIR) $(BIN_DIR)/*

info:
	@echo "Targets: ${TARGETS}"
	@echo "Sources: ${SRC}"
	@echo "Application dir: ${BIN_DIR}"
	@echo "Object dir: ${OBJ_DIR}"
	@echo "Objects: ${OBJECTS}"
	@echo "Dependencies: ${DEPENDENCIES}"