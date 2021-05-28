#ifndef LIB_H
#define LIB_H

int write(int fd, char* buffer, int length);
int read(int fd, char* buffer, int length);
int DateTime(int selector);
int getMem(unsigned char *buffer, unsigned long long address, int bytes);
int getReg(unsigned long long *array);
void Clear();
void opCodeExc();

#endif
