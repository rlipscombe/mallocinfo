REBAR3 ?= ./rebar3

all: compile

compile:
	$(REBAR3) compile

tarball: compile
	tar -czh -f mallocinfo.tar.gz \
            -C _build/default/lib \
            mallocinfo/ebin mallocinfo/priv
