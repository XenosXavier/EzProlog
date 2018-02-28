CXX = clang++
CXXFLAGS = -std=c++11 -glldb
LIBS = -lgtest -lpthread
 
ifeq ($(OS), Windows_NT)
    CXX = g++
    CXXFLAGS = -std=gnu++0x
    LIBS = -lgtest
endif

SOURCE_DIR = src
BUILD_DIR = build
EXE_FILE_DIR = .
EXE_FILE_NAME = ezProlog
TEST_FILE_DIR = .
TEST_FILE_NAME = ezPrologTest

SOURCES = $(wildcard $(SOURCE_DIR)/*.cpp)
OBJECTS = $(patsubst $(SOURCE_DIR)/%.cpp,$(BUILD_DIR)/%.o, $(SOURCES))
DEPENDS = ${OBJECTS:.o=.d}
TEST_OBJECTS = $(filter-out $(BUILD_DIR)/$(EXE_FILE_NAME).o, $(OBJECTS))
EXE_OBJECTS = $(filter-out $(BUILD_DIR)/$(TEST_FILE_NAME).o, $(OBJECTS))

all: setup program unit-test

setup:
	mkdir -p $(BUILD_DIR)

program: $(EXE_OBJECTS)
	$(CXX) -o $(EXE_FILE_DIR)/$(EXE_FILE_NAME) $(EXE_OBJECTS) $(LIBS)

unit-test: $(TEST_OBJECTS)
	$(CXX) -o $(TEST_FILE_DIR)/$(TEST_FILE_NAME) $(TEST_OBJECTS) $(LIBS)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

-include ${DEPENDS}
 
clean:
	$(RM) $(EXE_FILE_DIR)/$(EXE_FILE_NAME)
	$(RM) $(TEST_FILE_DIR)/$(TEST_FILE_NAME)
	$(RM) $(BUILD_DIR)/*.d
	$(RM) $(BUILD_DIR)/*.o
 
test: all
	$(TEST_FILE_DIR)/$(TEST_FILE_NAME)
 
test.%: all
	$(TEST_FILE_DIR)/$(TEST_FILE_NAME) --gtest_filter=$(word 2, $(subst ., ,$@)).*