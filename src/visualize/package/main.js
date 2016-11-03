/**
 * References
 * ====
 * Intro and Ramp Up
 * http://alignedleft.com/tutorials/d3/binding-data
 * http://jsdatav.is/visuals.html?id=83515b77c2764837aac2
 * http://bl.ocks.org/mbostock/1153292
 *
 * D3 Force Layout API Ref
 * https://github.com/d3/d3-3.x-api-reference/blob/master/Force-Layout.md
 *
 * SVG Mouseevents
 * http://bl.ocks.org/WilliamQLiu/76ae20060e19bf42d774
 *
 * Level-ed Layout
 * http://bl.ocks.org/rmarimon/1079724
 *
 * Future:
 * http://stackoverflow.com/questions/23986466/d3-force-layout-linking-nodes-by-name-instead-of-index
 */

/* global d3 */

(function () {
  var width = 640
  var height = 480

  var svg = d3.select('body').append('svg')
    .attr('width', width)
    .attr('height', height)

  var nodeRadius = 10
  var linkNodeRadius = 2
  var nodeCharge = -150
  var verticalSpace = 150
  var linkStrengthArray = [0.5, 0.2, 0.05]

  var force = null
  var nodes = null
  var linkNodes = null
  var links = null
  var levels = null
  var names = null
  var maxDepth = 0

  var showLevels = false
  var showLinkNodes = false

  function init (graph) {
    svg.selectAll('*').remove()

    svg.append('defs').append('marker')
      .attr('id', 'program')
      .attr('viewBox', '0 0 11 11')
      .attr('refX', '10')
      .attr('refY', '6')
      .attr('orient', 'auto')
      .attr('markerWidth', '5')
      .attr('markerHeight', '5')
      .append('path')
        .attr('d', 'M0,0L11,6L0,11')

    /**
     * To prevent Node-Edge overlap, we insert these
     * linkNodes that essentially provide charge to edges.
     * The charges are distributed evenly along the length
     * of the edge (both the edge length and linkNode position
     * are functions of the depth difference)
     * e.g:
     * [1 -> 5] => [1 -> 2 -> 3 -> 4 -> 5]
     * [1 -> 2] => [1 -> 2]
     */
    graph.linkNodes = []
    graph.links.forEach(function (d) {
      var sourceNode = graph.nodes[d.source]
      var targetNode = graph.nodes[d.target]
      var depthDiff = targetNode.depth - sourceNode.depth
      // LinkNodes include neither starting nor ending depth
      for (var i = 1; i < depthDiff; ++i) {
        graph.linkNodes.push({
          isLinkNode: true,
          markerPosition: i * 1.0 / depthDiff,
          source: sourceNode,
          target: targetNode
        })
      }
    })

    force = d3.layout.force()
      .size([width, height])
      .nodes(graph.nodes.concat(graph.linkNodes))
      .links(graph.links)
      .linkDistance(function (d) {
        var depthDiff = d.target.depth - d.source.depth
        return depthDiff * verticalSpace
      })
      .linkStrength(function (d) {
        /* Beyond 3 levels, the link strength parameter
        is completely ineffective. This means the layout
        has complete control over the exact link distance */
        var depthDiff = d.target.depth - d.source.depth
        return (
          (depthDiff < linkStrengthArray.length)
          ? linkStrengthArray[depthDiff] : 0
        )
      })
      .charge(nodeCharge)

    // Traverese the node data...
    maxDepth = graph.nodes.reduce(function (maxSoFar, d) {
      d.depth = d.depth || 1
      return (maxSoFar > d.depth) ? maxSoFar : d.depth
    }, 0)

    var depthData = []
    for (var i = 1; i <= maxDepth; ++i) {
      var datum = graph.nodes.filter(function (d) {
        return d.depth === i
      })
      depthData.push({
        depth: i,
        nodes: datum
      })
    }

    levels = svg
      .append('g')
      .attr('display', showLevels ? 'inherit' : 'none')
      .attr('id', 'g-levels')
        .selectAll('.level-connector')
        .data(depthData)
        .enter().append('path')
          .attr('class', 'level-connector')
          .attr('id', function (d) {
            return 'level-' + d.depth
          })

    links = svg
      .append('g')
      .attr('id', 'g-links')
        .selectAll('.link')
        .data(graph.links)
        .enter().append('path')
          .attr('class', 'link')
          .attr('marker-end', 'url(#program)')

    linkNodes = svg
      .append('g')
      .attr('display', showLinkNodes ? 'inherit' : 'none')
      .attr('id', 'g-link-nodes')
        .selectAll('.link-node')
        .data(graph.linkNodes)
        .enter().append('circle')
          .attr('class', 'link-node')
          .attr('r', linkNodeRadius)

    nodes = svg
      .append('g')
      .attr('id', 'g-nodes')
        .selectAll('.node')
        .data(graph.nodes)
        .enter().append('circle')
          .attr('class', 'node')
          .attr('r', function (d) {
            d.radius = nodeRadius
            return d.radius
          })
          .on('mouseover', handleNodeMouseOver)
          .on('mouseout', handleNodeMouseOut)

    names = svg
      .append('g')
      .attr('id', 'g-node-labels')
        .selectAll('text')
        .data(graph.nodes)
        .enter().append('text')
          .attr('x', 8)
          .attr('y', '.31em')
          .attr('id', function (d) { return 'label-' + d.id })
          .attr('display', 'none')
          .text(function (d) { return d.name })

    force.on('tick', step)
  }

  function handleNodeMouseOver (d) {
    d3.select(this).attr('class', 'node active')
    d3.select('#label-' + d.id).attr('display', 'inherit')
  }

  function handleNodeMouseOut (d) {
    d3.select(this).attr('class', 'node')
    d3.select('#label-' + d.id).attr('display', 'none')
  }

  function linkLine (d) {
    var dx = d.target.x - d.source.x
    var dy = d.target.y - d.source.y

    var dMag = Math.sqrt(dx * dx + dy * dy)

    // Vector addition: dx/dMag and dy/dMag are unit vectors
    var offsetX = d.target.radius * dx / dMag
    var offsetY = d.target.radius * dy / dMag

    // Apply appropriate direction offset
    // so link starts/ends beyond node circle...
    var targetX = d.target.x - offsetX
    var targetY = d.target.y - offsetY

    var sourceX = d.source.x + offsetX
    var sourceY = d.source.y + offsetY

    return 'M' + sourceX + ',' + sourceY +
      'L' + targetX + ',' + targetY
  }

  function levelLine (d) {
    var leadingOffset = 50
    var sortedCoords = d.nodes.map(function (node) {
      return {x: node.x, y: node.y}
    }).sort(function (first, second) {
      return first.x - second.x
    })

    if (!sortedCoords.length) {
      return ''
    }

    var pathSpec = []
    var eachPt = sortedCoords.shift()
    pathSpec.push('M' + 0 + ',' + height / 2.0)
    pathSpec.push('L' + (eachPt.x - leadingOffset) + ',' + eachPt.y)
    while (sortedCoords.length) {
      eachPt = sortedCoords.shift()
      pathSpec.push('L' + (eachPt.x - leadingOffset) + ',' + eachPt.y)
    }
    pathSpec.push('L' + (eachPt.x + leadingOffset) + ',' + eachPt.y)
    pathSpec.push('L' + width + ',' + height / 2.0)

    var pathSpecStr = pathSpec.join(' ')
    return pathSpecStr
  }

  function transform (d) {
    return 'translate(' + d.x + ',' + d.y + ')'
  }

  function transformLinkNode (d) {
    // x + (y - x) * p
    var delta = {
      x: d.target.x - d.source.x,
      y: d.target.y - d.source.y
    }
    var dx = d.source.x + delta.x * d.markerPosition
    var dy = d.source.y + delta.y * d.markerPosition
    return 'translate(' + dx + ',' + dy + ')'
  }

  function step (d) {
    // Apply leveling
    var k = 0.5 * d.alpha
    nodes.each(function (d) {
      d.y += ((d.depth || maxDepth) * 100 - d.y) * k
    })

    nodes.attr('transform', transform)
    names.attr('transform', transform)
    links.attr('d', linkLine)
    linkNodes.attr('transform', transformLinkNode)
    levels.attr('d', levelLine)
  }

  d3.json('graph.json', function (err, json) {
    if (err) {
      console.error(err)
      return
    }
    init(json)
    force.start()
  })
}())
