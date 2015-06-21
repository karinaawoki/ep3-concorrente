All-in-One Makefile
=====================

[![Build Status](https://travis-ci.org/renatocf/make.svg?branch=master)]
                (https://travis-ci.org/renatocf/make)
[![License](https://img.shields.io/badge/license-Apache-blue.svg)]
           (https://github.com/renatocf/make/blob/master/LICENSE)

A single Makefile to compile all your projects: in C, C++, Assembly
and Fortran.

Tired of installing tools to compile your projects? (Automake, CMake
and Ant). Do you want to go back to the old days, when all you needed 
was typing `make`? Here is the solution! A single generalized Makefile 
which aims to compile and mix almost everything related to C, C++, 
Assembly and Fortran projects - with support to many executables, static
and shared libraries, lexer and parser generators, dependency management,
file creation and much more! Everything just 4 letters far from you.

## Starting ##

Good tools are simple. That's why `make` is so successful. And
that's the aim of AIO Makefile.

In order to start, just download the Makefile:

    curl -O https://raw.githubusercontent.com/renatocf/make/master/Makefile

To begin a new project, just type:

    make init

A group of directories and a git repository are now ready for you!

But how about configuring your project settings? `Config.mk` presents a
self-explanatory set of variables used by AIO Makefile to do all its
magic. And the best: everything within the own Make language - no 
extra parsers, neither extra programs. Just one single Makefile.

In order to make your very first compilation, just create a .c, .cpp,
.asm or .f (or any of the many source extensions avaiable) and set the 
variable `BIN` whith its name in Config.mk. Then  *voilà*: it will
compile everything perfectly (at least as perfect as your program...)

#### Single-directory projects ####

Do you have old single-directory code that is getting out of control? 
We also have a solution! `make standard` checks and separates your
files in our default directory structure. Improve your organization
(and use a great new tool) with almost no work!

#### Git submodule ####

To keep a copy of this project as a submodule, just clone it in your
working directory:

    git clone git@github.com:renatocf/make.git

Then, create a symbolic link:

    ln -s make/Makefile .

`make init` will automatically add it as a submodule.

## Makeballs ##

Using frameworks or libraries may be tricky, even with a simple-of-use
tool as AIO Makefile. We need to read documentations and find where
headers and libraries are located, in a world of complicated and no
standardized projects. So, why not to reuse these flags? `Makeballs` 
are meant for that!

To start using Makeballs, create a `conf` directory and download one
of the `conf/makeball.mk` avaiable. Then, add it in the end of 
`Config.mk`:

```make
...
# Makeball list
# ===============
include conf/makeball_1.mk
include conf/makeball_2.mk
```

If you cloned `make` to be used as a git submodule, all Makeballs are 
already avaiable for you! Just create a symbolic link:

    ln -s make/conf/ .

And include them as above.

#### Didn't find your favorite library? ####

Then just create you own `Makeball`! `conf/makeball.mk` provides the
most complete set of variables that could be used to add funcionalities
to AIO Makefile. Even better: make a pull request and **contribute**
reducing the work of others (and yourself) in the future.

## Administrative Issues ##

#### Getting the lastest version ####

To get the latest version, just type `make upgrade` and the newest 
Makefile will be automatically downloaded. If it is a submodule,
the same procedure will do it.

#### Portability ####

This Makefile is currently being tested under projects developed mainly
in C++ within Ubuntu Linux, Arch Linux and MAC OS X. Tests have already
been done in purely C and C/C++ projects. To report compatibility
problems, check the session below.

#### Bug report and Contributions ####

Any error or bug can be reported by opening an Issue. In order to 
contribute, make a pull request.

## More info ##

For all avaiable targets, type:

    make projecthelp

And it will print a list with all AIO Makefile avaiable options.
