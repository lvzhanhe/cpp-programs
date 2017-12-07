#ifndef TRIMAP_H
#define TRIMAP_H

#include <iostream>
using std::ostream; using std::cout; using std::endl;
#include <sstream>
using std::ostringstream;
#include <utility>
#include <algorithm>
using std::swap;
#include <string>
using std::string;

// forward declaration so we can make Element a friend of TriMap
template<typename K, typename V>
class TriMap;

// private Element, friend of TriMap class
template <typename K, typename V>
class Element{

private:
  K key_;
  size_t index_ = 0;
  Element *next_ = nullptr;  

public:
  V value_;
  
  Element() = default;
  Element(K key, V val, size_t i) : key_(key),index_(i), next_(nullptr), value_(val) {};

  // *defined* in the class, makes templating easier.
  friend ostream& operator<<(ostream& out, Element& e){
    out << e.key_ << ":" << e.value_ << ":" << e.index_;
    return out;
  }
  friend class TriMap<K,V>;
};


template<typename K, typename V>
class TriMap{

private:
  Element<K,V> *head_ = nullptr;
  Element<K,V> *tail_ = nullptr;
  size_t size_ = 0;
  
  // a private function, used by operator<<
  void print_list(ostream& out);
  
public:
  TriMap() = default;
  TriMap(K, V);
  TriMap(const TriMap&);
  TriMap& operator=(TriMap);
  ~TriMap();
  long size();
  bool insert(K,V);
  bool remove(K);
  Element<K,V>* find_key(K);
  Element<K,V>* find_value(V);
  Element<K,V>* find_index(size_t);  
  
  // *defined* in the class, makes templating easier.
  // uses private method print_list
  // you can remove print_list and just do it here if you
  // prefer. I won't test print_list
  friend ostream& operator<<(ostream& out, TriMap<K,V>& sl){
    sl.print_list(out);
    return out;
  };
};

template<typename K, typename V>
TriMap<K,V>::TriMap(K key, V value){
  Element<K,V>* ptr = new Element<K,V>(key,value,0);
  head_ = ptr;
  tail_ = ptr;
  size_ = 1;
}

/* 
bit of work. we need to remember a pointer that walks
down the list to copy, as tail_ walks down the new list. 
Make a new node (copy the current node of the list we are copying), 
update the tail_->next_ to point to the new node, update tail_ to new node
 */
template<typename K, typename V>
TriMap<K,V>::TriMap(const TriMap& tm){
  if (tm.head_ == nullptr){
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
  }
  else{
    head_ = new Element<K,V>(tm.head_->key_,tm.head_->value_,tm.head_->index_);
    tail_ = head_;
    Element<K,V>* tm_ptr = tm.head_->next_;
    Element<K,V>* new_element;
    while (tm_ptr != nullptr){
      new_element = new Element<K,V>(tm_ptr->key_,tm_ptr->value_,tm_ptr->index_);
      tail_->next_ = new_element;
      tm_ptr = tm_ptr->next_;
      tail_ = new_element;
    }
    size_ = tm.size_;
  }
}

template<typename K, typename V>
TriMap<K,V>& TriMap<K,V>::operator=(TriMap tm){
  swap(head_, tm.head_);
  swap(tail_, tm.tail_);
  swap(size_, tm.size_);
  return *this;
}
	

// walk down the list using head_ , keeping a trailer pointer called to_del
// delete what to_del points to
// move head_ and to_del to the next node.
template<typename K, typename V>
TriMap<K,V>::~TriMap(){
  Element<K,V>* to_del = head_;
  while (to_del != nullptr){
    head_ = head_->next_;
    delete to_del;
    to_del = head_;
  }
  head_ = nullptr;
  tail_ = nullptr;
  size_ = 0;
}

template<typename K, typename V>
long TriMap<K,V>::size(){
  return size_;
  
}

template<typename K, typename V>
bool TriMap<K,V>::insert(K key, V value){
    Element<K,V> *ptr;
    Element<K,V>* new_element = new Element<K,V>(key,value,size_);
    if (find_key(key)){
        return false;
    }
    if (head_ == nullptr){
        head_ = new_element;
        tail_ = new_element;
        size_++;
        return true;
    }
    else{
        if (head_->key_ > key){
            new_element->next_ = head_;
            head_ = new_element;
            size_++;
            return true;
        }
        else{
            for(ptr = head_; ptr->next_ != nullptr; ptr = ptr->next_){
                if (ptr->next_->key_ > key){
                    new_element->next_ = ptr->next_;
                    ptr->next_ = new_element;
                    size_++;
                    return true;
                }
            }
            tail_->next_ = new_element;
            tail_ = new_element;
            size_++;
            return true;
            //Code to add element as tail element
            //Set tail's next_ (which is nullptr right now) to new element
            //Set new elements next_ to nullptr (bc its the tail now)
            //Set tail_ to new element
        }
    }
  // very important, what are all the cases here!!!!
  // elements are inserted in *key order*
}
    

  
 

template<typename K, typename V>
Element<K,V>* TriMap<K,V>::find_key(K key){
  // linear search
    Element<K,V> *result = nullptr;
    for(Element<K,V> *n = head_; n != nullptr; n = n->next_){
        if (n->key_ == key){
            result = n;
            break;
        }
    }
  return result;
}    
template<typename K, typename V>
bool TriMap<K,V>::remove(K key){
    Element<K,V> *k = find_key(key);
    Element<K,V> *ptr;
    if (k == nullptr){
        return false;
    }
    size_t i = k->index_;
    if (head_ == tail_){
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
        return true;
    }
    if (head_->next_ == tail_){
        if (head_->key_ == key){
            head_ = tail_;
            size_--;
        }
        else{
            tail_ = head_;
            head_->next_ = nullptr;
            size_--;
        }
    }
    else if (head_->key_ == key){
        head_ = head_->next_;
        size_--;
    }
    else{
        for(ptr = head_; ptr->next_ != nullptr; ptr = ptr->next_){
            if (ptr->next_->key_ == key){
                if (ptr->next_->next_ == nullptr){
                    ptr->next_ = nullptr;
                    tail_ = ptr;
                }
                else{
                    ptr->next_ = ptr->next_->next_;
                }
            size_--;
            break;
            }
        }
    }
    
    for(ptr = head_; ptr != nullptr; ptr = ptr->next_){
        if (ptr->index_ > i){
            ptr->index_--;
        }
    }
    return true;
  
  // again, what are all the cases!!!
  // also, if you delete a node, the indicies of all
  // nodes with a higher index have that index reduced by one
}

template<typename K, typename V>
Element<K,V>* TriMap<K,V>::find_value(V val){
  // linear search
    Element<K,V> *result = nullptr;
    for(Element<K,V> *n = head_; n != nullptr; n = n->next_){
        if (n->value_ == val){
            result = n;
            break;
        }
    }
  return result;
}  

template<typename K, typename V>
Element<K,V>* TriMap<K,V>::find_index(size_t i){
  // linear search
  Element<K,V> *result = nullptr;
  for(Element<K,V> *n = head_; n != nullptr; n = n->next_){
    if (n->index_ == i){
      result = n;
      break;
    }
  }
  return result;
}  

template<typename K, typename V>
void TriMap<K,V>::print_list(ostream &out){
  ostringstream oss;
  Element<K,V> *ptr;
  for(ptr = head_; ptr != nullptr; ptr = ptr->next_)
    oss << *ptr << ", ";
  string s = oss.str();
  out << s.substr(0,s.size()-2);
  // this is a class member function, has access
  // to private data. Called by operator<<
}


#endif