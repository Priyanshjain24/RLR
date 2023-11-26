#include <algorithm>
#include <iterator>
#include <map>
#include <vector>

#include "cache.h"
#include "util.h"


struct Priority
{
  int Page = 0;
  int Ptype = 0;
  int Phit = 0;
};

struct LineState
{
  bool accessed=false;
  int age=0;
};

double RelativeDistance=10;
double AveragePreuseDistance=0;

int counter8=0;
int counter32=0;

std::map<CACHE*, std::vector<Priority> > LineValues;
std::map<CACHE*, std::vector<LineState> > LineStates;

bool PriorityStateComparator(const Priority& A, const Priority &B)
{
  return (A.Page+A.Phit+A.Ptype)<=(B.Page+B.Phit+B.Ptype);
}

void CACHE::initialize_replacement() {
  LineValues[this].resize(NUM_SET*NUM_WAY);
  LineStates[this].resize(NUM_SET*NUM_WAY);
}

// find replacement victim
uint32_t CACHE::find_victim(uint32_t cpu, uint64_t instr_id, uint32_t set, const BLOCK* current_set, uint64_t ip, uint64_t full_addr, uint32_t type)
{
  // baseline LRU
  auto it = next(LineValues[this].begin(),NUM_WAY*set);
  return std::distance(it,std::max_element(it, next(it,NUM_WAY), PriorityStateComparator));
}

// called on every cache hit and cache fill
void CACHE::update_replacement_state(uint32_t cpu, uint32_t set, uint32_t way, uint64_t full_addr, uint64_t ip, uint64_t victim_addr, uint32_t type, uint8_t hit)
{
  LineStates[this][NUM_WAY*set+way].accessed=true;

  if(hit)
  {
    LineValues[this][NUM_WAY*set+way].Phit=1;
  }
  else
  {
    LineValues[this][NUM_WAY*set+way].Phit=0;

    counter8++;

    if(counter8==8)
    {
      counter8=0;
      for(int i=NUM_WAY*set; i<NUM_WAY; i++)
      {
        LineStates[this][i].age++;
        if(LineStates[this][i].age>RelativeDistance)
        {
          LineValues[this][i].Page=0;
        }
        else
        {
          LineValues[this][i].Page=8;
        }
      }
    }
  }

  if(LineStates[this][NUM_WAY*set+way].age>RelativeDistance)
  {
    LineValues[this][NUM_WAY*set+way].Page=0;
  }
  else
  {
    LineValues[this][NUM_WAY*set+way].Page=8;
  }

  if(type!=PREFETCH)
  {
    LineValues[this][NUM_WAY*set+way].Ptype=1;
  }
  else
  {
    LineValues[this][NUM_WAY*set+way].Ptype=0;
  }

  counter32++;
  if(counter32==32)
  {
    AveragePreuseDistance=0;
    for(auto x: LineStates[this])
    {
      AveragePreuseDistance+=x.age;
    }

    AveragePreuseDistance/=(1.0*NUM_WAY*NUM_SET);
    RelativeDistance=2*AveragePreuseDistance;
  }

  return;
}

void CACHE::replacement_final_stats() {
  cout<<"DONEEEEEE!!!!!!!!!!!!!!!!!"<<endl;
}
