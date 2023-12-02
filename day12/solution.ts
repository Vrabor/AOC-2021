import {UndirectedTaggedGraph, UniNode} from "./graph.ts";

const data : string = await Deno.readTextFile("input.txt");
const re = /^(\w+)-(\w+)$/g;
const uppercase = /^[A-Z]+$/;
const lines : string[] = data.split('\n');

const graph : UndirectedTaggedGraph = new UndirectedTaggedGraph();

for (const line of lines){
    for (const match of line.matchAll(re)){
        const beginName = match[1];
        const endName = match[2];

        console.log('begin: ' + beginName + ', ' + 'end: ' + endName);

        if (!graph.has(beginName)){
            const tagged = !uppercase.test(beginName);
            graph.addNode(new UniNode(beginName, new Set()), tagged);
        }
        
        if (!graph.has(endName)){
            const tagged = !uppercase.test(endName);
            graph.addNode(new UniNode(endName, new Set()), tagged);
        }

        graph.addEdge(beginName, endName);
    }
}

console.log(graph);

function count_paths(start : string, end : string, tagged_nodes_visited : Set<string>) : number{
    if (tagged_nodes_visited.has(start)){
        return 0;
    }

    if (start === end){
        return 1;
    }

    if (graph.isTagged(start)){
        tagged_nodes_visited.add(start);
    }

    const startNode = graph.get(start);
    if (startNode === undefined) {
        console.warn('undefined node found');
        return 0;
    }

    let paths = 0;
    for(const next of startNode.neighbors) {
       paths += count_paths(next, end, tagged_nodes_visited);  
    }
    
    if (graph.isTagged(start)){
        tagged_nodes_visited.delete(start);
    }

    return paths;

}

function count_paths_modified(start : string, end : string, tagged_nodes_visited : Map<string, number>) : number{
    if (start === end){
        return 1;
    }

    if (graph.isTagged(start)){
        var visited = tagged_nodes_visited.get(start);
        if (visited === undefined){
            visited = 0;
            tagged_nodes_visited.set(start, visited);
        }
        visited += 1;

        if (start === "start" && visited === 2){
            return 0;
        }

        if (visited > 2){
            return 0;
        } else if(visited > 1) {
            let other_twice = Array.from(tagged_nodes_visited.values()).findIndex((x) => x >= 2);
            if (other_twice !== -1){
                return 0;
            }
        }

        tagged_nodes_visited.set(start, visited);
    }

    const startNode = graph.get(start);
    if (startNode === undefined) {
        console.warn('undefined node found');
        return 0;
    }

    let paths = 0;
    for(const next of startNode.neighbors) {
       paths += count_paths_modified(next, end, tagged_nodes_visited);
    }
    
    if (visited !== undefined){
        tagged_nodes_visited.set(start, visited - 1);
    }    

    return paths;

}

console.log('Solution1: ' + count_paths('start', 'end', new Set()));
console.log('Solution2: ' + count_paths_modified('start', 'end', new Map()));
