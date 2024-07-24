mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS +=\
color_sensor.o\
port_settings.o\
ultrasonic_sensor.o\
gyro_sensor.o

APPL_LIBS += -lm
APPL_DIRS += $Drv\
    $Mid
INCLUDES += \
    -I$Drv\
    -I$Mid