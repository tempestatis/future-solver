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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Source/VNDO.o \
	${OBJECTDIR}/Source/ILS.o \
	${OBJECTDIR}/Source/Parser.o \
	${OBJECTDIR}/Source/main.o \
	${OBJECTDIR}/Source/BitVector.o \
	${OBJECTDIR}/Source/anyoption.o \
	${OBJECTDIR}/Source/UnsatChecker.o \
	${OBJECTDIR}/Source/SimulatedAnnealingOriginal.o \
	${OBJECTDIR}/Source/SolvObject.o \
	${OBJECTDIR}/Source/SimulatedAnnealingLessFlips.o \
	${OBJECTDIR}/Source/VNDF.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

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

${OBJECTDIR}/Source/VNDO.o: Source/VNDO.cpp 
	${MKDIR} -p ${OBJECTDIR}/Source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/VNDO.o Source/VNDO.cpp

${OBJECTDIR}/Source/ILS.o: Source/ILS.cpp 
	${MKDIR} -p ${OBJECTDIR}/Source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/ILS.o Source/ILS.cpp

${OBJECTDIR}/Source/Parser.o: Source/Parser.cpp 
	${MKDIR} -p ${OBJECTDIR}/Source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/Parser.o Source/Parser.cpp

${OBJECTDIR}/Source/main.o: Source/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/Source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/main.o Source/main.cpp

${OBJECTDIR}/Source/BitVector.o: Source/BitVector.cpp 
	${MKDIR} -p ${OBJECTDIR}/Source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/BitVector.o Source/BitVector.cpp

${OBJECTDIR}/Source/anyoption.o: Source/anyoption.cpp 
	${MKDIR} -p ${OBJECTDIR}/Source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/anyoption.o Source/anyoption.cpp

${OBJECTDIR}/Source/UnsatChecker.o: Source/UnsatChecker.cpp 
	${MKDIR} -p ${OBJECTDIR}/Source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/UnsatChecker.o Source/UnsatChecker.cpp

${OBJECTDIR}/Source/SimulatedAnnealingOriginal.o: Source/SimulatedAnnealingOriginal.cpp 
	${MKDIR} -p ${OBJECTDIR}/Source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/SimulatedAnnealingOriginal.o Source/SimulatedAnnealingOriginal.cpp

${OBJECTDIR}/Source/SolvObject.o: Source/SolvObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/Source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/SolvObject.o Source/SolvObject.cpp

${OBJECTDIR}/Source/SimulatedAnnealingLessFlips.o: Source/SimulatedAnnealingLessFlips.cpp 
	${MKDIR} -p ${OBJECTDIR}/Source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/SimulatedAnnealingLessFlips.o Source/SimulatedAnnealingLessFlips.cpp

${OBJECTDIR}/Source/VNDF.o: Source/VNDF.cpp 
	${MKDIR} -p ${OBJECTDIR}/Source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/VNDF.o Source/VNDF.cpp

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
