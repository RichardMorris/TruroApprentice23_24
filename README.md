From https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm


function Dijkstra(Graph, source):
      
      for each vertex v in Graph.Vertices:
          dist[v] ← INFINITY
          prev[v] ← UNDEFINED
          add v to Q
      dist[source] ← 0
      
      while Q is not empty:
          u ← vertex in Q with min dist[u]
          remove u from Q
          
          for each neighbor v of u still in Q:
              alt ← dist[u] + Graph.Edges(u, v)
              if alt < dist[v]:
                  dist[v] ← alt
                  prev[v] ← u

      return dist[], prev[]