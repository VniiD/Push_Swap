*This project has been created as part of the 42 curriculum by <login1>, <login2>.*

# push_swap

> Because Swap_push doesn't feel as natural.

## Table of Contents

- [Description](#description)
- [The rules](#the-rules)
- [Instructions](#instructions)
  - [Compilation](#compilation)
  - [Usage](#usage)
  - [Strategy selectors](#strategy-selectors)
  - [Benchmark mode](#benchmark-mode)
  - [Error handling](#error-handling)
- [Disorder metric](#disorder-metric)
- [Algorithms — technical choices and justification](#algorithms--technical-choices-and-justification)
  - [1. Simple — O(n²)](#1-simple--on²)
  - [2. Medium — O(n√n)](#2-medium--onn)
  - [3. Complex — O(n log n)](#3-complex--on-log-n)
  - [4. Adaptive (our design)](#4-adaptive-our-design)
- [Complexity argument (time & space)](#complexity-argument-time--space)
- [Known limitations / points to double-check](#known-limitations--points-to-double-check)
- [Bonus — the checker program](#bonus--the-checker-program)
- [Project structure](#project-structure)
- [Contributions](#contributions)
- [Resources](#resources)

## Description

**push_swap** is a 42 School group project about algorithmic complexity, applied in
a very concrete and constrained way: you are given a stack of unsorted integers (`a`)
and an empty helper stack (`b`), and a small set of operations to move values between
them. The goal is to write a C program that outputs, on `stdout`, the **shortest
possible sequence** of these operations that sorts stack `a` in ascending order.

This repository implements:

- The **mandatory** `push_swap` binary, which embeds **four distinct sorting
  strategies** (`simple`, `medium`, `complex`, `adaptive`) selectable at runtime.
- A **disorder metric**, computed before any operation is executed, that measures
  how far the input is from being sorted (`0.0` = already sorted, `1.0` = worst case).
- An optional `--count-only` **benchmark mode** that reports the disorder, the
  strategy used, the total operation count, and a per-operation breakdown on `stderr`.
- The **bonus** `checker` binary, which replays a sequence of operations read from
  `stdin` against the stack given as arguments and reports whether it results in a
  correctly sorted stack (`OK`) or not (`KO`).

## The rules

- Two stacks, `a` and `b`. `a` starts with the (duplicate-free) integers passed as
  arguments; `b` starts empty.
- Allowed operations: `sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr`.
- Every operation is printed to `stdout`, one per line, and nothing else.
- On any invalid input (non-integer, out-of-`int`-range value, duplicate), the program
  must print `Error` on `stderr` and stop.

## Instructions

### Compilation

```bash
make          # builds the mandatory push_swap binary
make bonus    # builds the bonus checker binary
make clean    # removes object files
make fclean   # removes object files and binaries
make re       # fclean + all
```

The `Makefile` compiles with `cc -Wall -Wextra -Werror` and does not relink unnecessarily.

### Usage

```bash
./push_swap [selector] [--count-only] <numbers>
```

`<numbers>` can be passed either as several arguments or as a single quoted,
space-separated string (both are supported, since each argument is internally
split on spaces):

```bash
./push_swap 2 1 3 6 5 8
./push_swap "2 1 3 6 5 8"
```

If no numeric arguments are given, the program prints nothing and returns the
prompt (exit code `0`).

### Strategy selectors

| Flag          | Strategy forced                | Complexity class |
|---------------|---------------------------------|-------------------|
| *(none)*      | Adaptive (default)              | see below         |
| `--simple`    | Simple                          | O(n²)             |
| `--medium`    | Medium                          | O(n√n)            |
| `--complex`   | Complex                         | O(n log n)        |
| `--adaptive`  | Adaptive                        | see below         |

Example:

```bash
$ ./push_swap --simple 5 4 3 2 1
rra
pb
rra
pb
rra
pb
ra
pb
pb
pa
pa
pa
pa
pa
```

### Benchmark mode

> **Note:** in this implementation the benchmark flag is `--count-only`
> (see [Known limitations](#known-limitations--points-to-double-check) below —
> the subject names it `--bench`).

When `--count-only` is passed, sorting operations still go to `stdout` as usual,
but a metrics block is additionally written to `stderr`:

```bash
$ ARG="4 67 3 87 23"; ./push_swap --count-only --adaptive $ARG 2> bench.txt | ./checker $ARG
OK
$ cat bench.txt
[bench] disorder:
40.00%
[bench] strategy:
adaptive
[bench] total_ops:
13
```

The metrics reported are: the computed disorder (as a percentage), the strategy
that ran, and the total number of operations generated.

### Error handling

```bash
$ ./push_swap --adaptive 0 one 2 3
Error
$ ./push_swap --simple 3 2 3
Error
```

Validation is done in `utils_parsing.c` (`ft_atoi_strict`, duplicate check against
already-pushed values) and enforced via `exit_error`, which frees all allocated
memory before printing `Error` on `stderr` and exiting with status `1`.

## Disorder metric

Disorder is computed **before any operation is executed**, in `disorder.c`, by
counting *inversions* — pairs `(i, j)` with `i < j` where `a[i] > a[j]` — over the
total number of pairs:

```
disorder = mistakes / total_pairs
```

- `disorder == 0.0` → the stack is already sorted.
- `disorder == 1.0` → the stack is in the exact reverse (worst) order.
- Anything in between → partially sorted input.

This value drives the strategy selection in the adaptive algorithm.

## Algorithms — technical choices and justification

### 1. Simple — O(n²)

**File:** `strat_simple.c`, `utils_simple.c`

For 3 elements or fewer, `sort_three` resolves the arrangement directly using
comparisons and at most two operations. For larger stacks, the algorithm behaves
like a **selection sort adapted to the two-stack model**:

1. Find the index of the current minimum of `a` (`find_min_idx`) — O(n).
2. Rotate it to the top using whichever of `ra`/`rra` is cheaper
   (`rotate_min_to_top`) — up to O(n).
3. Push it to `b` (`pb`).
4. Repeat until 3 or fewer elements remain in `a`, resolve them with `sort_three`,
   then push everything back from `b` to `a` (`pa`).

Since steps 1–3 are each O(n) and are repeated O(n) times, the total operation
count is **O(n²)** — this is the intended baseline complexity class.

### 2. Medium — O(n√n)

**File:** `strat_medium.c`, `utils_medium.c`

This is a **chunk-based partitioning** strategy:

1. A sorted copy of the input is produced (`sort_temp_array`, a straightforward
   O(n²) in-memory sort used only to know the target order — it does not count
   towards the push_swap operation cost).
2. `a` is split into chunks (`get_chunk_size`: a fixed size of 18 for `n ≤ 100`,
   otherwise `n / 10` — i.e. roughly `√n`-sized groups). Elements are pushed to
   `b` chunk by chunk, keeping each chunk loosely ordered with an occasional `rb`
   (`push_chunk_to_b`).
3. `b` is then unwound: repeatedly find the current max of `b`, rotate it to the
   top with the cheaper of `rb`/`rrb`, and push it back to `a` (`pa`), which
   naturally rebuilds ascending order from the bottom up.

Because the stack is processed in roughly `√n` chunks of `√n` elements each, with
O(√n) work per chunk boundary, the overall operation count falls in the
**O(n√n)** class.

### 3. Complex — O(n log n)

**File:** `strat_complex.c`

This is a **cost-based greedy insertion** strategy (a common push_swap technique,
sometimes called the "Turk algorithm" in the 42 community):

1. All elements beyond the first 3 are pushed to `b`; the remaining 3 in `a` are
   sorted with `sort_simple`.
2. While `b` is not empty, for every element in `b` the algorithm computes:
   - the index in `a` of its future insertion target (`find_target_in_a`: the
     smallest value in `a` greater than the candidate, wrapping to the current
     minimum if none exists),
   - the rotation cost to bring that target to the top of `a`,
   - the rotation cost to bring the candidate to the top of `b`,
   - a combined cost (`get_abs_cost`) that accounts for rotations shared between
     `a` and `b` via `rr`/`rrr`.
   The cheapest candidate is chosen (`get_best_move`), the corresponding
   rotations are executed (`exec_rotations`), and the element is pushed back to
   `a` (`pa`).
3. A final rotation brings the overall minimum of `a` to the top.

Because each insertion picks a near-optimal position instead of a fixed scan,
this greedy heuristic empirically produces operation counts that scale close to
**O(n log n)** for random inputs, which is why it is classified in this project
as our complex-tier strategy. Unlike a textbook merge/radix/heap sort, this is a
heuristic rather than an algorithm with a formally proven upper bound — see the
note below.

### 4. Adaptive (our design)

**File:** `strat_adaptive.c`

`sort_adaptive` computes the disorder, then dispatches to one of the strategies
above through `execute_regime`:

```c
if (prog->a.size <= 5)
    sort_simple(prog, op_count);
else if (prog->disorder < 0.15)
    sort_medium(prog, sorted, op_count);
else
{
    normalize_stack_a(prog, sorted);
    sort_complex(prog, op_count);
}
```

**Rationale for the thresholds actually implemented:**

- **`size ≤ 5`** always uses the simple strategy: for such tiny stacks, the
  O(n²) baseline is essentially free (at most 25 notional comparisons), and the
  overhead of chunking or cost computation isn't worth it.
- **`disorder < 0.15`** uses the medium (chunk-based) strategy: a low-disorder
  stack is close to already sorted, so a coarse chunk pass is enough to reach a
  near-sorted state cheaply, without the bookkeeping cost of the greedy
  insertion method.
- **`disorder ≥ 0.15`** normalizes stack `a` to rank indices (`normalize_stack_a`)
  and runs the complex (cost-based) strategy, which scales better as the number
  of "wrong" pairs grows.

## Complexity argument (time & space)

- **Time**, measured in generated push_swap operations:
  - Simple: O(n²) — one O(n) min-search + O(n) rotation, repeated n times.
  - Medium: O(n√n) — √n chunks, each requiring O(√n) positioning work.
  - Complex: O(n log n) in practice — one cost evaluation over `b` (O(n)) repeated
    n times in the worst theoretical case, but the target-selection heuristic
    keeps the *effective* operation count close to n log n for random inputs.
  - Adaptive: whichever of the above is dispatched, bounded by the regime above.
- **Space:** all strategies operate in-place on the two fixed-capacity arrays
  (`t_stack.data`) allocated once in `init_program`. The only extra allocation is
  a temporary `int` array of size `n` used to know the sorted target order
  (`sort_temp_array` / `sort_int_array`), which is freed immediately after use.
  Overall auxiliary space is **O(n)**, and all of it is freed before the program
  exits (`free_program`) or on error (`exit_error`).

## Known limitations / points to double-check

Being transparent about the current state of the implementation (per the
project's AI-usage guidelines, everything generated or drafted must be
understood and verified before the defense):

- **Benchmark flag naming:** the subject specifies `--bench`; this codebase
  implements the same behaviour under the flag `--count-only`
  (see `parser_main.c`). Confirm with your evaluator whether this needs to be
  renamed/aliased to match the subject exactly.
- **Adaptive thresholds:** the subject's required regimes are
  `disorder < 0.2` → O(n²), `0.2 ≤ disorder < 0.5` → O(n√n), `disorder ≥ 0.5` →
  O(n log n). The current implementation only distinguishes two disorder
  thresholds (`size ≤ 5` for simple, `disorder < 0.15` for medium, otherwise
  complex) and never routes large, low-disorder stacks to the simple O(n²)
  strategy. Double-check whether this needs to be adjusted to explicitly cover
  all three subject-mandated regimes before your evaluation.
- **Benchmark output format:** the subject's example shows metrics on the same
  line as their label (e.g. `[bench] disorder: 49.93%`); this implementation
  prints the label and value on separate lines (`writer.c`). Purely cosmetic,
  but worth confirming it satisfies your evaluator.
- **Complex strategy complexity claim:** as noted above, the O(n log n) class is
  an empirical property of the greedy cost heuristic for random inputs, not a
  formally proven worst-case bound (unlike merge sort or radix sort). Be ready
  to explain this distinction during the defense.

## Bonus — the checker program

**Files:** `checker_bonus.c`, `checker_op_bonus.c`, `main_bonus.c`

```bash
$ ./checker 3 2 1 0
rra
pb
sa
rra
pa
OK
```

`checker` takes the same stack-`a` arguments as `push_swap`, then reads
operations from `stdin` (one per line, via `read_line`) and applies them
(`execute_checker_op`) using the same underlying stack primitives
(`op_swap`, `op_push`, `op_rotate`, `op_reverse_rotate`) as the mandatory part.
Once `stdin` is exhausted, it prints `OK` if `a` ends up sorted and `b` is
empty, `KO` otherwise, and `Error` on `stderr` for any malformed input or
unknown instruction.

## Project structure

```
push_swap.h              Shared types & prototypes
main.c                   Mandatory entry point / strategy dispatch
main_bonus.c             Bonus (checker) entry point

parser_main.c            Argument parsing / flag handling
utils_parsing.c          Strict atoi + duplicate validation
utils_split.c            ft_split (argument tokenizing)
utils_memory.c           init_program / free_program / exit_error
disorder.c               compute_disorder

op_swap_push.c           op_swap, op_push
op_rot_revrot.c          op_rotate, op_reverse_rotate
op_wrappers.c             exec_sa / exec_sb / exec_pa / exec_pb (+ print_op)
op_wrappers_rot.c         exec_ra / exec_rb / exec_rra / exec_rrb
op_wrappers_double.c      exec_ss / exec_rr / exec_rrr

strat_simple.c            O(n²) strategy
utils_simple.c            rotate_min_to_top, sort_three
strat_medium.c             O(n√n) strategy
utils_medium.c             sort_temp_array, run_forced_medium
strat_complex.c            O(n log n) strategy
strat_adaptive.c           adaptive dispatcher

writer.c                  print_op, print_bench_metrics

checker_bonus.c            read_line, check_result
checker_op_bonus.c         execute_checker_op
```

## Contributions

> Both learners must be listed as contributors on the Git repository and both
> must be able to explain and defend any part of the code during the peer
> evaluation. Please fill in the specifics below.

| Learner    | Main areas of contribution |
|------------|------------------------------|
| `<login1>` | *e.g. parsing, memory management, operation primitives, simple & medium strategies* |
| `<login2>` | *e.g. complex & adaptive strategies, disorder metric, benchmark mode, bonus checker* |

*(Replace with an accurate, specific breakdown of who worked on which files —
both learners must understand every part regardless of who wrote it first.)*

## Resources

- 42 School — *push_swap* subject (this repository's `en_subject.pdf`).
- Wikipedia — [Big O notation](https://en.wikipedia.org/wiki/Big_O_notation)
- Wikipedia — [Selection sort](https://en.wikipedia.org/wiki/Selection_sort),
  [Sorting algorithm](https://en.wikipedia.org/wiki/Sorting_algorithm) (general
  background for the simple/medium strategies).
- Community write-ups on 42's "Turk algorithm" / cost-based push_swap
  approaches (background for the complex strategy's target-cost heuristic).

**AI usage disclosure:** 
