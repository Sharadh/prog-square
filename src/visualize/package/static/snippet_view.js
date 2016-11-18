/* global d3 */
(function () {
  var SnippetView = function (el, trigger) {
    this.onStateChanged = function (newState, oldState) {
      if (newState.graph === oldState.graph &&
        newState.selection === oldState.selection) {
        return
      }
      var nodeDetails = newState.graph.nodes.filter(function (node) {
        return node.id === newState.selection.id
      })
      this.update(nodeDetails[0], newState.selection)
    }

    var codeBox = d3.select(el).append('pre')
    this.update = function (nodeDetails, selectionDetails) {
      nodeDetails = nodeDetails || {name: ''}
      codeBox.text(selectionDetails.snippet)
    }
  }

  window.p2.SnippetView = SnippetView
}())
