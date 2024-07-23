mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS += motor_test.o

APPL_LIBS += -lm
APPL_DIRS += ver_R7/zoudatest
INCLUDES += ver_R7/zoudatest
