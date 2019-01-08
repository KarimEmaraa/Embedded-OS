## Description
This is my step by step creating Embedded OS following ***Embedded and Real Time Operating Systems By KC Wang*** book.
Using **qemu-system-arm** for hardware simulation, **gnu toolchain for arm**  and  using 2 development platforms **Realview-pbx-a9** and **Versatile-epb**

## Details

**makefile** contains * *MACHINE* * to select between the two developoment platforms.
             contains * *OBJS* * to specify all .c and .s files to be compiled and linked.

## Build sequence
* *make build* builds all files and outputs the final executable.
* *make run* runs the executable on qemu vm.
* *make clean* deletes all object file and executables.
**Note** There is also specific rules for preproccessing, assembling and linking.
