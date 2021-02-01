//
// Created by vok1n on 17.01.2021.
//

#ifndef TEMPLATE_BROKER_H
#define TEMPLATE_BROKER_H
#include <file.h>
#include <string>
#include <vector>
#include <set>

class broker {
 public:
  broker() = default;
  broker(const std::string &name, const std::vector<financial_file> &files,
         const std::set<std::string> &accounts);

  std::string name() const;
  std::vector<financial_file> files() const;
  std::set<std::string> accounts() const;


 private:
  std::string _name;
  std::vector<financial_file> _files;
  std::set<std::string> _accounts;
};
#endif  // TEMPLATE_BROKER_H
