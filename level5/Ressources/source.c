void __noreturn o()
{
  system("/bin/sh");
  _exit(1);
}
// 80484A4: using guessed type void __noreturn o();

//----- (080484C2) --------------------------------------------------------
void __noreturn n()
{
  char s[520]; // [esp+10h] [ebp-208h] BYREF

  fgets(s, 512, stdin);
  printf(s);
  exit(1);
}

//----- (08048504) --------------------------------------------------------
int __cdecl __noreturn main(int argc, const char **argv, const char **envp)
{
  n();
}