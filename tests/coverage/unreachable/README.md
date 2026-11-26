# Unreachable branch outcomes

Branch outcomes the unit tests cannot cover, with the reason: one TSV per object directory, `engine.csv` for the
other files in `src/main/`. `outcome` is `taken`, `not-taken` or `both`.

Classes: `unreachable-logic`, `dead-code`, `data-dependent`, `platform-only`, `crashes-everywhere`,
`requires-sdk`, `requires-hardware`, `hardware-or-library`, `needs-tooling`, `unobservable-on-host` (runs, but the test host cannot
observe the effect). Evidence may start with `[saturn-only]` or `[proto-only]`, or contain `[derived count]`
(llvm-cov reports a count for an outcome that never happens).
