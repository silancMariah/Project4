#!/bin/bash
make
killall jtagd
jtagd --user-start
/home/is1500/Downloads/dtekv-tools/dtekv-run /home/is1500/Downloads/time4riscv-7/time4riscv/main.bin
