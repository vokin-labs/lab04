// Copyright 2021 vokin-labs <vokinsilok2305@mail.ru>

#ifndef TEMPLATE_FILE_H
#define TEMPLATE_FILE_H
#include <string>

class financial_file {
 public:
  financial_file() = default;
  financial_file(const std::string &name, const std::string &date,
                 const std::string &account);

  std::string name() const;
  std::string date() const;
  std::string account() const;

 private:
  std::string _name;
  std::string _date;
  std::string _account;
};
#endif  // TEMPLATE_FILE_H
