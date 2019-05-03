module Infix = {
  let (<|>) = (a, b) =>
    switch (a) {
    | None => b
    | Some(c) => c
    };
};

module M =
  Map.Make({
    type t = string;
    let compare = String.compare;
  });

type t =
  | Node(option(string), M.t(t));

/* The empty Trie */
let empty = Node(None, M.empty);

let add: (string, t) => t =
  (str, root) => {
    let rec add' = (chars, tree) => {
      switch (tree, chars) {
      | (r, []) => r
      | (Node(v, m), [c, ...cs]) =>
        let t = Infix.(m |> M.find_opt(c) <|> empty |> add'(cs));
        Node(v, m |> M.add(c, t));
      };
    };

    let chars =
      str |> String.to_seq |> List.of_seq |> List.map(String.make(1));
    add'(chars, root);
  };

let check: (string, t) => bool =
  (key, root) => {
    let rec find' = (chars, tree) => {
      switch (chars, tree) {
      | ([], _) => true
      | ([c, ...cs], Node(_, m)) =>
        switch (M.find_opt(c, m)) {
        | None => false
        | Some(n') => find'(cs, n')
        }
      };
    };

    let chars =
      key |> String.to_seq |> List.of_seq |> List.map(String.make(1));
    find'(chars, root);
  };

let trie =
  ["announce", "annual", "annulment", "antiques"]
  |> List.fold_left((trie, el) => add(el, trie), empty);

print_string( trie |> check ("baaaah") ? "baaah should not be there" : "baaah wasnt found, yay!");
print_newline();
print_string( trie |> check ("ann") ? "ann works" : "ann broke");
print_newline();
print_string( trie |> check ("annual") ? "annual works" : "annual broke");
print_newline();
print_string( trie |> check ("annulment") ? "annulment works" : "annulment broke");
print_newline();
