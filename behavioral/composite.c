#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum _FileType {
    Directory,
    File,
} FileType;

typedef struct _FileInfo {
    FileType type;
    char* name;
    int size;
    struct _FileInfo* children[32];
    int childCount;
    struct _FileInfo* parent;
} FileInfo;

void appendChild(FileInfo* self, FileInfo* child);

FileInfo* new_Directory(char* name);
FileInfo* new_File(char* name, char* content);

void _absolutePath(FileInfo* info);
void absolutePath(FileInfo* info);

void _ls(FileInfo* info, int depth);
void ls(FileInfo* info);

void delete_FileInfo(FileInfo* info);

int main(void) {
    FileInfo* rootDir = new_Directory("root");
    FileInfo* homeDir = new_Directory("home");
    FileInfo* fileD = new_File("fileD.txt", "this is a file D.");
    appendChild(rootDir, new_File("fileA.txt", "Hello, World!"));
    appendChild(rootDir, new_File("fileB.txt", "this is a file b."));
    appendChild(rootDir, homeDir);
    appendChild(homeDir, new_File("fileC.txt", "Hello, World!"));
    appendChild(homeDir, fileD);
    appendChild(homeDir, fileD);
    appendChild(homeDir, new_File("fileD.txt", "duplicate name."));
    appendChild(fileD, homeDir);

    ls(rootDir);
    ls(homeDir);
    ls(fileD);

    absolutePath(fileD);

    delete_FileInfo(rootDir);
    return 0;
}

void appendChild(FileInfo* self, FileInfo* child) {
    if (self->type == File) {
        printf("Error: Can't appendChild to File.\n");
        return;
    }
    for (int i = 0; i < self->childCount; i++) {
        if (self->children[i] == child) {
            printf("Error: File already added.\n");
            return;
        }
        if (strcmp(self->children[i]->name, child->name) == 0) {
            printf("Error: Duplicate file name.\n");
            return;
        }
    }
    self->children[self->childCount++] = child;
    child->parent = self;
    FileInfo* current = self;
    while (current != NULL) {
        current->size += child->size;
        current = current->parent;
    }
}

FileInfo* new_Directory(char* name) {
    FileInfo* directory = (FileInfo*)malloc(sizeof(FileInfo));
    directory->name = strdup(name);
    directory->size = 0;
    directory->type = Directory;
    directory->childCount = 0;
    directory->parent = NULL;
    return directory;
}

FileInfo* new_File(char* name, char* content) {
    FileInfo* file = (FileInfo*)malloc(sizeof(FileInfo));
    file->name = strdup(name);
    file->size = strlen(content);
    file->type = File;
    file->childCount = 0;
    file->parent = NULL;
    return file;
}

void _absolutePath(FileInfo* info) {
    if (info->parent != NULL) _absolutePath(info->parent);
    printf("/%s", info->name);
}
void absolutePath(FileInfo* info) {
    printf("absolute: ");
    _absolutePath(info);
    printf("\n");
}

void _ls(FileInfo* info, int depth) {
    for (int i=0; i<depth; i++) printf("  ");
    printf("L %s [%s] %d\n", info->name, info->type == File ? "F" : "D",  info->size);

    for (int i=0; i<info->childCount; i++) {
        _ls(info->children[i], depth + 1);
    }
}

void ls(FileInfo* info) {
    FileInfo* path[32];
    int pathIndex = 0;
    FileInfo* current = info->parent;
    while (current != NULL) {
        path[pathIndex++] = current;
        current = current->parent;
    }
    int empty = 1;
    for (int i=pathIndex-1; i>=0; i--) {
        printf("/%s", path[i]->name);
        empty = 0;
    }
    if (empty) printf("/");
    printf("\n");

    _ls(info, 0);
}

void delete_FileInfo(FileInfo* info) {
    for (int i=0; i<info->childCount; i++) {
        delete_FileInfo(info->children[i]);
    }
    free(info->name);
    free(info);
}
