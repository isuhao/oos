#ifndef FACTORYTESTUNIT_HPP
#define FACTORYTESTUNIT_HPP

#include "unit/unit_test.hpp"

class FactoryTestUnit : public oos::unit_test
{
public:
  FactoryTestUnit();

  void create_factory();
  void insert_items();
  void produce_items();
  void list_items();
};

#endif /* FACTORYTESTUNIT_HPP */
