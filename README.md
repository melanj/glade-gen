# Gladegen - Code Generator for Glade
Gladegen is a program written in C that takes a Glade XML file and generates skeleton code. The main goal of this is to generate a C code to load Glade file into GtkBuilder and initiate the widgets and but not to automatically generates all the source code for a graphical control element.

### Built With
* C
* [libxml2](https://gitlab.gnome.org/GNOME/libxml2)

### Prerequisites
* make
* gcc (or compilable)
* libxml2-dev

### Install prerequisites
You can install libxml2-dev (or its equivalent) based on your Linux distribution:  

Debian/Ubuntu-based distributions  

   ```sh
   sudo apt-get install libxml2-dev
   ```
RPM-based distributions
Use dnf (or yum on older versions):

   ```sh
   sudo dnf install libxml2-devel
   ```


### Installation

use the Makefile to build the executable and add `gladegen` to the system path. 
e.g

   ```sh
   make
   ```

or if you wants to rebuild everything, regardless of timestamps

   ```sh
   make -B all
   ```

### Usage
Open a terminal, change the directory to a glade file location and run the `gladegen` as follows. source code will generate in the same directory. 
   ```sh
   gladegen <Glade XML file>
   ```
e.g

   ```sh
   gladegen sample.glade
   ```

### Roadmap

- [x] Support to generate minimum C skeleton code
- [ ] Implement command line options
- [ ] Glade resource file generation
- [ ] Makefile generation
- [ ] Move to template based code generation
- [ ] Provide a simple UI as an alternative to command line

### License
Distributed under the BSD Zero Clause License. See `LICENSE.MD` for more information.
