
CXX = g++
CC = gcc

TOP_DIR = .


TARGET_EXE = unit_test

CXX_SOURCE += $(TOP_DIR)/test_matrix_multiply.cpp

EP_INC_DIR += -I$(TOP_DIR)/


OBJ_CPP := $(patsubst %.cpp, %.o, $(CXX_SOURCE))
OBJ_C := $(patsubst %.c, %.o, $(C_SOURCE))

DEFINE_MACRO := 

CPPFLAGS := -Wall -O3 -fpermissive -std=c++11 
CPPFLAGS += $(DEP_INC_DIR) $(DEFINE_MACRO) 
CFLAGS += $(DEP_INC_DIR) $(DEFINE_MACRO) 

$(TARGET_EXE):$(OBJ_CPP)$(OBJ_C)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o : %.cpp
	$(CXX) $(CPPFLAGS) -o $@ -c $< 

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $< 

clean:
	rm -rf $(OBJ_CPP) $(OBJ_C) $(TARGET_EXE)