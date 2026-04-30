# Noxide
Simplified Zoxide written entirely in C.

Noxide is an alternative CD command that
allows you to warp between directories.

Example:

```sh
# With cd:
cd /var/lib/mpd

# With Noxide:
z mpd
```

If multiple possibilities exist,
it warps you to the oldest one.
To remove old memories run `noxide clean`.



## Commands

```sh
z # go home
z <path> # find path in the system
zi # open interactive path picker

noxide clean # remove history
```

## Installation

```sh
make install # will install at /usr/local/bin/noxide
echo 'eval "$(noxide init)"' >> ~/.bashrc # add initial script to your shell's rc
```
