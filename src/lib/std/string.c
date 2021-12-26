#include "string.h"

int strlen(char *str)
{
  int i = 0;
  while (str[i] != '\0')
  {
    i++;
  }
  return i;
}

int strcmp(char *str1, char *str2)
{
  if (strlen(str1) != strlen(str2))
  {
    return 0;
  }

  for (int i = 0; i < strlen(str1); i++)
  {
    if (str1[i] != str2[i])
    {
      return 0;
    }
  }

  return 1;
}

void strrev(char *str)
{
  int c, i, j;
  for (i = 0, j = strlen(str) - 1; i < j; i++, j--)
  {
    c = str[i];
    str[i] = str[j];
    str[j] = c;
  }
}

void strappend(char *str, char ch)
{
  int len = strlen(str);
  str[len] = ch;
  str[len + 1] = '\0';
}

int strrm(char *str)
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

void its(char *str, int n)
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

char tolower(char ch)
{
  if (ch >= 'A' && ch <= 'Z')
  {
    ch += 32;
  }
  return ch;
}

char toupper(char ch)
{
  if (ch >= 'a' && ch <= 'z')
  {
    ch -= 32;
  }
  return ch;
}
