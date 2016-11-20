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

    this.el = d3.select(el)
    this.meta = this.el
      .append('div')
        .attr('class', 'snippet-meta col-sm-12')
    this.title = this.meta
      .append('h3')
    this.codeBlock = this.el
      .append('pre')
        .attr('class', 'code-snippet col-sm-12')
        .style('padding', '0px')
        .style('background', 'transparent')
      .append('code')

    this.update = function (nodeDetails, selectionDetails) {
      nodeDetails = nodeDetails || {name: ''}
      let snippetTitle, snippetCode
      if (selectionDetails.snippet) {
        snippetTitle = selectionDetails.snippet.meta.name
        snippetCode = selectionDetails.snippet.data
      }
      this.title.text(snippetTitle)
      this.codeBlock.text(snippetCode)
      hljs.highlightBlock(this.codeBlock.node())
    }.bind(this)
  }

  window.p2.SnippetView = SnippetView
}())
