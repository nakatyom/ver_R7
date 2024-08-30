mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS += 
APPL_COBJS += odometry.o
APPL_COBJS += 
APPL_COBJS += body.o port.o
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
