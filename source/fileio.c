#include <main.h>

int getFileSize(const char *file)
{
    SceIoStat stat;
    int result = sceIoGetstat(file, &stat);
    if (result < 0)
        errorExit("Error getting file size for '%s': 0x%08x.", file, result);
    return stat.st_size;
}

int readFile(const char *file, char *buffer)
{
    SceUID fd = sceIoOpen(file, PSP_O_RDONLY, 0777);
    if (fd < 0)
        errorExit("Error opening file '%s' for reading: 0x%08x.", file, fd);

    int bytes = sceIoRead(fd, buffer, BUFFER_SIZE);
    sceIoClose(fd);

    if (bytes < 0)
        errorExit("Error reading file '%s': 0x%08x.", file, bytes);

    if (bytes < BUFFER_SIZE)
        buffer[bytes] = '\0';

    return bytes;
}

int writeFile(const char *file, const char *data, SceSize size)
{
    SceUID fd = sceIoOpen(file, PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
    if (fd < 0)
        errorExit("Error opening file '%s' for writing: 0x%08x.", file, fd);

    int bytes = sceIoWrite(fd, data, size);
    sceIoClose(fd);

    if (bytes < 0)
        errorExit("Error writing to file '%s': 0x%08x.", file, bytes);

    return bytes;
}

void copyFile(const char *file, const char *dstfile)
{
    int size = getFileSize(file);
    if (size < 0)
        errorExit("Error getting file size for '%s'.", file);

    char *buffer = malloc(size);
    if (!buffer)
        errorExit("Memory allocation failed for file copy.");

    int bytes = readFile(file, buffer);
    if (bytes < 0)
    {
        free(buffer);
        errorExit("Error reading file '%s'.", file);
    }

    if (writeFile(dstfile, buffer, bytes) < 0)
    {
        free(buffer);
        errorExit("Error writing to file '%s'.", dstfile);
    }

    free(buffer);
}

void removeFile(const char *file)
{
    int ret = sceIoRemove(file);
    if (ret < 0)
        errorExit("Error removing file '%s': 0x%08x.", file, ret);
}

void bin2File(const char *file, const char *data, size_t size)
{
    SceUID fd = sceIoOpen(file, PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
    if (fd < 0)
        errorExit("Error opening file '%s' for writing binary data: 0x%08x.", file, fd);

    int bytes = sceIoWrite(fd, data, size);
    if (bytes != size)
    {
        sceIoClose(fd);
        errorExit("Error writing binary data to file '%s': wrote %d bytes, expected %zu.", file, bytes, size);
    }

    sceIoClose(fd);
}

void convertVersion(const char *file, int version, char *result, size_t size)
{
    FILE *fp = fopen(file, "r");
    if (!fp)
        errorExit("Error opening file '%s' for version conversion.", file);

    char line[512];
    int current = 1;
    size_t bytes = 0;
    unsigned char value;

    while (fgets(line, sizeof(line), fp))
    {
        if (current == version)
        {
            for (size_t i = 0; i < strlen(line) - 1 && bytes < size - 1; i += 2)
            {
                if (sscanf(&line[i], "%2hhx", &value) == 1)
                    result[bytes++] = (char)value;
            }
            result[bytes] = '\0';
            break;
        }
        current++;
    }
    fclose(fp);

    if (current != version)
        errorExit("Version %d not found in file '%s'.", version, file);
}

void initFlash(void)
{
    int ret;
    ret = sceIoUnassign("flash0:");
    while (ret < 0)
    {
        sceKernelDelayThread(500000);
        ret = sceIoUnassign("flash0:");
    }

    ret = sceIoAssign("flash0:", "lflash0:0,0", "flashfat0:", 0, NULL, 0);
    if (ret < 0)
        errorExit("Error assigning flash0: 0x%08x", ret);

    ret = sceIoUnassign("flash1:");
    while (ret < 0)
    {
        sceKernelDelayThread(500000);
        ret = sceIoUnassign("flash1:");
    }

    ret = sceIoAssign("flash1:", "lflash0:0,1", "flashfat1:", 0, NULL, 0);
    if (ret < 0)
        errorExit("Error assigning flash1: 0x%08x", ret);
}