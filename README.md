# mallocinfo

A NIF that calls [malloc_info(3)](http://man7.org/linux/man-pages/man3/malloc_info.3.html).

## Background

We're seeing our Erlang nodes use up more and more memory. Our current
suspicion is that it's caused not by Erlang heap fragmentation, but by libc
heap fragmentation caused by a NIF.

This NIF can be loaded into a running Erlang node and will dump the libc heap
information to an XML file.

## Build

    $ rebar3 compile

## Run

    ERL_LIBS=_build/default/lib erl
    1> l(mallocinfo).
    {module,mallocinfo}
    2> mallocinfo:info().
    ok

## Injecting into a running node

Locally:

    $ make tarball
    $ scp mallocinfo.tar.gz otherhost:.

On `otherhost`:

    $ tar xfz mallocinfo.tar.gz
    $ bin/blah remote_console

    1> code:add_path("/home/user/mallocinfo/ebin").
    {module,mallocinfo}.
    2> mallocinfo:info("/tmp/mallocinfo.xml").
    ok

## Inspecting the output

You'll need a couple of packages first:

    $ sudo apt-get install libxml2 python-pygments

Locally:

    $ scp otherhost:/tmp/mallocinfo.xml .

    $ xmllint --format mallocinfo.xml | pygmentize -l xml | less -R
