###################################
# >>  COMPILER CONFIGURATION   << #
###################################
CXX := g++
CXXF:= -Wall -std=c++11 -O2 -fno-rtti



###################################
# >>          SOURCES          << #
###################################
TARGET  := bin/mmlab
SRCS    := $(wildcard src/*.cxx) \
					 $(wildcard src/L*/*.cxx)
OBJS    := $(patsubst src/%,build/obj/%,$(SRCS:.cxx=.o))
INCLUDE := include/



###################################
# >>     BUILD DIRECTORIES     << #
###################################
MD := mkdir
RD := rm -rf
OBJ_DIRS := $(sort $(dir $(OBJS)))
BUILD_DIRS := bin build
DIRS_TO_CREATE := $(BUILD_DIRS) $(OBJ_DIRS)
DIRS_TO_REMOVE := $(BUILD_DIRS)



###############################################################################
# >>                 PLATFORM SPECIFIC CONFIGURATIONS                      << #
###############################################################################

ifeq ($(OS),Windows_NT)
#----------------------------------------------------

	TARGET := $(TARGET).exe
	# >> SAFE CREATE & REMOVE DIRECTORIES IN WINDOWS >>
	#==================================================

	# Eliminate remove directory command
	# so it won't cause any error if there's nothing to remove
	RD :=
	
	# Filter dirs that need to be created
	#
	FOUND_DIRS     := $(wildcard $(DIRS_TO_CREATE))
	FILTERED       := $(filter-out $(FOUND_DIRS),$(DIRS_TO_CREATE))
	DIRS_TO_CREATE := $(subst /,\,$(FILTERED))

	# Filter dirs that need to be removed
	#
	FOUND_DIRS     := $(wildcard $(DIRS_TO_REMOVE))
	FILTERED       := $(filter $(FOUND_DIRS), $(DIRS_TO_REMOVE))
	DIRS_TO_REMOVE := $(subst /,\,$(FILTERED))


	#
	# * If there are some dirs to remove, initialize the remove command
	#
	ifneq (,$(DIRS_TO_REMOVE))
	#-----------------
		RD := rd /S /Q
	#-----------------
	endif

	#
	# * If we don't have anything to create, eliminate the "mkdir" command
	#
	ifeq (,$(DIRS_TO_CREATE))
	#-----------------
		MD :=
	#-----------------
	endif

	#==================================================

#----------------------------------------------------
endif

###############################################################################



##################################
# >>         TARGETS          << #
##################################
all: prep $(TARGET)
.PHONY: prep clean run



define print_header
	$(info )
	$(info ===================================)
  $(info * ${1})
	$(info ===================================)
	$(info )
endef


##################################
# >>          RULES           << #
##################################
#=============================
#     CREATE DIRECTORIES     #
#=============================
prep:
	@:
	@$(call print_header,CHECKING DIRECTORIES...)
	@$(MD) $(DIRS_TO_CREATE)


#=============================
#     CREATE EXECUTABLE      #
#=============================
$(TARGET): $(OBJS)
	@$(call print_header,CREATING EXECUTABLE...)
	$(CXX) $(CXXF) $^ -o $@


#=============================
#         PROCESS IRs        #
#=============================
.SECONDEXPANSION:
$(OBJS): $$(patsubst build/obj/%.o,src/%.cxx,$$@)
	$(info )
	$(info => CREATING IR)
	@$(info --------------------------------------)
	$(CXX) -I$(INCLUDE) -c -o $@ $<


#=============================
#             RUN            #
#=============================
run: $(TARGET)
	@$(TARGET) $(arg)



#=============================
#           CLEANUP          #
#=============================
clean:
	@:
	@$(call print_header,CLEANING UP...)
	@$(RD) $(DIRS_TO_REMOVE)
	@echo DONE!

