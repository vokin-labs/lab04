#include <file.h>

financial_file::financial_file(const std::string& name, const std::string& date,
                               const std::string& account)
    : _name(name), _date(date), _account(account) {}

std::string financial_file::name() const { return _name + ".txt"; }

std::string financial_file::date() const { return _date; }

std::string financial_file::account() const { return _account; }//
// Created by vok1n on 17.01.2021.
//
