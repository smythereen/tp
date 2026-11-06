# tp — transactions per second / minute / hour / day

`tp` keeps rolling **transaction-rate counters** in memory-mapped files. Each
counter is a fixed-size ring of per-interval counts plus running statistics:
`Count`, `Maximum`, `Average`, `TP` (current interval), `Total` (over the
range) and `Stamp` (last interval). It is meant for long-running servers that
need cheap "how many per second / per day" figures that other processes can
read from the mapped file.

## Ranges (`tp.h`)

| Type | Interval | Ring length | Covers |
|------|----------|-------------|--------|
| `tps_t` | 1 s | 600 | 10 minutes |
| `tpm_t` | 60 s | 60 | 1 hour |
| `tph_t` | 3600 s | 168 | 1 week |
| `tpd_t` | 86400 s | 365 | 1 year |
| `tp_t` | — | — | a `tps_t`, a `tpd_t` and a `tpd_file[64]` name |

`tpd.h`, `tph.h` and `tps.h` are convenience headers that include `tp.h`.

## How a client uses it

For each range `X` in `TPS`, `TPM`, `TPH`, `TPD` (and `TP` for `tp_t`):

- `X_Initialize(p)`: zero and set up a counter.
- `X_Add(p, n[, file])` / `X_Bump(p[, file])`: add `n` / add 1 to the current interval.
- `X_Check(p[, file])`: roll intervals forward when the clock has moved.
- `X_Interval(p[, file])`: close the current interval.

The `file` argument (minute, hour and day ranges) is a data file where completed
intervals are written. Generic forms (`tp_Initialize`, `tp_Add`, …, taking a
`TP_t *` and a ring size), `tp_File(file, max)` (map a counter file sized for
`max`) and `TP_File_Bump(file)` are also exported.

Typical use: map the counter with `map` (`MapFile2Mem(file, sizeof(tps_t), PROT_WRITE)`)
or `tp_File`, call `TPS_Bump()` for each transaction, and read
`TP`/`Average`/`Maximum` from any process that maps the same file.

## Utility programs (in the source)

- `tp`, `tps`, `tpm`, `tph`, `tpd`: `FILE.mem a[dd] | b[ump] | c[heck] | i[nitialize]`
  on a mapped counter file. They print fields such as `tp->tps.TP=…`.
- `tpmem`, `tpsmem`, `tpmmem`, `tphmem`, `tpdmem`: `FILE.mem [field [value]]`
  shows all fields, shows one, or sets one. They use `mio`
  (`Input_Memory_Item` / `Output_Memory_Item` with the `tp_l`, `tps_l`, … tables)
  and `UpdateMap`.

This unit has no test suite. No sample output is shown because none was
captured from a verified build.

## Build notes

The makefile builds `libtp.a` and symlinks `libtpd.a`, `libtph.a` and
`libtps.a` to it. `LIBRARIES = -lmio -lnow -lmap -lsem -lfar -lsys`. The
`-lmsg -laddr` entries from `v0.1.0` are gone; tp needs no messaging or
address unit.

## Dependencies

| Unit | Kind | Evidence |
|------|------|----------|
| `sys` | direct | `tp.h` includes `<common.h>` |
| `atomic` | direct (header only) | `tplocal.h` includes `<atomic_32.h>` |
| `far` | direct | `tplocal.h` includes `<far.h>` |
| `map` | direct | `<map.h>`; `file.c` and the tools call `MapFile2Mem` and `UpdateMap` |
| `mio` | direct | `tplocal.h` includes `<mem_io.h>`; the `*_fmt.c` files define `Mitem` tables |
| `sem` | indirect (link) | not used by tp's own source; `map` calls `SemFree` (`map/unmap.c`), so `-lsem` is needed to link |
| `now` | indirect (link) | not used by tp's own source; required by `mio` |

`UNIT.deps` lists `far map mio now sem sys`. `atomic` is used through its
header only.

## Getting it

Requires the `base` repository (project root with `BASE`, `rules.mak`,
`targets.mak` and the `repo` unit). A plain `make` in a fresh base clone
fetches the starter list (project `NONE`), which is, in dependency order:

```
sys atomic far map sem now mio tp tpi
```

Or add this unit on its own with `repo add <unit>`.

## Using this unit from C++

This unit can be used from **C and C++**. Keep the unit's `.c` implementation
files compiled as C with `gcc`/`CC`; compile your C++ client with `g++`/`CXX`
and use `g++` for the final mixed-language link. There is no need to rebuild
the C library as C++.

Base's shared rules recognize C++ product sources named `.cc` and compile
them with `CXX` and `CXXFLAGS` (for example `make CXX=g++`). `CPP` names
the preprocessor, not the C++ compiler. The commands below assume the
headers and libraries have already been installed into `$HOME/cmn` and
`$HOME/lib`. GNU C++17 on Linux x86-64 is the example target; GNU extensions
in the shared types/headers are intentional.

`tp.h`, `tps.h`, `tph.h` and `tpd.h` already provide C linkage, including
through nested `common.h`; no caller `extern "C"` wrapper is required.
The `TpProto` expansion creates distinct anonymous-struct typedefs. Use
`tps_t`, `tpm_t`, `tph_t`, `tpd_t` and their matching uppercase public APIs;
do not redeclare them as `struct tps_t` or assume they implicitly convert to
`TP_t *` in C++. `TP_t` uses a GNU zero-length tail array. Keep the default
`TP_NEW` setting consistent with the C-built library: do not enable it only
in a C++ client, since that changes the shared layout.

Save as `use_tp.cc`:

```cpp
#include <tp.h>
int main() {
    tps_t counter{};
    TPS_Initialize(&counter);
    TPS_Bump(&counter);
    return counter.Count == 1 ? 0 : 1;
}
```

```sh
g++ -std=gnu++17 -I"$HOME/cmn" use_tp.cc -L"$HOME/lib" -ltp -lmio -lnow -lmap -lsem -lfar -lsys -lquadmath -lm -o use_tp
./use_tp
```

The C++ example above was compiled, linked and run on Linux x86-64 using
Clang 22.1.8 via `zig c++ -std=gnu++17 -nostdlib++`, with GCC 14.2-built C
objects where needed. It uses no C++ standard-library runtime. The `g++`
command is the GNU-toolchain form; that driver was not available for this
smoke check. This is not an exhaustive API or concurrency test.

## License

The original files are offered under `Apache-2.0 OR GPL-2.0-or-later`;
you choose either license. See `LICENSE` and `LICENSES/`. Copyright notices
are retained; third-party-derived files keep their own SPDX identifiers.

## Version

Version tag: `v0.2.0`.
