/* global d3 hljs */
(function () {
  var SnippetView = function (el, trigger) {
    this.onStateChanged = function (newState, oldState) {
      if (newState.graph === oldState.graph &&
        newState.selection === oldState.selection) {
        return
      }
      this.update(newState.selection)
    }

    function appendLink (d, linkTo, text) {
      text = text || linkTo
      d.append('a')
        .attr('href', linkTo)
        .attr('target', '_blank')
        .text(text)
    }

    function serializeTokens (tokens) {
      var codeString = ''
      if (tokens) {
        for (var tokenName in tokens) {
          if (tokens.hasOwnProperty(tokenName)) {
            codeString += tokenName + ': ' + tokens[tokenName] + '\n'
          }
        }
      }
      return codeString
    }

    this.el = d3.select(el)
    this.title = this.el
      .append('h3')
        .attr('class', 'snippet-title col-sm-12')
    this.codeBlock = this.el
      .append('pre')
        .attr('class', 'code-snippet col-sm-12')
        .style('padding', '0px')
        .style('background', 'transparent')
      .append('code')

    this.tokens = this.el
      .append('div')
        .attr('class', 'snippet-tokens col-sm-12')
    this.tokensInner = this.tokens
      .append('div')
        .attr('class', 'row')
    this.tokensInner
      .append('h5')
        .attr('class', 'col-sm-12')
        .text('Token Counts')
    this.tokenCountBlock = this.tokensInner
      .append('pre')
        .attr('class', 'code-snippet col-sm-12')
        .style('padding', '0px')
        .style('background', 'transparent')
      .append('code')

    this.meta = this.el
      .append('div')
        .attr('class', 'snippet-meta col-sm-12')

    this.updateTokens = function (meta) {
      var tokenString = serializeTokens(meta.tokens)

      this.tokenCountBlock.text(tokenString)
      hljs.highlightBlock(this.tokenCountBlock.node())
    }

    this.updateDetails = function (meta) {
      meta = meta || {}
      this.meta.selectAll('*').remove()
      this.meta
          .append('h5')
          .text('Details')
      let intro = this.meta.append('p')
      if (meta.retrieved_from) {
        intro.append('span')
          .text('This snippet was initially found elsewhere on the web, and was' +
            ' retrieved for p2. ')
        appendLink(intro, meta.retrieved_from, 'Click here')
        intro.append('span')
          .text(' for the original.')
      } else {
        intro.text('This snippet was contributed to p2 by ' +
          meta.created_by || 'an anonymous contributor' +
          '.')
      }

      if (meta.references) {
        this.meta
          .append('h5')
          .text('References')

        let references = this.meta
          .append('ul')
        meta.references.forEach(function (link) {
          appendLink(references.append('li'), link)
        })
      }
    }.bind(this)

    this.update = function (selectionDetails) {
      if (!selectionDetails.snippet) {
        this.el.style('display', 'none')
        return
      }

      this.el.style('display', 'inherit')

      let snippetMeta = selectionDetails.snippet.meta
      let snippetCode = selectionDetails.snippet.data

      this.title.text(snippetMeta.name)

      this.codeBlock.text(snippetCode)
      hljs.highlightBlock(this.codeBlock.node())

      this.updateTokens(snippetMeta)

      this.updateDetails(snippetMeta)
    }.bind(this)
  }

  window.p2.SnippetView = SnippetView
}())
