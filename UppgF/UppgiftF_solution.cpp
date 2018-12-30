#include <vector>

double avarageTrunk(std::vector<Animal*>& djuren){
  int sum = 0, count = 0;

  for(auto djuret : djuren){
    if (ElephAnt* e = dynamic_cast<ElephAnt*>(djuret)){
      sum += e->getTrunkLength();
      count++;
    } // if
  } // for

  if (count == 0)
    return 0;
  else
    return sum / (double)count;

} // avarageTrunk
