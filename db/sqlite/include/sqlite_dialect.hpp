//
// Created by sascha on 3/3/16.
//

#ifndef OOS_SQLITE_DIALECT_HPP
#define OOS_SQLITE_DIALECT_HPP

#include "sql/basic_dialect.hpp"

namespace oos {
namespace sqlite {

class sqlite_dialect : public basic_dialect
{
public:
  sqlite_dialect();

  const char* type_string(oos::data_type type) const;
  data_type string_type(const char *type) const;
};

}
}

#endif //OOS_SQLITE_DIALECT_HPP
