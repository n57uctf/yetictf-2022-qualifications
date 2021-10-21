#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

// Суть: изменить ход выполнения программы, перезаписав переменную определённым значением

void win()
{
  printf("YetiCTF{m45t3r_0f_f10w}\n");
}

int main(int argc, char **argv)
{
  volatile int (*fp)();
  printf("%s", "Hello, what do you think about code flow?\nFlag should be somewhere here!\nFind him!\n");
  char buffer[64];

  fp = 0;

  gets(buffer);

  if(fp) {
      printf("Hint: Jumping to 0x%08x\n !!!", fp);
      fp();
  }

  return 0;
}
