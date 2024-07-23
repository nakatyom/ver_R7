mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS += motor_test.o

APPL_LIBS += -lm
# APPL_DIRS += zoudatest
# INCLUDES += zoudatest

APPL_DIRS += $(mkfile_path)
INCLUDES += $(mkfile_path)
