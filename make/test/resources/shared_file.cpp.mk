
############################################################
##     UNCOMMENT ANY TARGET TO OVERWRITE THE DEFAULT!     ##
############################################################

# Project info
# ===============
# PROJECT         := # Project name (def: Default)
# VERSION         := # Version (def: 1.0)
# GIT_REMOTE      := # Remote path for git repository
# MAINTEINER_NAME := # Your name
# MAINTEINER_MAIL := # your_name@mail.com
# COPYRIGHT       := # Copyright Holder
# SYNOPSIS        := # One-line description of the program
# DESCRIPTION     := # Longer description of the program

# Program settings
# ==================
BIN             := hello1 hello2 hello3
# ARLIB           := # Static/Shared libraries' names. If"
# SHRLIB          := # one is a dir, all srcs within will"
#                    # make the lib"

hello1_flags := \
    CXXFLAGS => -ansi -pedantic -Wall -O2

hello3_flags := \
    CXXFLAGS => -std=c++11 -O2

# Dependencies
# ==============
# GIT_DEPENDENCY  := # List of git dependencies in the format
#                    # DEP_NAME => dep_path                  
# WEB_DEPENDENCY  := # Same as above, but for URL downloads  
#                    # with 'curl -o' (default) or 'wget -O' 

# Paths
# =======
# ASLIBS          := # Assembly paths
# CLIBS           := # C paths
# CXXLIBS         := # C++ paths
# LDLIBS          := # Linker paths

# Flags
# =======
# CPPFLAGS        := # Precompiler Flags
# ASFLAGS         := # Assembly Flags
# CFLAGS          := # C Flags
# CXXFLAGS        := # C++ Flags
# LDFLAGS         := # Linker flags

# Documentation
# ===============
# LICENSE         := # File with a License (def: LICENSE)
# NOTICE          := # Notice of the License, to be put in 
#                    # the top of any file (def: NOTICE).
# DOXYFILE        := # Dxygen config file (def: Doxyfile)

