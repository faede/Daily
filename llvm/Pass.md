# Pass



### SCC

According to [The LLVM Lexicon](http://llvm.org/docs/Lexicon.html#SCC), It stands for "[strongly connected component](http://en.wikipedia.org/wiki/Strongly_connected_component)".

The source-code comments explain it this way:

> Because there may be cycles in the call graph, passes of this type operate on the call-graph in SCC order: that is, they process function bottom-up, except for recursive functions, which they process all at once.

(But the only reason I was able to find the lexicon is that I figured out that they must mean "strongly connected component", and then I Googled for that phrase on `site:llvm.org` to confirm. It doesn't seem to be prominently linked.)



[Share](https://stackoverflow.com/a/8546377)

[Improve this answer](https://stackoverflow.com/posts/8546377/edit)
