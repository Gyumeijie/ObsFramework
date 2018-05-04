# ObsFramework

The OBS Framework is a research prototype of an object-oriented software framework for satellite on-board applications. Its purpose is to investigate and demonstrate how object-oriented and framework technology can be used to develop reusable and adaptable components for on-board applications.

It's written in c++ originally, but in this repo I rewrote it in c but still in the object-oriented way with using [qemu object model](https://github.com/Gyumeijie/qemu-object-model)(a.k.a. qom) as it's object model.

# Reasons for rewriting
There are Three main reasons why I spent time to rewrite the OBS Framework.

- Mix programming with [Ada](https://en.wikipedia.org/wiki/Ada_(programming_language))
> For c++ cann't mixed with Ada, but c do.

- Reducing program size 
> As we all know, c++ code occupied lot of space, and it is not ideally used in environment which has limited memory size.
So I try reducing the size by rewriting it with c.

- Portability
> C programming language has a better portability than c++.

# Links
For more information about OBS Framework, you can visit the following site, which introduces it very specifically.

- [The OBS Framework Project](https://www.pnp-software.com/ObsFramework/)
