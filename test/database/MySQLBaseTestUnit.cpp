#include "MySQLBaseTestUnit.hpp"

#include "../Item.hpp"

#include "object/object_view.hpp"
#include "object/object_list.hpp"
#include "object/object_store.hpp"


#include "database/session.hpp"
#include "database/transaction.hpp"
#include "database/database_exception.hpp"

#include <iostream>
#include <fstream>
#include <cstdio>

using namespace oos;
using namespace std;

MySQLBaseTestUnit::MySQLBaseTestUnit()
  : unit_test("database test unit")
{
  add_test("open_close", std::tr1::bind(&MySQLBaseTestUnit::test_open_close, this), "open and close database test");
  add_test("create_drop", std::tr1::bind(&MySQLBaseTestUnit::test_create_drop, this), "create and drop database test");
}

MySQLBaseTestUnit::~MySQLBaseTestUnit()
{}

void
MySQLBaseTestUnit::initialize()
{
}

void
MySQLBaseTestUnit::finalize()
{
}

void MySQLBaseTestUnit::test_open_close()
{
  oos::object_store ostore;
  ostore.insert_prototype<book>("book");

  // create database and make object store known to the database
  session db(ostore, "mysql://sascha:sascha@localhost/test");

  UNIT_ASSERT_TRUE(db.is_open(), "couldn't open database database");
  
  db.close();

  UNIT_ASSERT_FALSE(db.is_open(), "couldn't close database database");

  ostore.clear(true);
}

void MySQLBaseTestUnit::test_create_drop()
{
  oos::object_store ostore;
  ostore.insert_prototype<Item>("item");

  // create database and make object store known to the database
  session db(ostore, "mysql://sascha:sascha@localhost/test");

  UNIT_ASSERT_TRUE(db.is_open(), "couldn't open database database");
  
  db.create();

  db.close();

  UNIT_ASSERT_FALSE(db.is_open(), "couldn't close database database");

  ostore.clear(true);
}