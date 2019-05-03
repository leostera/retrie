# retrie
> A quick and dirty trie, possibly broken in more than one way

I originally started with an algebraic datatype like:

```reason
type t =
  | Node(list(edge))
  | Leaf
and edge = (string, t);
```

which makes a single path construction trivial, but makes merging searches more
convoluted.

Then I swapped to a `Hashtbl.t(int, list(string))`, where each position had an
associated string. While making it easier to look up chars, it did not make it
any easier to search.

Then I swapped to the an algebraic type like:

```reason
type t = 
  | Node(option(string), M.t(t));
```

Where `M.t('a)` is a map of string-keys to `'a`.

Not in love with it, and I haven't benchmarked, but beyond the bugs I haven't
dug for, it seems to work for the simple tests I've done with it.

### Running

```sh
ostera/retrie λ npm -g i esy
ostera/retrie λ esy dune exec ./retrie.exe
baaah wasnt found, yay!
ann works
annual works
annulment works
```
