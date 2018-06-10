# Heterogeneous-Event-Manager
An offshoot of the Mudbath repo, the heterogeneous event manager is an exploration of implementing an observer model with multi-casted delegates and sender-receiver functionality with heterogenous object types. 

It is yet another event system implemented in c++, but with a twist; it focusses on subscribing to objects and dealing with all events they publish (as opposed to subscribing to events themselves).

It makes use of unions to keep track of pointers to multiple object types.

This could have been implemented with classes for senders, and receivers, (or both) with inheritance, dynamic polymorphism and the likes, but where’s the fun in that?

Instead, you have this hacky (and rather high-maintenance,) interface that stands as a testament to how much you can push the limits of c++.

