# Buffer-overflow-attack-Return-to-libc

Execute the commands in order to reproduce the Return-to-libc buffer overflow attack (Linux terminal):

sudo sysctl -w kernel.randomize_va_space=0

sudo gcc -m32 -fno-stack-protector -z noexecstack -o exploit exploit.c

cat vulnerable.c

sudo gcc -m32 -fno-stack-protector -z noexecstack -o vulnerable vulnerable.c

export MYSHELL=/bin/sh

env | grep MYSHELL

gdb vulnerable

./exploit

./vulnerable
