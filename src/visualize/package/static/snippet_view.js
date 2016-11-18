/* global d3 hljs */
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

    var codeBlock = d3.select(el)
      .append('pre')
        .style('padding', '0px')
        .style('background', 'transparent')
      .append('code')
        .style('height', '100%')
    this.update = function (nodeDetails, selectionDetails) {
      nodeDetails = nodeDetails || {name: ''}
      codeBlock.text(selectionDetails.snippet)
      hljs.highlightBlock(codeBlock.node())
    }
  }

  window.p2.SnippetView = SnippetView
}())
