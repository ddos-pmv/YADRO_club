#pragma once
#include <stdexcept>

class ParseException : public std::runtime_error {
 public:
  using std::runtime_error::runtime_error;
};

class ConfigParseException : public ParseException {
 public:
  using ParseException::ParseException;
};
class EventParseException : public ParseException {
 public:
  using ParseException::ParseException;
};
