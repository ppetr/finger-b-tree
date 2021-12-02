# Finger B-trees for C++

**Disclaimer:* This is not an officially supported Google product.*

## Objective

Implement efficient, general purpose finger [B-tree] data structure on a par
with open-source Google [Abseil](https://abseil.io/) tree data structures such
as [`absl::btree_set`] or [`absl::btree_map`]

[`absl::btree_set`]: https://github.com/abseil/abseil-cpp/blob/master/absl/container/btree_set.h
[`absl::btree_map`]: https://github.com/abseil/abseil-cpp/blob/master/absl/container/btree_map.h

[Finger trees], lesser known outside the world of functional programming, have
the same asymptotic characteristics as regular trees for general operations, but
allow *O(1)* amortized time complexity on the leftmost and rightmost node.

[B-tree]: https://en.wikipedia.org/wiki/B-tree
[Finger trees]: https://en.wikipedia.org/wiki/Finger_tree

The implemented data structure will be:

-   Move-only for move-only elements.
-   Copyable for copyable elements, with efficient sharing using a
    [copy-on-write] technique, which avoids copying by sharing common nodes
    (similar to [`absl::Cord`] and [`absl::Status`]).

[copy-on-write]: https://github.com/ppetr/refcounted-var-sized-class/blob/main/copy_on_write.h
[`absl::Cord`]: https://github.com/abseil/abseil-cpp/blob/master/absl/strings/cord.h
[`absl::Status`]: https://github.com/abseil/abseil-cpp/tree/master/absl/status

By combining it with appropriate monoids (see [this blog-post][monoids]), derive
further data structures, including:

-   Sequences with *O(1)* access to its ends (sum monoid, each element with
    value of 1). Thus constructing a sequence by appending/prepending n elements
    is *O(n)*.
-   Cord, ditto (sum monoid, each element with value of its size).
-   Sorted set/map with *O(1)* access to minimum and maximum (maximum monoid,
    each element is its own monoid value). In particular, constructing such a
    sorted set from a list of already ordered elements has *O(n)* time
    complexity, compared to O(n log n) for the standard tree data structure.

-   Priority queue (maximum monoid, each element with value of its priority) -
    priority queue with *O(1)* access to the first (and last) element.

[monoids]: https://apfelmus.nfshost.com/articles/monoid-fingertree.html

## Contributions

Please see [Code of Conduct](docs/code-of-conduct.md) and
[Contributing](docs/contributing.md).
