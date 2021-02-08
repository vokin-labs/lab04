// Copyright 2021 vokin-labs <vokinsilok2305@mail.ru>

#include <analysers.h>
#include <broker.h>

#include <algorithm>
#include <boost/filesystem.hpp>
#include <iostream>
#include <string>
#include <vector>

using d_path = boost::filesystem::path;
using d_iter = boost::filesystem::directory_iterator;
using d_entry = boost::filesystem::directory_entry;

inline bool is_separator(char c) { return c == '_'; }

inline bool not_separator(char c) { return !is_separator(c); }

std::vector<std::string> split_string(const std::string &text) {
  std::vector<std::string> ret;
  for (auto i = text.cbegin(); i != text.cend();) {
    i = std::find_if(i, text.end(), not_separator);
    auto j = std::find_if(i, text.end(), is_separator);
    ret.push_back(std::string(i, j));
    i = j;
  }
  return ret;
}

void processing_filename(const std::string &filename,
                         std::vector<financial_file> &files,
                         std::set<std::string> &accounts) {
  const std::string type = "balance";
  const std::size_t account_length = 8;
  const std::size_t date_length = 8;

  enum { balance, account, date };

  std::vector<std::string> filename_tokens = split_string(filename);

  if (filename_tokens.size() != 3) return;

  if (filename_tokens[balance] != type) return;
  if (filename_tokens[account].length() != account_length) return;
  if (filename_tokens[date].length() != date_length) return;

  files.push_back(financial_file(filename, filename_tokens[date],
                                 filename_tokens[account]));
  accounts.insert(filename_tokens[account]);
}

broker analyse_one(const std::string &path) {
  std::string name;
  std::vector<financial_file> files;
  std::set<std::string> accounts;

  const d_path broker_directory{path};
  if (!boost::filesystem::is_directory(broker_directory))
    throw std::runtime_error(
        "argument must be path to broker directory, not file");

  name = broker_directory.filename().stem().string();
  for (const auto &entry : d_iter{broker_directory}) {
    if (boost::filesystem::is_directory(entry) ||
        !entry.path().stem().extension().empty() ||
        entry.path().extension().string() != ".txt") {
      continue;
    }
    processing_filename(entry.path().filename().stem().string(), files,
                        accounts);
  }
  return broker(name, files, accounts);
}

std::vector<broker> analyse_all(const std::string &path) {
  const d_path brokers_directory{path};
  std::vector<broker> result;
  for (const auto &entry : d_iter{brokers_directory}) {
    broker brok = analyse_one(entry.path().string());
    if (!brok.files().empty() && !brok.accounts().empty())
      result.push_back(brok);
  }
  return result;
}

std::string lastdate(const std::vector<financial_file> &files) {
  std::string res;
  for (const auto &file : files) {
    res = std::max(res, file.date());
  }
  return res;
}

void print_brokers_files(const std::vector<broker> &brokers) {
  for (auto const &broker : brokers) {
    for (auto const &broker_file : broker.files()) {
      std::cout << broker.name() << " " << broker_file.name() << std::endl;
    }
  }
}

void print_brokers_info(const std::vector<broker> &brokers) {
  for (auto const &broker : brokers) {
    for (auto const &account : broker.accounts()) {
      std::vector<financial_file> this_account_files;
      for (auto const &file : broker.files()) {
        if (file.account() == account) this_account_files.push_back(file);
      }
      std::cout << "broker:" << broker.name() << " account:" << account
                << " files:" << this_account_files.size()
                << " lastdate:" << lastdate(this_account_files) << std::endl;
    }
  }
}
