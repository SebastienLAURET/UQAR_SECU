#ifndef BRUTEFORCE_HPP_
# define BRUTEFORCE_HPP_

#include <iostream>
#include <algorithm>
#include <thread>
#include <vector>
#include <list>
#include <ctgmath>
#include <atomic>
#include "MD5.hpp"

class BruteForce : public std::thread {
public:
  BruteForce(std::list<std::string>  &tabH, std::atomic<uint64_t>/*uint64_t*/ &it)
  : std::thread(BruteForce::trampoline, this),
    _tabHash(tabH), _iter(it) {
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
    int       pwdLength = 5, tmpIter;
    uint64_t  max = std::pow(_tabChar.size(), pwdLength);
    std::cout << "max "<< max << " "<< _tabChar.size()<<'\n';
    while (_iter < max) {
      tmpIter = _iter++;
      nPwd = _genPwd(tmpIter, pwdLength);
      pwdH = _md5(nPwd);
    //  std::cout << nPwd << "=" << pwdH << "==" << "65466125197978378ec6340989ac50db" << std::endl;
      if (_checkPWD(pwdH)) {
        std::cout << nPwd << "==" << pwdH << std::endl;
        if (_tabHash.size() == 0)
          exit(0);
      }
    }

  }


  static void trampoline(BruteForce *self) {
    (*self)();
  }
private:

  bool _checkPWD(std::string &input) {
    auto it = std::find(_tabHash.begin(), _tabHash.end(), input);
    if (it != _tabHash.end()) {
      _tabHash.erase(it);
    }
    return (it != _tabHash.end());
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

  std::vector<char>       _tabChar;
  std::list<std::string>  &_tabHash;
  std::atomic<uint64_t>   &_iter;
//  uint64_t   &_iter;
};

#endif //!BRUTEFORCE_HPP_
