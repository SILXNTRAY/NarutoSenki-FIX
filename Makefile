PLATFORM ?= linux

define MAKE_TARGET
	+$(MAKE) -C cocos2dx/proj.$(PLATFORM) $@
	+$(MAKE) -C CocosDenshion/proj.$(PLATFORM) $@
	+$(MAKE) -C extensions/proj.$(PLATFORM) $@
	+$(MAKE) -C scripting/lua/proj.$(PLATFORM) $@
	+$(MAKE) -C projects/NarutoSenki/proj.$(PLATFORM) $@
endef

all:
	$(call MAKE_TARGET,all)

clean:
	$(call MAKE_TARGET,clean)

.PHONY: all clean
