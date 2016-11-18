/* global d3 */
(function () {
  let Controller = function () {
    this.state = {
      graph: {},
      selection: []
    }

    this.initialize = function (graphEl, snippetEl) {
      this.graph = new this.GraphView(graphEl, this.onMessage)
      this.snippet = new this.SnippetView(snippetEl)

      // Todo: move from d3 to something more neutral for state-loading?
      d3.json('graph/default', this.onLoad)
    }

    this.onLoad = function (err, json) {
      if (err) {
        console.error(err)
        return
      }
      this.setState({
        graph: json,
        selection: []
      })
    }.bind(this)

    this.onMessage = function (message, data) {
      var parts = message.split(':')
      var entity = parts[0]
      var command = parts[1]

      if (entity === 'graph') {
        let newSelection
        if (command === 'select') {
          newSelection = [data.node_id]
        } else if (command === 'deselect') {
          newSelection = []
        }
        this.setState({
          graph: this.state.graph,
          selection: newSelection
        })
      } else if (entity === 'snippet') {
        console.log('snippet says ' + command)
      }
    }.bind(this)

    this.setState = function (newState) {
      var oldState = this.state
      this.state = newState
      this.graph.onStateChanged(this.state, oldState)
      this.snippet.onStateChanged(this.state, oldState)
    }
  }

  window.p2 = new Controller()
}())
