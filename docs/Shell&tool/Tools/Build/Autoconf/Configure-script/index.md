# configure script

1、一般，开源软件，很多采用的是这种方式

2、更好地支持cross-plateform

## wikipedia [configure script](https://en.wikipedia.org/wiki/Configure_script)

### Usage

```shell
./configure
make
make install
```



```shell
./configure --libs="-lmpfr -lgmp"
./configure --prefix=/home/user/local
```

### Generating `configure`

Software developers simplify the challenge of [cross-platform](https://en.wikipedia.org/wiki/Cross-platform) software development by using [GNU Autotools](https://en.wikipedia.org/wiki/GNU_Autotools).[[2\]](https://en.wikipedia.org/wiki/Configure_script#cite_note-2)

### Dependency checking

In new development, library dependency checking has been done in great part using [pkg-config](https://en.wikipedia.org/wiki/Pkg-config) via the [m4](https://en.wikipedia.org/wiki/M4_(computer_language)) macro, PKG_CHECK_MODULES. Before pkg-config gained popularity, separate m4 macros were created to locate files known to be included in the distribution of libraries depended upon.