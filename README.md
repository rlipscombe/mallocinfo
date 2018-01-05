# mallocinfo

A NIF that calls [malloc_info(3)](http://man7.org/linux/man-pages/man3/malloc_info.3.html).

## Build

    $ rebar3 compile

## Run

    ERL_LIBS=_build/default/lib erl
    1> l(mallocinfo).
    {module,mallocinfo}
    2> mallocinfo:info().
    ok
