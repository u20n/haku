#pragma once

#include <string>
#include <vector>
#include <utility>
#include <cassert>


/**
 * key manager for haku
 * we map abitrary keytypes
 * in arbitrary key-orientations
 * (for your convienance)
 * this is opt-in, if it doesn't make
 * sense to utilise this, manage your
 * keys in a way that does
 *
 * all that keys does is manage the key sets,
 * it is up to the overlay to determine the 
 * use/patterns/meaning of these keys
 * 
 * to use these keys cryptographically, use either
 * the implementations in core, or write your own
 * from the crypto++ library
 * */
using namespace CryptoPP;
struct keys {
private:
  std::vector<
    std::vector<SecByteBlock*>
  > kledger; // key ledger
public:
  void set(
      int kli, // key ledger index
      std::map<int, std::string> im // encoded keys mapped to interal index 
    ) {
    // TODO
    
  }

  std::string get(
      int kli, // key ledger index
      int ii // interal index
    ) {
    // TODO
  }
};
