This is a serie of C/C++ code about Windows' Winsock 2 API.

The code is a copy and reformating of code examples taken from this article:
https://www.winsocketdotnetworkprogramming.com/winsock2programming/winsock2advancedcode1chap.html

To compile examples, using Visual Studio:
* Create Console Window project

* Replace the default code by one of the example on this repo

* Add the follwing configs in the project
 --> Right Clight on the project 
 --> Properties
* Add in C/C++ > Preprocessor > Preprocessor Definitions
 value  _WINSOCK_DEPRECATED_NO_WARNINGS
  --> Project Settings > 
* Add in Linker > Input >  Additionnal Dependencies the value ws2_32.lib