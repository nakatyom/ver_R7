mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS +=\
Log.o\

APPL_LIBS += -lm

APPL_DIRS += $(mkfile_path)Test

INCLUDES += \
	-I$(mkfile_path)Test\

