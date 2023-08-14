#ifndef PARSER_H
#define PARSER_H
#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

void parseFile(char* path, void (*callback)(char* line, void* data), void* data);

#endif