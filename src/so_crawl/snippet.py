class Snippet(object):
    def __init__(self, snippet_id, code, url, author, retrieved_at, additional_url):
        self.snippet_id = snippet_id
        self.code = code
        self.url = url
        self.author = author
        self.retrieved_at = retrieved_at
        self.extra_url = additional_url
