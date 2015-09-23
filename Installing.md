# Installing and linking tidypp on Linux #
  * Get automake 1.10 if you don't have it:
```
sudo apt-get install automake1.10
```
  * Get libtool if you don't have it:
```
sudo apt-get install libtool
```
  * Get git if you don't have it:
```
sudo apt-get install git
```
  * Get a copy of the source:
```
cd ~
git clone https://code.google.com/p/tidypp/
```
  * Build it:
```
cd tidypp
chmod u+x autogen.sh
./autogen.sh
make
sudo make install
sudo ldconfig
```
  * Add /usr/local/include/tidypp-1.0/ to your include directories when you compile your program:
```
g++ -c -o MyProgram.o -I/usr/local/include/tidypp-1.0/ MyProgram.cpp
```
  * Link your program to /usr/local/lib/libtidypp.la with libtool and add -ltidy to link tidylib:
```
libtool --mode=link g++ -g -O -o MyProgram MyProgram.o /usr/local/lib/libtidypp-1.0.la -ltidy -lm
```
  * You should now be able to run your program:
```
./MyProgram
```

# Installing and linking tidypp on Windows #
MinGW / MinGW based IDEs:
  * Download the binaries in the [downloads](http://code.google.com/p/tidypp/downloads/list) section and extract them.
  * Copy include and lib folders to your MinGW directory.
  * Add -ltidypp to your compiler settings.

MSVC / Others:
  * Download the binaries in the [downloads](http://code.google.com/p/tidypp/downloads/list) section and extract them.
  * Add the include folder to your include directories in the project settings.
  * Add lib/libtidypp.a to the libraries to link in the linker settings of your project.