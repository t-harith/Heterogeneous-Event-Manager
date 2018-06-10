# Heterogeneous-Event-Manager
An offshoot of the Mudbath repo, the heterogeneous event manager is an exploration of implementing multicasted delegates 
and a observer model with varied sender and receiver types. 

Yet another event manager implemented in c++, but with a twist: more focus on subscribing to objects and dealing with all 
events that they publish as opposed to subscribing to events, no matter which object publishes them.

This could have been implemented with classes for senders, receivers (or both) with inheritence, dynamic polymorphism and
the likes, but wheres the fun in that?

Instead, you have this hacky, rather high-maintance, interface that stands as a testament to the fact that just because something
can be done, doesn't always mean it should be :)
