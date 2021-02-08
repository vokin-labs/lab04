#include <analysers.h>
#include <broker.h>
#include <file.h>

int main(int argc, char *argv[]) {
  std::string directory;
  if (argc == 1) {
    directory = ".";
  } else {
    directory = argv[1];
  }

  // for test
  directory = "../misc/ftp";

  std::vector<broker> brokers = analyse_all(directory);
  print_brokers_files(brokers);
  print_brokers_info(brokers);
  return 0;
}
