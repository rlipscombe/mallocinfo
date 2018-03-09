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
    2> mallocinfo:info("/tmp/mallocinfo.xml").
    ok
    3> mallocinfo:stats().
    ok

## Injecting into a running node

Locally:

    $ make tarball
    $ scp mallocinfo.tar.gz otherhost:.

On `otherhost`:

    $ tar xfz mallocinfo.tar.gz
    $ bin/blah remote_console

    1> code:add_path("/home/user/mallocinfo/ebin").
    true
    2> l(mallocinfo).
    {module,mallocinfo}.
    3> mallocinfo:info("/tmp/mallocinfo.xml").
    ok

Alternatively:

    3> mallocinfo:stats().
    ok

The output from `mallocinfo:stats/0` goes to standard error, so where it
ultimately ends up depends on your environment. At Electric Imp, we use
`logger` to forward it to syslog.

Press Ctrl+C twice to disconnect the remote console.

## Inspecting the stats output

`mallocinfo:stats/0` calls `malloc_stats()`, which prints allocator statistics
to standard error. It looks something like this:

    Arena 0:
    system bytes     =     303104
    in use bytes     =     301488
    Arena 1:
    system bytes     =  103809024
    in use bytes     =   98866320

...etc.

## Inspecting the XML output

You'll need a couple of packages first:

    $ sudo apt-get install libxml2 python-pygments

Locally:

    $ scp otherhost:/tmp/mallocinfo.xml .

    $ xmllint --format mallocinfo.xml | pygmentize -l xml | less -R

The interesting values are:

    <total type="fast" count="93" size="8752"/>
    <total type="rest" count="113379" size="4977315"/>
    <system type="current" size="108421120"/>

`current` corresponds to `system bytes`; `current - (fast + rest)` corresponds
to `in use bytes`.
