#include "ex_runner.h"
#include <sstream>

void ExRunner::run(const Ex* insert){
  std::stringstream thecommand{insert->sentence};
  std::string curr; 
  thecommand >> curr;
  if (curr == "w"){
    
  }
}

