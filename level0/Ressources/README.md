level0

first level of Rainfall
once connected we have
```
level0@RainFall:~$ ll
total 737
dr-xr-x---+ 1 level0 level0     60 Mar  6  2016 ./
dr-x--x--x  1 root   root      340 Sep 23  2015 ../
-rw-r--r--  1 level0 level0    220 Apr  3  2012 .bash_logout
-rw-r--r--  1 level0 level0   3530 Sep 23  2015 .bashrc     
-rwsr-x---+ 1 level1 users  747441 Mar  6  2016 level0*     
-rw-r--r--  1 level0 level0    675 Apr  3  2012 .profile  
```

if we try to execute level0
```
level0@RainFall:~$ ./level0
Segmentation fault (core dumped)
```

if we add an argument we have 

level0@RainFall:~$ ./level0 test
No !

if we decompiple the code we weel see

```
level0@RainFall:~$ gdb -q ./level0
Reading symbols from /home/user/level0/level0...(no debugging symbols found)...done.
(gdb) disassemble main
Dump of assembler code for function main:
   ;initialisation of the pile
   0x08048ec0 <+0>:     push   %ebp
   0x08048ec1 <+1>:     mov    %esp,%ebp
   0x08048ec3 <+3>:     and    $0xfffffff0,%esp     
   0x08048ec6 <+6>:     sub    $0x20,%esp
   ;reading arguments
   0x08048ec9 <+9>:     mov    0xc(%ebp),%eax       
   0x08048ecc <+12>:    add    $0x4,%eax
   0x08048ecf <+15>:    mov    (%eax),%eax
   0x08048ed1 <+17>:    mov    %eax,(%esp)
   ;comparison with 0x1a7 (423)
   0x08048ed4 <+20>:    call   0x8049710 <atoi>     
   0x08048ed9 <+25>:    cmp    $0x1a7,%eax
   0x08048ede <+30>:    jne    0x8048f58 <main+152> 
   ;condition equal 423
        ;strdup
        0x08048ee0 <+32>:    movl   $0x80c5348,(%esp)    
        0x08048ee7 <+39>:    call   0x8050bf0 <strdup> 
        ;getegid and deteuid
        0x08048eec <+44>:    mov    %eax,0x10(%esp)      
        0x08048ef0 <+48>:    movl   $0x0,0x14(%esp)      
        0x08048ef8 <+56>:    call   0x8054680 <getegid>
        0x08048efd <+61>:    mov    %eax,0x1c(%esp)      
        0x08048f01 <+65>:    call   0x8054670 <geteuid>  
        0x08048f06 <+70>:    mov    %eax,0x18(%esp)      
        ;setresgid and setresuid
        0x08048f0a <+74>:    mov    0x1c(%esp),%eax      
        0x08048f0e <+78>:    mov    %eax,0x8(%esp)       
        0x08048f12 <+82>:    mov    0x1c(%esp),%eax      
        0x08048f16 <+86>:    mov    %eax,0x4(%esp)       
        0x08048f1a <+90>:    mov    0x1c(%esp),%eax      
        0x08048f1e <+94>:    mov    %eax,(%esp)
        0x08048f21 <+97>:    call   0x8054700 <setresgid>
        0x08048f26 <+102>:   mov    0x18(%esp),%eax      
        0x08048f2a <+106>:   mov    %eax,0x8(%esp)       
        0x08048f2e <+110>:   mov    0x18(%esp),%eax      
        0x08048f32 <+114>:   mov    %eax,0x4(%esp)       
        0x08048f36 <+118>:   mov    0x18(%esp),%eax      
        0x08048f3a <+122>:   mov    %eax,(%esp)
        0x08048f3d <+125>:   call   0x8054690 <setresuid>
        ;exec
        0x08048f42 <+130>:   lea    0x10(%esp),%eax      
        0x08048f46 <+134>:   mov    %eax,0x4(%esp)       
        0x08048f4a <+138>:   movl   $0x80c5348,(%esp)
        0x08048f51 <+145>:   call   0x8054640 <execv>
        0x08048f56 <+150>:   jmp    0x8048f80 <main+192>
   ;condition not equal 423
        ;fwrite
        0x08048f58 <+152>:   mov    0x80ee170,%eax
        0x08048f5d <+157>:   mov    %eax,%edx
        0x08048f5f <+159>:   mov    $0x80c5350,%eax
        0x08048f64 <+164>:   mov    %edx,0xc(%esp)
        0x08048f68 <+168>:   movl   $0x5,0x8(%esp)
        0x08048f70 <+176>:   movl   $0x1,0x4(%esp)
        0x08048f78 <+184>:   mov    %eax,(%esp)
        0x08048f7b <+187>:   call   0x804a230 <fwrite>
   ;reutrn (0) 
   0x08048f80 <+192>:   mov    $0x0,%eax
   0x08048f85 <+197>:   leave
   0x08048f86 <+198>:   ret
End of assembler dump.
```

the programe segfault without argument because atoi read invalid memory
``` 
    nb = atoi(av[1]);
```

this ligne weel swap the effctiv group id (EGID) and the  effctiv user (UGID)id 
and the permission of EGID and UGID 

```
    cmd_args[0] = strdup("/bin/sh");
    cmd_args[1] = NULL;

    gid = getegid();
    uid = geteuid();
    setresgid(gid, gid, gid);
    setresuid(uid, uid, uid);

    execv("/bin/sh", cmd_args);

```

Explication:
level0 have the uid of level1
```
-rwsr-x---+ 1 level1 users  747441 Mar  6  2016 level0*
```
the permission of this file is owned by level1
when we execute ./level0 423 we weel have the permission of level1 
```
level0@RainFall:~$ ./level0 423
$ whoami
level1
```

the flag is 
```
$ cat /home/user/level1/.pass
1fe8a524fa4bec01ca4ea21fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
```