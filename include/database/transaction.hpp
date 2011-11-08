#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include "tools/byte_buffer.hpp"
#include "object/object_store.hpp"
#include "object/object_serializer.hpp"
#include "database/action.hpp"

#include <memory>
#include <list>

namespace oos {

class database;

class transaction
{
public:
  transaction(database *db);
  ~transaction();
  
  long id() const;

  void begin();
  void commit();
  void rollback();

  database* db();
  const database* db() const;

private:
  class transaction_observer : public object_observer
  {
  public:
    transaction_observer(transaction &tr);
    virtual ~transaction_observer();

    virtual void on_insert(object *o);
    virtual void on_update(object *o);
    virtual void on_delete(object *o);
    
  private:
    transaction &tr_;
  };

  class backup_visitor : public action_visitor
  {
  public:
    backup_visitor(byte_buffer &buffer)
      : buffer_(buffer)
    {}
    virtual ~backup_visitor() {}

    bool backup(action *act);

    virtual void visit(insert_action *a);
    virtual void visit(update_action *a);
    virtual void visit(delete_action *a);  

  private:
    byte_buffer &buffer_;
    object_serializer serializer_;
  };

  class restore_visitor : public action_visitor
  {
  public:
    restore_visitor(byte_buffer &buffer, object_store &ostore)
      : buffer_(buffer)
      , ostore_(ostore)
    {}
    virtual ~restore_visitor() {}

    bool restore(action *act);

    virtual void visit(insert_action *a);
    virtual void visit(update_action *a);
    virtual void visit(delete_action *a);  

  private:
    byte_buffer &buffer_;
    object_store &ostore_;
    object_serializer serializer_;
  };

private:
  friend class transaction_observer;
  
  void backup(action *a);

private:
  static long id_counter;

private:
  database *db_;
  long id_;
  
  std::auto_ptr<transaction_observer> tro_;
  
  typedef std::list<action*> action_list_t;
  typedef action_list_t::iterator iterator;
  typedef action_list_t::const_iterator const_iterator;
  action_list_t action_list_;

  byte_buffer object_buffer_;
  backup_visitor backup_visitor_;
  restore_visitor restore_visitor_;
};

}

#endif /* TRANSACTION_HPP */