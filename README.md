# rtoml 

Provides a convenient way to load/save variables to configuration files using TOML.  
Uses submodules ToruNiina/toml11 and Tessil/ordered-map .

Requires -std=c++17.  
Is a header only library.  

# Usage:

Declare a configuration map:  
~~~cpp
    rtoml::vsr mapa("filename.toml");
~~~
The argument is optional, and can be defined/overridden when saving.

First we define a variable, for example a double. We should give it a default value by initializing it.  
We can then associate a map entry to it. It then contains a reference to that variable.  
This means that calling `vsr::load` overwrites all the variables with entries found in the configuration file, and `vsr::save` saves all the entries into a file.  
The variable can be used normally once initialized and a load is performed.
~~~cpp
    double a=5;
    mapa["entry1"]=a;
~~~
It is possible to have entry hierarchy:
~~~cpp
    std::string b=5;
    mapa["Map1"]["Map2"]["entry2"]=b;
~~~
Note that if `mapa["entry1"]` is associated to a variable, trying `mapa["entry1"]["entry2"]` will obviously throw an exception.  
It is also possible to retrieve an entry directly by name (it must exist and you must know the type):
~~~cpp
    double var=*mapa["MapX"]["entryY"].get<int>();
~~~
Furthermore, you can add comments to both entries and maps that are then visible in the .toml configuration file.
~~~cpp
    mapa["x"]["xx"].comments.push_back("comment 1");
    mapa["x"]["xx"].comments.push_back("comment 2");
~~~

Once all entries have been initialized we can now load a file. This searches the file for entries matching those that have been initialized, and if found replaces the variable values with those from the file. Other entries are ignored.
~~~cpp
    mapa.load();
~~~
load takes two optional arguments:  
&nbsp;&nbsp;&nbsp;&nbsp; `bool trip (false)`  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;if true, and the file does not contain all of the initialized variables or does not exist,  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;an exception will be thrown; otherwise, missing file/entries will be ignored  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;extra entries are always ignored  
&nbsp;&nbsp;&nbsp;&nbsp; `std::string confFilename=""`  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;if specified, this overrides the filename

NOTE: you cannot use `.get<type>` for uninitialized entries even thought they were present in the loaded file.  
NOTE: you cannot load a file unless at least one entry has been added to the map object (would be pointless anyway without .get).

At this point you use and modify your variables as you see fit without the need to call any objects in the library.
Once you wish to save them just do:
~~~cpp
    mapa.save();
~~~
save takes two optional arguments:  
&nbsp;&nbsp;&nbsp;&nbsp; `bool clear (false)`  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;if true and the called object is a map, extra entries in the file will be deleted,  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;otherwise the new file will still contain unused entries (reformatted though)  
&nbsp;&nbsp;&nbsp;&nbsp; `std::string confFilename=""`  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;if specified, this overrides the filename

Note that each non-variable member of the map is a map itself, so you can call `vsr::save` and `vsr::load` on it. However, it loads/saves full entry depth: ie. the below example saves `["Map1"]["Map2"]["entry1"]` instead of just `["entry1"]`. Thus the purpose of this is to only update a portion of your config file, rather than the whole file. In this case setting `clear` will not remove any entries defined in `["Map1"]`, it just wont update them. If you specify `confFilename`, this simply overrides the top object's filename.

It is also possible to assign one map to another - this makes the entry point to the other map. NOTE: if the assigned map is destroyed and the other map tries to access it, it will segfault. Also the assigned map's defined confFilename is overriden by the key and the map now behaves like a part of the map it was assigned to, ie. calling `vsr::save` will show the whole hierarchy.
~~~cpp
    rtoml::vsr mapa;
    rtoml::vsr mapb;
    mapa["Map1"]["Map2"]=mapb;
    int a;
    mapb["entry1"]=a;   // equivalent to mapa["Map1"]["Map2"]["entry1"]=a;
~~~
Assigning the map again will throw an error. The map can have at most one parent.  

It is also possible to change the top object's save filename by using `void vsr::setConfFilename(std::string confFilename)`, and get it with `std::string vsr::getConfFilename()`. This can be called at any depth.

Similar to `vsr::load`, `vsr::changed` loads the file but does not update the map, it just checks for differences. If there is a difference, it returns true, else false.
~~~cpp
    bool changed = mapa.changed();
~~~
changed takes one optional argument:  
&nbsp;&nbsp;&nbsp;&nbsp; `std::string confFilename=""`  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;if specified, this overrides the filename


An usage example is given in example.cpp.

NOTE: supported variable types: arithmetic types (see `std::is_arithmetic`) and `std::string`  
however custom template classes with `typename T` (which has to be arithmetic or string) are supported if they have `T get()` and `set(T var)` functions defined
