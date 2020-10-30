How Can You Look Object Module Using Microsoft Visual Studio?

* 1. [Open x86 Native Tools Command Prompt On Vs 20xx ](https://docs.microsoft.com/en-us/dotnet/framework/tools/developer-command-prompt-for-vs) 

* 2. `cd` to your workspace

* 3. use `cl [filename] /d1reportSingleClassLayout[Class]`

Command will display to you the information of c++ object module 

Ex:

You can easy use that `cl vis.cpp /d1reportSingleClassLayoutBase2 >>out.cpp`  to print object module information of Class `Base2` which save at c++ file `vis.cpp`, and rewrite to file `out.cpp`

You also can use `cl [filename] /d1reportAllClassLayout` to print All object module information 

