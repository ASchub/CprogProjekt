#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

void insult(string who){
	cout << who << ", du är så dum och ful!\n";
}

void praise(string who){
	cout << who << ", du är så snygg och begåvad!\n";
}
void quit(string){
  exit(0);
}

void menu(string){
  cout << "0-quit, 1-insult, 2-praise, 3-menu\n";
}

typedef void(*Fpek)(string);

unordered_map<string, Fpek> funcs{	{"quit", quit}, {"insult", insult},
									{"praise", praise}, {"menu", menu} };

int main(){
  string namn;
  cout << "Vad heter du? ";
  cin >> namn;
  for(;;){
    cout << "Kommando: ";
    string kommando;
    cin >> kommando;
    funcs[kommando](namn);
  }

  return 0;
}

