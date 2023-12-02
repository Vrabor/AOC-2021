export class Node {
    name : string;
    neighbors : Array<Node>;
    constructor(name : string, neighbors : Array<Node>){
        this.name = name;
        this.neighbors = neighbors;
    }
}

export class UniNode {
    name : string;
    neighbors : Set<string>;
    constructor(name : string, neighbors : Set<string>){
        this.name = name;
        this.neighbors = neighbors;
    }
}

export class DirectedTaggedGraph {
    nodes : Map<string, Node>;
    tags : Set<string>;
    constructor(){
        this.nodes = new Map<string, Node>();
        this.tags = new Set<string>();
    }

    addNode(node : Node, tagged : boolean) {
        this.nodes.set(node.name, node);
        if (tagged) {
            this.tags.add(node.name);
        }
    }

    addEdge(from : string, to : string){
        const fromNode = this.get(from);
        if (fromNode === undefined){
            return;
        }
        
        const toNode = this.get(to);
        if (toNode === undefined){
            return;
        }

        fromNode.neighbors.push(toNode);
    }

    get(name : string) : Node | undefined {
        return this.nodes.get(name);
    }

    has(name: string) : boolean {
        return this.nodes.has(name);
    }

    isTagged(name : string) : boolean {
        return this.tags.has(name);
    }
}

export class UndirectedTaggedGraph {
    nodes : Map<string, UniNode>;
    tags : Set<string>;
    constructor(){
        this.nodes = new Map<string, UniNode>();
        this.tags = new Set<string>();
    }

    addNode(node : UniNode, tagged : boolean) {
        this.nodes.set(node.name, node);
        if (tagged) {
            this.tags.add(node.name);
        }
    }

    addEdge(name1 : string, name2 : string){
        const node1 = this.get(name1);
        if (node1 === undefined){
            return;
        }
        
        const node2 = this.get(name2);
        if (node2 === undefined){
            return;
        }

        node1.neighbors.add(node2.name);
        node2.neighbors.add(node1.name);
    }

    get(name : string) : UniNode | undefined {
        return this.nodes.get(name);
    }

    has(name: string) : boolean {
        return this.nodes.has(name);
    }

    isTagged(name : string) : boolean {
        return this.tags.has(name);
    }
}
