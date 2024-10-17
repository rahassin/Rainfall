
extern unsigned int m;
extern FILE_t *stdin;
extern FILE_t *stdout;

void v()
{
    char v0;  // [bp-0x20c]

    fgets(&v0, 0x200, stdin);
    printf(&v0);
    if (m == 64)
    {
        fwrite("Wait what?!\n", 1, 12, stdout);
        system("/bin/sh");
    }
    return;
}

int main()
{
    return (unsigned int)v();
}