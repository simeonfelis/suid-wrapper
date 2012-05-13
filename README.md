suid-wrapper
============

C wrapper for scipts, as glibc dropps suid permissions in scripts (everything
beginning with #!/bin...)

The wrapper returns the original return value of your executed script. If
something inside the wrapper fails, it returns 255.

The wrapper supports up to 4 arguments to pass to the script. You can expand it
yourself. If you know a better way for flexible and safe way for argument
passing, let me know.

See main.c for licence.

Prerequesites:
  *  gnu make
  *  c compiler

Settings:
=========

All settings can be done in the makefile.

Install:
========

  *  make install

Uninstall:
==========

  *  make uninstall
