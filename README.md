# redll

The original [redgrep](https://github.com/google/redgrep)
generates DFA to JIT with LLVM.
This fork introduces redll, which outputs the constructed DFA as LLVM IR.

## Building

Same as original.

You must have GNU make, GNU bison and either GCC or Clang.

redgrep follows the "latest and greatest" in LLVM development, so you should
check out the source from
[Subversion](https://llvm.org/docs/GettingStarted.html#checkout-llvm-from-subversion)
or [Git](https://llvm.org/docs/GettingStarted.html#git-mirror), then configure,
build, check and install as per the
[instructions](https://llvm.org/docs/GettingStarted.html#getting-started-quickly-a-summary).
(Debian and Ubuntu users may prefer to install the
[nightly packages](https://apt.llvm.org/) instead.)

You should set the `LLVM_CONFIG` environment variable appropriately when you run
`make`.
