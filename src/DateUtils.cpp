#include "DateUtils.h"
#include <ctime>
#include <sstream>
#include <iomanip>

bool DateUtils::isLeapYear(int year) {

    if (year % 400 == 0) return true;
    if (year % 100 == 0) return false;
    if (year % 4 == 0) return true;

    return false;
}

std::tm DateUtils::parseDate(const std::string& date) {

    std::tm t{};
    t.tm_year = std::stoi(date.substr(0,4)) - 1900;
    t.tm_mon  = std::stoi(date.substr(5,2)) - 1;
    t.tm_mday = std::stoi(date.substr(8,2));

    return t;
}

std::string DateUtils::formatDate(const std::tm& t) {

    std::ostringstream oss;

    oss << std::setw(4) << std::setfill('0') << (t.tm_year + 1900)
        << "-"
        << std::setw(2) << std::setfill('0') << (t.tm_mon + 1)
        << "-"
        << std::setw(2) << std::setfill('0') << t.tm_mday;

    return oss.str();
}

std::string DateUtils::addDays(const std::string& date, int days) {

    std::tm t = parseDate(date);
    std::time_t time = std::mktime(&t);

    time += days * 86400;

    std::tm* result = std::localtime(&time);

    return formatDate(*result);
}

int DateUtils::daysBetween(const std::string& date1,
                           const std::string& date2) {

    std::tm t1 = parseDate(date1);
    std::tm t2 = parseDate(date2);

    std::time_t time1 = std::mktime(&t1);
    std::time_t time2 = std::mktime(&t2);

    int diff = (time2 - time1) / 86400;

    return diff;
}

std::string DateUtils::today() {

    std::time_t now = std::time(nullptr);
    std::tm* t = std::localtime(&now);

    return formatDate(*t);
}