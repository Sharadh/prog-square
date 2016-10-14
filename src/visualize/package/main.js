/**
 * Reference
 * http://jsdatav.is/visuals.html?id=83515b77c2764837aac2
 * http://bl.ocks.org/mbostock/1153292
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
      }, 
      {
        "source": 1, 
        "target": 2
      }, 
      {
        "source": 1, 
        "target": 3
      }, 
      {
        "source": 3, 
        "target": 2
      }, 
      {
        "source": 4, 
        "target": 0
      }, 
      {
        "source": 4, 
        "target": 1
      }, 
      {
        "source": 4, 
        "target": 2
      }, 
      {
        "source": 4, 
        "target": 3
      }, 
      {
        "source": 4, 
        "target": 5
      }, 
      {
        "source": 5, 
        "target": 2
      }
    ]
  }
  var width = 640,
    height = 480;

  var svg = d3.select('body').append('svg')
    .attr('width', width)
    .attr('height', height);

  var animationStep = 400;
  
  var force = null,
    nodes = null,
    links = null,
    names = null;

  function initForce() {
    svg.selectAll('*').remove();

    force = d3.layout.force()
      .size([width, height])
      .nodes(graph.nodes)
      .links(graph.links)
      .linkDistance(150)
      .charge(-100);

    nodes = svg.append('g').selectAll('.node')
      .data(graph.nodes)
      .enter().append('circle')
      .attr('class', 'node')
      .attr('r', width/25);
    
    links = svg.append('g').selectAll('.link')
      .data(graph.links)
      .enter().append('line')
      .attr('class', 'link');

    names = svg.append('g').selectAll("text")
      .data(graph.nodes)
      .enter().append("text")
      .attr("x", 8)
      .attr("y", ".31em")
      .text(function(d) {
        return d.name;
      });

    force.on('tick', stepForce);
  }

  function stepForce() {
    var updatedNodes,
      updatedLinks;

    if (force.fullSpeed) {
      updatedNodes = nodes;
      updatedLinks = links;
      updatedNames = names;
    } else {
      updatedNodes = nodes.transition()
        .ease('linear')
        .duration(animationStep);
      updatedLinks = links.transition()
        .ease('linear')
        .duration(animationStep);
      updatedNames = names.transition()
        .ease('linear')
        .duration(animationStep);
    }

    updatedNodes
      .attr('cx', function(d) { return d.x; })
      .attr('cy', function(d) { return d.y; });

    updatedNames
      .attr('x', function(d) { return d.x; })
      .attr('y', function(d) { return d.y; });

    updatedLinks
      .attr('x1', function(d) { return d.source.x; })
      .attr('y1', function(d) { return d.source.y; })
      .attr('x2', function(d) { return d.target.x; })
      .attr('y2', function(d) { return d.target.y; });

    if (!force.fullSpeed) {
      force.stop();

      if (force.slowMotion) {
        setTimeout(
          function () { force.start(); },
          animationStep
        );
      }
    }
  }

  initForce();
  force.fullSpeed = true;
  force.start();

}())