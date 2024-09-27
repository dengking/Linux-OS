# [Accelerate](https://developer.apple.com/documentation/accelerate)

```
lapack is keg-only, which means it was not symlinked into /opt/homebrew,
because macOS provides LAPACK in Accelerate.framework.

For compilers to find lapack you may need to set:
  export LDFLAGS="-L/opt/homebrew/opt/lapack/lib"
  export CPPFLAGS="-I/opt/homebrew/opt/lapack/include"

For pkg-config to find lapack you may need to set:
  export PKG_CONFIG_PATH="/opt/homebrew/opt/lapack/lib/pkgconfig"
```

