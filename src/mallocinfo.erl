-module(mallocinfo).
-export([info/1]).
-define(NOT_LOADED, not_loaded(?LINE)).
-compile([no_native]).
-on_load(on_load/0).

on_load() ->
    % Error checking left as an exercise.
    PrivDir = code:priv_dir(?MODULE),
    Nif = filename:join(PrivDir, "mallocinfo"),
    erlang:load_nif(Nif, 0).

not_loaded(Line) ->
    erlang:nif_error({not_loaded, [{module, ?MODULE}, {line, Line}]}).

info(_Path) ->
    ?NOT_LOADED.
