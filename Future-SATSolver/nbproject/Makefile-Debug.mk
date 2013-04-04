#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Source/Parser.o \
	${OBJECTDIR}/Source/main.o \
	${OBJECTDIR}/Source/BitVector.o \
<<<<<<< HEAD
=======
	${OBJECTDIR}/Source/SimulatedAnnealingAlgorithm.o \
>>>>>>> tobias
	${OBJECTDIR}/Source/SolvObject.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-O3
CXXFLAGS=-O3

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/future-satsolver

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/future-satsolver: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/future-satsolver ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/Source/Parser.o: Source/Parser.cpp 
	${MKDIR} -p ${OBJECTDIR}/Source
	${RM} $@.d
<<<<<<< HEAD
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/Parser.o Source/Parser.cpp
=======
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/Parser.o Source/Parser.cpp
>>>>>>> tobias

${OBJECTDIR}/Source/main.o: Source/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/Source
	${RM} $@.d
<<<<<<< HEAD
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/main.o Source/main.cpp
=======
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/main.o Source/main.cpp
>>>>>>> tobias

${OBJECTDIR}/Source/BitVector.o: Source/BitVector.cpp 
	${MKDIR} -p ${OBJECTDIR}/Source
	${RM} $@.d
<<<<<<< HEAD
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/BitVector.o Source/BitVector.cpp
=======
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/BitVector.o Source/BitVector.cpp

${OBJECTDIR}/Source/SimulatedAnnealingAlgorithm.o: Source/SimulatedAnnealingAlgorithm.cpp 
	${MKDIR} -p ${OBJECTDIR}/Source
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/SimulatedAnnealingAlgorithm.o Source/SimulatedAnnealingAlgorithm.cpp
>>>>>>> tobias

${OBJECTDIR}/Source/SolvObject.o: Source/SolvObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/Source
	${RM} $@.d
<<<<<<< HEAD
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/SolvObject.o Source/SolvObject.cpp
=======
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/SolvObject.o Source/SolvObject.cpp
>>>>>>> tobias

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/future-satsolver

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
