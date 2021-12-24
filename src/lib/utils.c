#include "utils.h"

void memcpy(uint8_t *source, uint8_t *dest, uint32_t nbytes)
{
  for (int i = 0; i < nbytes; i++)
  {
    *(dest + i) = *(source + i);
  }
}

int strlen(char str[])
{
  int i = 0;
  while (str[i] != '\0')
  {
    i++;
  }
  return i;
}

void strrev(char str[])
{
  int c, i, j;
  for (i = 0, j = strlen(str) - 1; i < j; i++, j--)
  {
    c = str[i];
    str[i] = str[j];
    str[j] = c;
  }
}

void its(int n, char str[])
{
  int i, sign;
  if ((sign = n) < 0)
    n = -n;
  i = 0;
  do
  {
    str[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);

  if (sign < 0)
    str[i++] = '-';
  str[i] = '\0';

  strrev(str);
}

void append(char str[], char n)
{
  int len = strlen(str);
  str[len] = n;
  str[len + 1] = '\0';
}

int backspace(char str[])
{
  int len = strlen(str);
  if (len > 0)
  {
    str[len - 1] = '\0';
    return 1;
  }
  else
  {
    return 0;
  }
}
