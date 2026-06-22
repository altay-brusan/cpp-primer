# Chapter 18 — Standard Library Containers

> **Topic:** The Standard Library containers — sequential containers (vector,
> deque, list, forward_list, array), `span`/`mdspan`, the container adapters
> (queue, priority_queue, stack), ordered and unordered associative containers
> (map/set and their multi/unordered variants), the C++23 flat containers, and
> `bitset`.

## Samples (37 folders)

`01`–`13` build up `std::vector` (constructors, copy/assign/compare, iterators,
add/remove, move vs copy `push_back`, `emplace`, non-member size/`data`, capacity
reclaiming). `14` is a `RoundRobin` scheduler showing `reserve`/iterator
invalidation. `15`–`17` cover `list` (`splice`, list-specific ops) and
`forward_list`. `18` `std::array`, `19` `span`, `20` C++23 `mdspan`. `21`–`23` the
queue/priority_queue/stack adapters. `24` `pair`. `25`–`32` the associative
containers: `map` basics & lookup, node handles/`merge`, a `BankAccount` map, a
`BuddyList` multimap, an `AccessControlList` set, a custom `std::hash`,
`unordered_map`, and a `PhoneBook` with bucket introspection. `33` C++23
`flat_set`, `34` C-arrays as ranges, `35` `string` as a container, `36`–`37`
`bitset` (basics and a cable-subscription model).

## Build & run

```powershell
./run.ps1 -Chapter 18           # interactive: pick a sample, build & run
./run.ps1 -Verify -Chapter 18   # compile-check every sample (no run)
```

## Notes

- **Wait for keyboard input:** `01_TestScores/*` and `05_VectorIterators/01_TestScoresIterator`
  (read scores from `cin`).
- **Data files (included):** `16_StudentEnrollment` reads `course1.txt`–`course3.txt`
  and `dropped.txt` from its folder — run it from inside the folder.
- **Intentional UB demo:** `05_VectorIterators/04_IteratorSafety` deliberately misuses
  iterators (MSVC debug builds will assert at run time).
- **Require C++23:** `20_mdspan` (`<mdspan>`), `33_FlatContainerAdapters` (`<flat_set>`),
  and various range-formatting / `*_range` member uses.
- Many tiny example files intentionally produce no console output — they only show that
  an operation compiles.
