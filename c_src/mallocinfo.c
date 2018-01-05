#include "erl_nif.h"
#include <stdio.h>
#include <linux/limits.h>
#include <malloc.h>
#include <errno.h>

static ERL_NIF_TERM a_ok;
static ERL_NIF_TERM a_error;

static int on_load(ErlNifEnv *env, void **priv, ERL_NIF_TERM info)
{
    a_ok = enif_make_atom(env, "ok");
    a_error = enif_make_atom(env, "error");
    return 0;
}

static ERL_NIF_TERM info(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[])
{
    char path[PATH_MAX];
    int options = 0;    // must be zero
    FILE *stream;

    if (argc != 1) {
        return enif_make_badarg(env);
    }

    if (enif_get_string(env, argv[0], path, PATH_MAX, ERL_NIF_LATIN1) <= 0) {
        return enif_make_badarg(env);
    }

    stream = fopen(path, "w");
    if (!stream) {
        return enif_make_tuple2(env, a_error, enif_make_int(env, errno));
    }

    ERL_NIF_TERM result;
    if (malloc_info(options, stream) == 0) {
        result = a_ok;
    }
    else {
        result = enif_make_tuple2(env, a_error, enif_make_int(env, errno));
    }

    fclose(stream);
    return result;
}

static ErlNifFunc funcs[] =
{
    {"info", 1, info}
};

ERL_NIF_INIT(mallocinfo, funcs, on_load, NULL, NULL, NULL)
