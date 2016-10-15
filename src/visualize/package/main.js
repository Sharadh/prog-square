/**
 * References
 * http://alignedleft.com/tutorials/d3/binding-data
 * http://jsdatav.is/visuals.html?id=83515b77c2764837aac2
 * http://bl.ocks.org/mbostock/1153292
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
(function(){
  var graph = {
    "nodes": [
      {
        "id": 0, 
        "name": "00_hello_world"
      }, 
      {
        "id": 1, 
        "name": "01_hello_function"
      }, 
      {
        "id": 2, 
        "name": "02_hello_param_if"
      }, 
      {
        "id": 3, 
        "name": "03_hello_param"
      }, 
      {
        "id": 4, 
        "name": "04_hello_world_again"
      }, 
      {
        "id": 5, 
        "name": "05_hello_world_twice"
      }
    ], 
    "links": [
      {
        "source": 0, 
        "target": 1
      }, 
      {
        "source": 0, 
        "target": 2
      }, 
      {
        "source": 0, 
        "target": 3
      }, 
      {
        "source": 0, 
        "target": 4
      }, 
      {
        "source": 0, 
        "target": 5
      }
    ]
  }
  var width = 640,
    height = 480;

  var svg = d3.select('body').append('svg')
    .attr('width', width)
    .attr('height', height);

  var nodeRadius = width/25;
  
  var force = null,
    nodes = null,
    links = null,
    names = null;

  function init() {
    svg.selectAll('*').remove();

    svg.append('defs').append('marker')
      .attr('id', 'program')
      .attr('viewBox', '0 0 10 10')
      .attr('refX', '10')
      .attr('refY', '5')
      .attr('orient', 'auto')
      .attr('markerWidth', '5')
      .attr('markerHeight', '5')
      .append('path')
        .attr('d', 'M0,0L10,5L0,10');

    force = d3.layout.force()
      .size([width, height])
      .nodes(graph.nodes)
      .links(graph.links)
      .linkDistance(150)
      .charge(-100);

    nodes = svg
      .append('g')
      .attr('id', 'g-nodes')
        .selectAll('.node')
        .data(graph.nodes)
        .enter().append('circle')
          .attr('class', 'node')
          .attr('r', function(d) {
            d.radius = nodeRadius;
            return d.radius;
          })
          .on('mouseover', handleNodeMouseOver)
          .on('mouseout', handleNodeMouseOut);

    links = svg
      .append('g')
      .attr('id', 'g-links')
        .selectAll('.link')
        .data(graph.links)
        .enter().append('path')
          .attr('class', 'link')
          .attr('marker-end', 'url(#program)');

    names = svg
      .append('g')
      .attr('id', 'g-node-labels')
        .selectAll('text')
        .data(graph.nodes)
        .enter().append("text")
          .attr('x', 8)
          .attr('y', ".31em")
          .attr('id', function(d) { return 'label-' + d.id })
          .attr('display', 'none')
          .text(function(d) { return d.name; });
    
    force.on('tick', step);
  }

  function handleNodeMouseOver(d) {
    d3.select(this).attr('class', 'node active');
    d3.select('#label-' + d.id).attr('display', 'inherit');
  }

  function handleNodeMouseOut(d) {
    d3.select(this).attr('class', 'node');
    d3.select('#label-' + d.id).attr('display', 'none');
  }

  function linkLine(d) {
    var dx = d.target.x - d.source.x,
      dy = d.target.y - d.source.y;

    var dMag = Math.sqrt(dx * dx + dy * dy);

    // Vector addition: dx/dMag and dy/dMag are unit vectors
    var offsetX = d.target.radius * dx / dMag;
    var offsetY = d.target.radius * dy / dMag;
    
    // Apply appropriate direction offset 
    // so link starts/ends beyond node circle...
    var targetX = d.target.x - offsetX;
    var targetY = d.target.y - offsetY;

    var sourceX = d.source.x + offsetX;
    var sourceY = d.source.y + offsetY;
    
    return "M" + sourceX + "," + sourceY +
      "L" + targetX + "," + targetY;
  }

  function transform(d) {
    return "translate(" + d.x + "," + d.y + ")";
  }

  function step() {
    nodes.attr('transform', transform);
    names.attr('transform', transform);
    links.attr('d', linkLine);
  }

  init();
  force.start();

}())