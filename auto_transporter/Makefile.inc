mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

SRCLANG := c

APPL_ASMOBJS :=
ifdef USE_CXX
	APPL_CXXOBJS +=
	APPL_COBJS += porter.o line_tracer.o linemon.o driver.o util.o timer.o bumper.o carrier.o wall_detector.o
else
	APPL_COBJS += porter.o line_tracer.o linemon.o driver.o util.o timer.o bumper.o carrier.o wall_detector.o
endif

APPL_DIRS += $(mkfile_path)app $(mkfile_path)unit $(mkfile_path)/../util
INCLUDES += \
	-I$(mkfile_path)app \
	-I$(mkfile_path)unit \
	-I$(mkfile_path)/../util
