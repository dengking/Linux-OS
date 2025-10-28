# eBPF

**Ingo Molnár wrote:**

> One of the more interesting features in this cycle is the ability to attach eBPF programs (user-defined, sandboxed bytecode executed by the kernel) to kprobes. This allows user-defined instrumentation on a live kernel image that can never crash, hang or interfere with the kernel negatively.

---

Explanation

- **eBPF** (extended Berkeley Packet Filter) is a virtual machine inside the Linux kernel, able to safely execute user-defined bytecode.
- **Kprobes** allow users to dynamically instrument nearly any function in the kernel, at runtime.
- By attaching eBPF programs to kprobes, users can insert custom instrumentation logic (for tracing, monitoring, debugging), safely and efficiently. Because eBPF execution is verified and constrained, these programs can run in the kernel without fear of causing crashes, hangs, or interfering with normal kernel operation.

## [wikipedia eBPF](https://en.wikipedia.org/wiki/EBPF)

## [eBPF](https://ebpf.io/)


