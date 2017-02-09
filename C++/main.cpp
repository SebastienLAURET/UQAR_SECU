#include <atomic>
#include "BruteForce.hpp"

int main(int argc, char const *argv[]) {
  std::list<std::string>  listH;
  std::atomic<uint64_t>   iter(0);
  //uint64_t   iter = 0;
//  listH.push_back("");
  listH.push_back("77e2a767d2c6a7db4efaec3a6b78986a");
  listH.push_back("884ab2ad0e957096f465729f4b65c569");
  listH.push_back("3dbe00a167653a1aaee01d93e77e730e");
  listH.push_back("b45e9faa7b5a41268216ad80e212be81");
  listH.push_back("896b4a5a5f3e14f7971b8145e26cc0f5");
  listH.push_back("3d59e81a5b45e30a73dbc674aa67d372");
  listH.push_back("61568f316347f53155bbfc609766d6b9");
  listH.push_back("8e30f24a51c9fe65bad23bad0236e3aa");
  listH.push_back("dc808ed2f06d925ac0080dd894b0e277");
  listH.push_back("7963c90f29cdf901001511fd15068f07");
  listH.push_back("64adf2ea93b015fc4778752092d7b913");
  listH.push_back("81854d328373663b052c32a6503035f2");
  listH.push_back("11d5ccad80c724dbbc1e6edb5a9de6a3");
  listH.push_back("c27b8bd22ffc89de4a1aa97234414b50");
  listH.push_back("6fb692a12e740016e297a62b751f2d21");
  listH.push_back("9c7709b39efe0e0038419fd2aa9526b6");
  listH.push_back("d37f80a433a83d8657ffee229f80388c");
  listH.push_back("b276b39080338bba04115929753351d9");

  std::list<BruteForce*> bFs;

  for (size_t i = 0; i <= 8; i++) {
    bFs.push_back(new BruteForce(listH, iter));
  }

  for (auto bF : bFs) {
    bF->join();
    delete bF;
  }
  return 0;
}
