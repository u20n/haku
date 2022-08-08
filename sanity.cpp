#include <vector>
#include <string>
#include <iostream>
#include <cassert>
int main(void) {
  std::vector<std::string> words, layers;

  words = {
    "llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll"
  };

  unsigned int aspace = 9;
  unsigned int i = 0;
  unsigned int lindex = layers.size(); // layer index
  while (i < words.size()) {
    if (words.at(i).size() > aspace) { // the word is too big, hypenate 
      std::string big = words.at(i);

      big.insert(aspace-1, "-"); // inject hyphen
      words.at(i) = big.substr(0, aspace); // first part of the split
       
      words.resize(words.size()+1); // we're adding a new word
      
      words.insert(
        words.begin() + i+1, // behind i 
        big.substr(aspace-1, big.size()) // so we get '-' on the other side too
      ); // rest
      std::cout << "trying again (hyphen)\n";
      continue; // try again 
    }
        
    if (layers.size() < lindex+1) { // new layer?
      layers.resize(lindex+1);
    }

    if ((layers.at(lindex).size() + words.at(i).size()) > aspace) {
      lindex++; // next layer
      std::cout << "trying again (layer++)\n";
      continue; // try again
    } 
        
    layers.at(lindex).append(words.at(i));
    i++;
  }
  // pad when necessary
  for (unsigned int i=0; i<layers.size(); i++) {
    while(layers.at(i).size() < aspace) {
      layers.at(i).append(" ");
    }
  }
  for (auto l: layers) {
    std::cout << l << '\n';
  }
  return 0;
}
