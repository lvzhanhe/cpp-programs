#include <sstream>
using std::ostringstream;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <algorithm>
using std::sort; using std::upper_bound;
#include <iostream>
using std::ostream;
#include <iterator>
using std::advance;
#include "trimap.h"

TriMap::TriMap(const Element& e){
 vec_ = {e};
 sz_ = 1;
}

TriMap::TriMap(initializer_list<Element> i){
 vec_= i;
 sz_ = vec_.size();
}

ostream& operator<<(ostream& oss, const Element& elem){
 oss << elem.key_ << ":" << elem.value_ << ":" << elem.index_;
 return oss;
}

ostream& operator<<(ostream& oss, const TriMap& m){
 size_t s = m.vec_.size();
 for (auto i = 0; i < s; ++i){
  oss << m.vec_[i];
  if (i != s-1)
   oss << ", ";
 }
 return oss;
}

size_t TriMap::size(){
 return vec_.size();
}

bool TriMap::insert(string key, string value){
 for (Element e : vec_){
  if (key == e.key_)
   return false;
 }
    Element new_elem(key, value, sz_);
    vec_.push_back(new_elem);
    sort(vec_.begin(),vec_.end(),[](auto &p1, auto &p2){
  return p1.key_ < p2.key_;
 });
 sz_++;
    return true;
}

bool TriMap::remove(string key){
 size_t s = vec_.size();
 for (auto i = 0; i < s; ++i){
  if (key == vec_[i].key_){
   vec_.erase(vec_.begin()+i);
   for(auto j = 0; j < s-1; ++j){
    if (vec_[j].index_ > vec_[i].index_)
     vec_[j].index_--;
   }
   sz_--;
   return true;
  }
 }
 return false;
}

Element* TriMap::find_key(const string& key){
  auto pos = upper_bound(vec_.begin(),vec_.end(),key,[](const string &str, Element &x){
      return str < x.key_;});
  advance(pos, -1);
  if (pos->key_ == key)
    return &(*pos);
  else
    return nullptr;
}


Element* TriMap::find_value(const string& value){
 size_t s = vec_.size();
 for (auto i = 0; i < s; ++i){
  if (value == vec_[i].value_){
   Element *p = &vec_[i];
   return p;
  }
 }
 return nullptr;
}

Element* TriMap::find_index(size_t index){
 size_t s = vec_.size();
 for (auto i = 0; i < s; ++i){
  if (index == vec_[i].index_){
   Element *p = &vec_[i];
   return p;
  }
 }
 return nullptr;
}
