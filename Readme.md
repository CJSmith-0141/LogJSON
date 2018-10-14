# LogJson - A streaming log using nlohmann::json
## WIP, see branch JustGettingStarted for current WIP 

The basic idea I had for this project is to make a specialization for nlohmann::json for just logging

Goals:

* Make a base class that's easy to specialize 
* Create a meta-programming step for basic POD-style classes and structs  
* Include some generaized derived classes for logging key-value pairs in json arrays or json objects (The parent logging object with always output a json-object)

What I've got so far: 

* I've started getting the scheme for different timestamp styles together