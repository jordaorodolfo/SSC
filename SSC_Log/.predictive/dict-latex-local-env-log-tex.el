(eval-when-compile (require 'cl))
(require 'dict-tree)
(defvar dict-latex-local-env-log-tex nil "Dictionary dict-latex-local-env-log-tex.")
(setq dict-latex-local-env-log-tex '[cl-struct-dictree- "dict-latex-local-env-log-tex" "/home/rjordao/Dropbox/SSC_Placement/Log_Report/.predictive/dict-latex-local-env-log-tex" t nil < + (closure ((insfun . +) . #1=(t)) (new old) (dictree--cell-set-data old (funcall insfun (dictree--cell-data new) (dictree--cell-data old))) old) predictive-dict-rank-function (closure ((rankfun . predictive-dict-rank-function) . #1#) (a b) (funcall rankfun (cons (car a) (dictree--cell-data (cdr a))) (cons (car b) (dictree--cell-data (cdr b))))) time synchronize nil nil nil nil #s(hash-table size 65 test equal rehash-size 1.5 rehash-threshold 0.8 data ()) 0.1 nil nil #s(hash-table size 65 test equal rehash-size 1.5 rehash-threshold 0.8 data ()) 0.1 nil nil nil nil predictive-auto-dict-plist-savefun nil [cl-struct-trie- [nil [cl-struct-avl-tree- [[[nil nil [100 [cl-struct-avl-tree- [[nil nil [101 [cl-struct-avl-tree- [[nil nil [102 [cl-struct-avl-tree- [[nil nil [110 [cl-struct-avl-tree- [[nil nil [--trie--terminator (0 :definitions (#2="/home/rjordao/Dropbox/SSC_Placement/Log_Report/log.tex"))] 0] nil nil 0] nil]] 0] nil nil 0] nil]] 0] nil nil 0] nil]] 0] nil nil 0] nil]] 0] [nil [nil nil [116 [cl-struct-avl-tree- [[nil nil [104 [cl-struct-avl-tree- [[nil nil [109 [cl-struct-avl-tree- [[nil nil [--trie--terminator (0 :definitions (#2#))] 0] nil nil 0] nil]] 0] nil nil 0] nil]] 0] nil nil 0] nil]] 0] [112 [cl-struct-avl-tree- [[nil nil [114 [cl-struct-avl-tree- [[nil nil [111 [cl-struct-avl-tree- [[nil [nil nil [112 [cl-struct-avl-tree- [[nil nil [--trie--terminator (0 :definitions (#2#))] 0] nil nil 0] nil]] 0] [111 [cl-struct-avl-tree- [[nil nil [102 [cl-struct-avl-tree- [[nil nil [--trie--terminator (0 :definitions (#2#))] 0] nil nil 0] nil]] 0] nil nil 0] nil]] 1] nil nil 0] nil]] 0] nil nil 0] nil]] 0] nil nil 0] nil]] 1] [102 [cl-struct-avl-tree- [[nil nil [97 [cl-struct-avl-tree- [[nil nil [99 [cl-struct-avl-tree- [[nil nil [116 [cl-struct-avl-tree- [[nil nil [--trie--terminator (0 :definitions (#2#))] 0] nil nil 0] nil]] 0] nil nil 0] nil]] 0] nil nil 0] nil]] 0] nil nil 0] nil]] 1] nil nil 0] #3=#[514 "\302!\262\302!\262	=\203 \211	=?\205% \303\207\211	=\203! \304\207\300\"\207" [< trie--terminator trie--node-split t nil] 5 "

(fn A B)"]]] < #3# #[514 "\300\301\300\302\211\211\303$#\207" [vector cl-struct-avl-tree- nil 0] 10 "

(fn CMPFUN SEQ)"] avl-tree-enter avl-tree-delete avl-tree-member avl-tree-mapc avl-tree-empty avl-tree-stack avl-tree-stack-pop avl-tree-stack-empty-p trie--avl-transform-for-print trie--avl-transform-from-read t] nil])
(trie-transform-from-read (dictree--trie dict-latex-local-env-log-tex))
 (trie-map
  (lambda (key cell)
     (dictree--cell-create
   (dictree--cell-data cell)
   (dictree--cell-plist cell)))
 (dictree--trie dict-latex-local-env-log-tex))
(unless (memq dict-latex-local-env-log-tex dictree-loaded-list)
  (push dict-latex-local-env-log-tex dictree-loaded-list))
