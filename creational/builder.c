#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Document {
    char* header;
    char* body;
} Document;

typedef struct _Builder {
    char* (*makeHeader)(struct _Builder* self, char* title);
    char* (*makeBody)(struct _Builder* self, char* body);
} Builder;

typedef struct _HTMLBuilder {
    Builder base;
} HTMLBuilder;

char* makeHTMLHeader(struct _Builder* self, char* title);
char* makeHTMLBody(struct _Builder* self, char* body);

typedef struct _MarkDownBuilder {
    Builder base;
} MarkDownBuilder;

char* makeMDHeader(struct _Builder* self, char* title);
char* makeMDBody(struct _Builder* self, char* body);

typedef struct _Editor {
    Document* document;
    Builder* builder;
    void (*setTitle)(struct _Editor* self, char* title);
    void (*setContent)(struct _Editor* self, char* content);
    void (*construct)(struct _Editor* self, char* title, char* content);
    void (*render)(struct _Editor* self);
} Editor;
void setTitle(struct _Editor* self, char* title);
void setContent(struct _Editor* self, char* content);
void construct(struct _Editor* self, char* title, char* content);
void render(struct _Editor* self);
Editor* new_Editor(Builder* builder);
void delete_Editor(Editor* editor);

int main(void) {
    HTMLBuilder HTMLbuilder = { { makeHTMLHeader, makeHTMLBody } };
    MarkDownBuilder MDbuilder = { { makeMDHeader, makeMDBody } };
    Editor* HTMLEditor = new_Editor((Builder*)&HTMLbuilder);
    HTMLEditor->construct(HTMLEditor, "Hello HTML!", "This is a HTML text!");
    HTMLEditor->render(HTMLEditor);
    delete_Editor(HTMLEditor);

    Editor* MDEditor = new_Editor((Builder*)&MDbuilder);
    MDEditor->construct(MDEditor, "Hello MD!", "This is a markdown text!");
    MDEditor->render(MDEditor);
    delete_Editor(MDEditor);
    return 0;
}

char* makeHTMLHeader(struct _Builder* self, char* title) {
    char* header = (char*)malloc(strlen(title) + strlen("<h1></h1>") + 1);
    sprintf(header, "<h1>%s</h1>", title);
    return header;
}

char* makeHTMLBody(struct _Builder* self, char* body) {
    char* content = (char*)malloc(strlen(body) + strlen("<p></p>") + 1);
    sprintf(content, "<p>%s</p>", body);
    return content;
}

char* makeMDHeader(struct _Builder* self, char* title) {
    char* header = (char*)malloc(strlen(title) + 3);
    sprintf(header, "# %s", title);
    return header;
}

char* makeMDBody(struct _Builder* self, char* body) {
    char* content = (char*)malloc(strlen(body) + 1);
    sprintf(content, "%s", body);
    return content;
}

void setTitle(struct _Editor* self, char* title) {
    self->document->header = self->builder->makeHeader(self->builder, title);
}

void setContent(struct _Editor* self, char* content) {
    self->document->body = self->builder->makeBody(self->builder, content);
}

void construct(struct _Editor* self, char* title, char* content) {
    self->setTitle(self, title);
    self->setContent(self, content);
}

void render(struct _Editor* self) {
    printf("%s\n%s\n", self->document->header, self->document->body);
}

Editor* new_Editor(Builder* builder) {
    Editor* editor = (Editor*)malloc(sizeof(Editor));
    editor->builder = builder;
    editor->document = (Document*)malloc(sizeof(Document));
    editor->document->header = NULL;
    editor->document->body = NULL;
    editor->setTitle = setTitle;
    editor->setContent = setContent;
    editor->construct = construct;
    editor->render = render;
    return editor;
}
void delete_Editor(Editor* editor) {
    free(editor->document->header);
    free(editor->document->body);
    free(editor->document);
    free(editor);
}
