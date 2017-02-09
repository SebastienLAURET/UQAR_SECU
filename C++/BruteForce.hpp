#ifndef BRUTEFORCE_HPP_
# define BRUTEFORCE_HPP_

#include <iostream>
#include <thread>
#include <vector>

#include "MD5.hpp"

class BruteForce : public std::thread {
public:
  BruteForce()
  : std::thread(BruteForce::trampoline, this) {
    _tabChar = std::vector<char>({
      'a','b','c','d','e','f','g','h','i','j',
      'k','l','m','n','o','p','q','r','s','t',
      'u','v','w','x','y','z',
      '0','1','2','3','4','5','6','7','8','9',
      '!','@','#','$','%','&','*'
    });
  }
  ~BruteForce() {

  }

  void operator()() {
    std::string nPwd, pwdH;
    for (size_t i = 0; i < 100; i++) {
      nPwd = _genPwd(i, 8);
      pwdH = _md5(nPwd);
      std::cout << nPwd << " = "<< pwdH << '\n';
    }
  }


  static void trampoline(BruteForce *self) {
    (*self)();
  }
private:

  std::string &_checkPWD() {

  }

  std::string _md5(std::string &input) {
    return md5(input);
  }

  std::string _genPwd(int value, int pwdLength) {
    std::string newPwd;
    int         tmpState = value;
    int         tmpChar;
    int         rang = _tabChar.size();

    for (size_t i = 0; i < pwdLength; i++) {
      tmpChar = int(tmpState / rang);
      newPwd += _tabChar[int(tmpState - (tmpChar * rang)) % rang];
      tmpState = tmpChar;
    }
    return newPwd;
  }

  std::vector<char> _tabChar;

};

#endif //!BRUTEFORCE_HPP_
