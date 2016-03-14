//
// Created by sascha on 12.03.16.
//

#include "tools/identifier_resolver.hpp"

#include "object/action_remover.hpp"
#include "object/insert_action.hpp"
#include "object/update_action.hpp"
#include "object/delete_action.hpp"

namespace oos {

action_remover::action_remover(t_action_vactor &actions)
  : actions_(actions)
{}


bool action_remover::remove(action_remover::action_iterator i, object_proxy *proxy)
{
  proxy_ = proxy;
  action_iterator_ = i;
  (*i)->accept(this);
  proxy_ = 0;
  return true;
}

void action_remover::visit(insert_action *a)
{
  /***********
   *
   * an insert action was found
   * try to find serializable with given
   * id and delete and remove it
   * from insert action
   *
   ***********/
  insert_action::iterator i = a->find(id_);
  if (i != a->end()) {
    a->erase(i);
  }
  if (a->empty()) {
    delete a;
    actions_.erase(action_iterator_);
  }
}

void action_remover::visit(update_action *)
{
  /***********
   *
   * an update action was found
   * replace this update action
   * with a new delete action
   * with this given serializable.
   *
   ***********/
//  if (a->proxy()->id() == id_) {
//    basic_identifier *pk = identifier_resolver::resolve(proxy_->obj());
//
//    action_iterator_->reset(new delete_action(proxy_->node()->type(), proxy_->id(), pk));
//  }
}

void action_remover::visit(delete_action *)
{

}

}