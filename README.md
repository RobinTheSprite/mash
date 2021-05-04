# mash
A Windows shell with a few simple commands

This was a project for CS321 Operating systems, which I took in 2019 from Orion Lawlor at the University of Alaska Fairbanks. I was dissatisfied with Windows' default command prompt, so I wrote my own. I called it MASH, which stands for Mark's Awesome SHell, or Mark's Awful SHell, depending on its performance at any given moment.

I am writing this README quite a few years later, so forgive me if it is somewhat hazy on the details.

## Design

There is one main executable, which parses input and creates new processes, and many other, smaller executables for specific tasks. Shells are modular by design in this respect, since basically the only thing one needs to do to add more commands is write a new execuatable and stick it in with the rest. That's pretty fun.

The whole thing is written in C++ using Windows' C++ system API. C++ was a no-brainer, since it was my main language in college and was also fast. The Windows API was a necessary evil following from that decision. To demonstrate, on Unix systems, the function call to create a new process is fork(), just like that. No arguments. The function used to create a new process using this API is CreateProcess(), which takes **TEN** arguments. I did not even need to use five of the arguments, so I had to pass `nullptr`.

## Results

MASH is not the fastest kid on the block, consistently getting slower times than equivalent Linux commands. If it is not fast, then perhaps C++ was not the best choice. If I had known more about Rust or Go at the time I wrote this, I may have used the opportunity to try one of them out. They both compile to native executables, and probably would have had far better tools for interacting with the OS.
