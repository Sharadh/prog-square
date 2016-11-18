(function () {
  let Controller = function () {
    this.initialize = function (graphEl, snippetEl) {
      this.graph = new this.GraphView(graphEl, this.onMessage)
      // this.snippetEl = new this.SnippetView(snippetEl)
    }

    this.onMessage = function (message, data) {
      var parts = message.split(':')
      var entity = parts[0]
      var command = parts[1]

      if (entity === 'graph') {
        console.log('Graph says ' + command)
      } else if (entity === 'snippet') {
        console.log('snippet says ' + command)
      }
    }
  }

  window.p2 = new Controller()
}())
