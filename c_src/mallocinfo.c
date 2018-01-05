#include "erl_nif.h"

static ERL_NIF_TERM a_ok;

static int on_load(ErlNifEnv *env, void **priv, ERL_NIF_TERM info)
{
    a_ok = enif_make_atom(env, "ok");
    return 0;
}

static ERL_NIF_TERM info(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[])
{
    return a_ok;
}

static ErlNifFunc funcs[] =
{
    {"info", 0, info}
};

ERL_NIF_INIT(mallocinfo, funcs, on_load, NULL, NULL, NULL)
