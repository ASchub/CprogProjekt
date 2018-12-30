#ifndef SESSION_H
#define SESSION_H

#include <string>

typedef void (*Func)();

void install(Func f, std::string command);
void run();

#endif
