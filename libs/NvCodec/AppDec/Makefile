include ../common.mk

LDFLAGS += -lnvcuvid
LDFLAGS += $(shell pkg-config --libs libavcodec libavutil libavformat)

all: build

build: AppDec

NvDecoder.o: ../NvCodec/NvDecoder/NvDecoder.cpp ../NvCodec/NvDecoder/NvDecoder.h
	$(GCC) $(CCFLAGS) $(INCLUDES) -o $@ -c $<

AppDec.o: AppDec.cpp ../NvCodec/NvDecoder/NvDecoder.h \
		  ../Utils/NvCodecUtils.h ../Utils/Logger.h
	$(GCC) $(CCFLAGS) $(INCLUDES) -o $@ -c $<

AppDec: AppDec.o NvDecoder.o 
	$(GCC) $(CCFLAGS) -o $@ $^ $(LDFLAGS)

clean: 
	$(RM) -rf AppDec AppDec.o NvDecoder.o 
