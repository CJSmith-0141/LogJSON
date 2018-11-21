# LogJson - A streaming log using nlohmann::json

The basic idea I had for this project is to make a specialization for nlohmann::json for just logging

Goals:

* Make a base class that's easy to specialize 
* Create a meta-programming step for basic POD classes and structs (i.e. given a header with POD classes, create source code that contains a LogJson derived class that logs the POD classes. )
* Include some generaized derived classes for logging key-value pairs in json arrays or json objects (The parent logging object will always output a json-object)

What I've got so far: 

* I've started getting the scheme for different timestamp styles together
