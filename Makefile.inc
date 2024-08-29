mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS += state.o
APPL_COBJS += linetrace.o
APPL_COBJS += 
APPL_COBJS += port.o
APPL_COBJS += 

APPL_LIBS += -lm

APPL_DIRS += $(mkfile_path)Apl
APPL_DIRS += $(mkfile_path)Mid
APPL_DIRS += $(mkfile_path)Drv
APPL_DIRS += $(mkfile_path)Cfg
APPL_DIRS += $(mkfile_path)Test

INCLUDES += -I$(mkfile_path)Apl
INCLUDES += -I$(mkfile_path)Mid
INCLUDES += -I$(mkfile_path)Drv
INCLUDES += -I$(mkfile_path)Cfg
INCLUDES += -I$(mkfile_path)Test
