/* global d3 */
(function () {
  var SnippetView = function (el, trigger) {
    this.onStateChanged = function (newState, oldState) {
      if (newState.graph === oldState.graph &&
        newState.selection === oldState.selection) {
        return
      }
      var nodeDetails = newState.graph.nodes.filter(function (node) {
        return node.id === newState.selection[0]
      })
      this.update(nodeDetails[0])
    }

    var code = d3.select(el).append('code')
    this.update = function (nodeDetails) {
      nodeDetails = nodeDetails || {name: ''}
      code.text(nodeDetails.name)
    }
  }

  window.p2.SnippetView = SnippetView
}())
