// Learn more about F# at http://docs.microsoft.com/dotnet/fsharp

open System

type Op =
    | Up of int
    | Down of int
    | Forward of int

let parse (line: String): Option<Op> =
    let split = line.Split " "
    match split with
    | [|"up"; x|] -> Some(Op.Up(int x))
    | [|"down"; x|] -> Some(Op.Down(int x))
    | [|"forward"; x|] -> Some(Op.Forward(int x))
    | _ -> None


let processTask1 (ops: seq<Option<Op>>) =
    let mutable depth = 0
    let mutable position = 0
    for op in ops do
        match op with
        | Some(Up(x)) -> depth <- depth - x
        | Some(Down(x)) -> depth <- depth + x
        | Some(Forward(x)) -> position <- position + x
        | None -> ()

    (depth, position)

let processTask2 (ops: seq<Option<Op>>) =
    let mutable depth = 0
    let mutable position = 0
    let mutable aim = 0
    for op in ops do
        match op with
        | Some(Up(x)) -> aim <- aim - x
        | Some(Down(x)) -> aim <- aim + x
        | Some(Forward(x)) -> position <- position + x
                              depth <- depth + x * aim
        | None -> ()

    (depth, position)



[<EntryPoint>]
let main argv =
    if argv.Length < 1 then
        printf "Not enough Arguments, please supply path to inputfile\n"
        
    let task1 = System.IO.File.ReadLines argv.[0]
                |> Seq.map parse
                |> processTask1

    printfn "Task1 answer: %d" ((fst task1) * (snd task1))

    let task2 = System.IO.File.ReadLines argv.[0]
                |> Seq.map parse
                |> processTask2
    printfn "Task2 answer: %d" ((fst task2) * (snd task2))

    0 // return an integer exit code