#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct _File {
    char* fileName;
} File;

typedef struct _FileProxy {
    File* cache[16];
    int cacheCount;
    File* (*readFile)(struct _FileProxy* self, char* filename);
    int (*findCache)(struct _FileProxy* self, char* filename);
} FileProxy;

File* readFile(struct _FileProxy* self, char* filename);
int findCache(struct _FileProxy* self, char* filename);
FileProxy* new_FileProxy(void);
void delete_FileProxy(struct _FileProxy* proxy);

int main(void) {
    FileProxy* proxy = new_FileProxy();
    proxy->readFile(proxy, "fileA.txt");
    proxy->readFile(proxy, "fileA.txt");
    proxy->readFile(proxy, "fileB.txt");

    delete_FileProxy(proxy);

    return 0;
}

File* readFile(struct _FileProxy* self, char* filename) {
    int foundIndex = self->findCache(self, filename);
    if (foundIndex != -1) {
        printf("read from cache. %s\n", filename);
        return self->cache[foundIndex];
    }
    printf("Waiting for...(3seconds)\n");
    sleep(3);
    File* file = (File*)malloc(sizeof(File));
    file->fileName = strdup(filename);
    self->cache[self->cacheCount++] = file;
    printf("read. %s\n", filename);
    return file;
}

int findCache(struct _FileProxy* self, char* filename) {
    for (int i=0; i<self->cacheCount; i++) {
        if (strcmp(self->cache[i]->fileName, filename) == 0) {
            return i;
        }
    }
    return -1;
}

FileProxy* new_FileProxy(void) {
    FileProxy* fileProxy = (FileProxy*)malloc(sizeof(FileProxy));
    fileProxy->cacheCount = 0;
    fileProxy->readFile = readFile;
    fileProxy->findCache = findCache;
    return fileProxy;
}

void delete_FileProxy(struct _FileProxy* proxy) {
    for (int i=0; i<proxy->cacheCount; i++) {
        free(proxy->cache[i]->fileName);
        free(proxy->cache[i]);
    }
    free(proxy);
}
