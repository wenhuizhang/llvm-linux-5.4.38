# llvm-linux-5.4.38

1. get source code for 5.4.38

```
wget https://mirrors.edge.kernel.org/pub/linux/kernel/v5.x/linux-5.4.38.tar.gz 
tar -xvf linux-5.4.38.tar.gz
rm linux-5.4.38.tar.gz
```
2. compile
```
export PATH=$LLVM_HOME/build/bin:$PATH
make -j4 LD=ld.lld HOSTLDFLAGS=-fuse-ld=lld KGZIP=pigz
```
