CXX = clang++
CXXFLAGS = -std=c++11 -glldb
LIBS = -lgtest -lpthread -lcurses
 
ifeq ($(OS), Windows_NT)
    CXX = g++
    CXXFLAGS = -std=gnu++0x
    LIBS = -lgtest
endif

SOURCE_DIR = src
BUILD_DIR = build
EXE_FILE_DIR = .
EXE_FILE_NAME = main

SOURCES = $(wildcard $(SOURCE_DIR)/*.cpp)
OBJECTS = $(patsubst $(SOURCE_DIR)/%.cpp,$(BUILD_DIR)/%.o, $(SOURCES))
DEPENDS = ${OBJECTS:.o=.d}
 
all: preprocess $(OBJECTS)
	$(CXX) -o $(EXE_FILE_DIR)/$(EXE_FILE_NAME) $(OBJECTS) $(LIBS)

preprocess:
	mkdir -p $(BUILD_DIR)
	

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

-include ${DEPENDS}
 
clean:
	$(RM) $(EXE_FILE_DIR)/$(EXE_FILE_NAME)
	$(RM) $(BUILD_DIR)/*.d
	$(RM) $(BUILD_DIR)/*.o
 
test: all
	$(EXE_FILE_DIR)/$(EXE_FILE_NAME)
 
test.%: all
	$(EXE_FILE_DIR)/$(EXE_FILE_NAME) --gtest_filter=$(or $(word 2,$(subst ., ,$@)),$(value 2)).*