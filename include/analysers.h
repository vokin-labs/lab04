// Copyright 2021 vokin-labs <vokinsilok2305@mail.ru>

#ifndef TEMPLATE_ANALYSERS_H
#define TEMPLATE_ANALYSERS_H

#include <broker.h>

#include <string>
#include <vector>

broker analyse_one(const std::string &path);
std::vector<broker> analyse_all(const std::string &path);

void print_brokers_files(const std::vector<broker> &brokers);
void print_brokers_info(const std::vector<broker> &brokers);
#endif  // TEMPLATE_ANALYSERS_H
