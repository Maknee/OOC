[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Build Status](https://travis-ci.com/Maknee/OOC.svg?token=awrLzay2NUpTLyLqBpuQ&branch=master)](https://travis-ci.com/Maknee/OOC)
[![Documentation](https://codedocs.xyz/Maknee/OOC.svg)](https://codedocs.xyz/Maknee/OOC/)
[![Coverage Status](https://coveralls.io/repos/github/Maknee/OOC/badge.svg?branch=master)](https://coveralls.io/github/Maknee/OOC?branch=master)
## Credits

Explanations of implementing object oriented in c

https://stackoverflow.com/questions/2181079/object-oriented-programming-in-c

Great Travis CI testing C example

https://github.com/softwaresaved/build_and_test_examples

RTTI
http://www.openrce.org/articles/full_view/23
https://www.blackhat.com/presentations/bh-dc-07/Sabanal_Yason/Paper/bh-dc-07-Sabanal_Yason-WP.pdf

## To Do

Document specifications
Finish string class
Test string class
Test on linux and create makefile
Implement Dynamic cast (upcast/downcast)
Provide Examples

## ?Wonderings, pondering, design decisions?

Should constructors just set vftable pointer to super's vftable or should the super's vftable be memcpy'ed into the dervied pointer?

Leaning towards memcpy

Reason:
No point in just setting the pointer if the pointer is just going to be overwritten...

Inefficient setting of variables in vtable, but necessary to call once. Easier to design, less code though...
