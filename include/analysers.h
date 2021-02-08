//
// Created by vok1n on 17.01.2021.
//

#ifndef TEMPLATE_ANALYSERS_H
#define TEMPLATE_ANALYSERS_H
#include <broker.h>

#include <boost/filesystem.hpp>
#include <string>
#include <vector>

using d_path = boost::filesystem::path;
using d_iter = boost::filesystem::directory_iterator;
using d_entry = boost::filesystem::directory_entry;

broker analyse_one(const std::string &path);

std::vector<broker> analyse_all(const std::string &path);

void print_brokers_files(const std::vector<broker> &brokers);
void print_brokers_info(const std::vector<broker> &brokers);
#endif  // TEMPLATE_ANALYSERS_H
