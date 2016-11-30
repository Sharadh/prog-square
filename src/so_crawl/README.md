so_crawl: Module Overview
---
This document describes the module, and provides a breakdown of responsibility across the various files.

### so_crawl
The module is responsible for connecting to StackOverflow, pulling questions and answers, and constructing code snippets from these. It abstracts away the process of connecting to the remote server and extracting snippets from the retrieved data.

### `api_utils.py`
Builds the API url before making a request. The key is the `build_url` function which translate keyword arguments into `GET` parameters. (Thanks to [Py-StackExchange](https://github.com/lucjon/Py-StackExchange) for the idea.) This also specifies two types of constants:
* standard utility fields that custom filters are augmented with, and
* constants specified in the API documentation

Check the [StackExchange API](https://api.stackexchange.com/docs) documentation for more details.

### `crawl.py`
Interface to users of the module; `fetch_snippets` is the functional entry-point. Note that questions and answers use different filters: this is handled by `custom_filters.py`. This also exposes a `main` method that allows the module to be run stand-alone (primarily for testing.)

Note that `check_source_and_warn` and `get_snippets` could interact better: to maintain DRY, we ought not to concern ourselves with `etree` in `get_snippets`, and instead use the `order.source_handler` fucntionality.

### `custom_filters.py`
Creates filters to retrieve the relevant fields of questions and answers in the API calls. This populates the generated file `_generated_filters.json` with the id of created filters. `ensure_updated_filters` also makes sure that any change in this file is followed by updating the filter ids.

### `snippet.py`
Defines the `Snippet` model: this is part of the interface and is passed back by the `fetch_snippets` function call.
