# mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))
# 
# APPL_COBJS +=\
# 
# APPL_LIBS += -lm
# APPL_DIRS += zoudatest\
# INCLUDES += zoudatest\


###############

mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))
 
APPL_COBJS +=\
list_api.o\
 
APPL_LIBS += -lm
APPL_DIRS += 
INCLUDES += \