#pragma once

#include <glaze/json/write.hpp>
#include <stdexcept>
#include <string>

namespace utilities {
template <typename T>
auto to_json(const T& data) -> std::string {
  std::string result;
  const auto err = glz::write_json(data, result);
  if (err) {
    const std::string errmsg(err.custom_error_message);
    throw std::logic_error(errmsg);
  }
  return result;
}
}  // namespace utilities

namespace std {
template <typename T>
std::string to_string(const T& data) {
  return utilities::to_json(data);
}
}  // namespace std
