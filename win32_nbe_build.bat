@echo off

REM ---------------------------------------------------------------------------
REM GCC/Clang Build
REM ---------------------------------------------------------------------------
REM
set DEF_COMPILER_FLAGS=-mconsole -march=native -mtune=native -std=c99 -pedantic -nodefaultlibs -nostdlib -mno-stack-arg-probe ^
-Xlinker /STACK:0x100000,0x100000 ^
-Xlinker /ENTRY:nostdlib_main ^
-fno-builtin -ffreestanding -fno-asynchronous-unwind-tables -fuse-ld=lld ^
-Wall -Wextra -Werror -Wvla -Wconversion -Wdouble-promotion -Wsign-conversion -Wmissing-field-initializers -Wuninitialized -Winit-self -Wunused -Wunused-macros -Wunused-local-typedefs

set DEF_FLAGS_LINKER=-lkernel32 -luser32 -lgdi32
set SOURCE=win32_nbe

REM ---------------------------------------------------------------------------
REM Build Targets
REM ---------------------------------------------------------------------------
cc -s -O2 %DEF_COMPILER_FLAGS% %SOURCE%.c -o %SOURCE%.exe %DEF_FLAGS_LINKER%

REM ---------------------------------------------------------------------------
REM Run
REM ---------------------------------------------------------------------------
%SOURCE%.exe
