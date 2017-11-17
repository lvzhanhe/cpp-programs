## TriMap

We have done work with an STL map, a way to map a key to a value. But there are some restrictions on a map. You can search a map for a key (and then the associated value) but you cannot search a map for a value (and then the associated key). Furthermore, because a map is kept in a particular order, an ordering based on the keys, we cannot know the order of insertion of each element. I am going to fix all that with a new STL-like data structure, the **TriMap**.

### notes

`std::upper_bound` returns an iterator pointing to the first element in the range `[first,last)` which compares greater than `val`.

`std::advance`: advances the iterator it by n element positions.

`->`: If you have a pointer or iterator pointing to an object, you would have to use the arrow to obtain the members of it.