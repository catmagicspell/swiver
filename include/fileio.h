#ifndef FILEIO_H
#define FILEIO_H

void initFlash(void);
int getFileSize(const char *file);
void removeFile(const char *file);
int readFile(const char *file, char *buffer);
void copyFile(const char *file, const char *dstfile);
void bin2File(const char *file, const char *data, size_t size);
int writeFile(const char *file, const char *data, SceSize size);
void convertVersion(const char *file, int version, char *result, size_t size);
#endif