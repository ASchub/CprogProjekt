#include "Session.h"
#include <map>
#include <iostream>
using namespace std;

map<string, Func> commands;

void install(Func f, string command){
  commands[command] = f;
}

void run(){
  for(;;){
    cout << "Kommando: ";
    string cmd;
    cin >> cmd;
    if (commands.count(cmd))
      commands[cmd]();
    else
      cout << "Inget sådant kommando!" << endl;
  }
}


