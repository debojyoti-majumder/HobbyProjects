I am trying to build DceRPC from https://github.com/dcerpc/dcerpc on Ubuntu VM and these are dependencies that are requires. Of course prepend sudo before the commands

1. apt install libtool
2. apt install flex
3. apt install bison
4. apt install autoconf

Then in the local checked out directory run
./bootstrap

This should create the configure command. Once that is done we can run 
./configure

After running this we should be able to see Makefile being present on the working direcoty then run 

make

The build did not gave me any error and then I did the following 

make install

This ideally should put the binaries and libraries in place
