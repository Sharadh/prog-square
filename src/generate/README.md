generate: Module Overview
---
This module is responsible of creating folders that can be consumed by the `order` module. In other words, this is an _adapter_.

### `p2_convert.py`
This takes a source directory of valid python scripts (`*.py` files) and converts them to `*.p2` files. This auto-generates some metadata for these files, and also accepts some values for other fields.

### `p2_so_crawl.py`
This takes [`Snippet`](../so_crawl/snippet.py) objects and saves them as `*.p2` files. The metadata is pulled from the relevant fields in the model.
