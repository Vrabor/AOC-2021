use std::io::prelude::*;
use std::io::BufReader;
use std::fs::File;


type Board = [[i32; 5]; 5];

fn get_boards(input: String) -> Vec<Board>{
    let mut boards = Vec::new();
    let lines = input.lines().filter(|x| !x.is_empty());

    let mut pos = 0;
    let mut st = String::new();
    let mut array: [[i32; 5]; 5] = [[0; 5]; 5]; 
    for s in lines{
        st = s.to_string();
        let b_line = st.split(" ").filter(|x| !x.is_empty()).map(|x| x.parse::<i32>().unwrap());
        for (j, u) in b_line.enumerate(){
            array[pos][j] = u;
        }
        
        if pos == 4{
            boards.push(array);
            pos = 0;
        } else {
            pos += 1;
        }
        
    }
    
    boards
}

fn bingo(board: &Board, draws: &[i32]) -> bool {
    // rows
    for i in 0..5{
        let mut b = true;
        for j in 0..5{
            if !draws.contains(&board[j][i]){
                b = false;
            }
        }
        if b {
            return true;
        }
    }
    // columns
    for i in 0..5{
        let mut b = true;
        for j in 0..5{
            if !draws.contains(&board[i][j]){
                b = false;
            }
        }
        if b {
            return true;
        }
    }
    false
}

fn check_bingo(boards: &Vec<Board>, draws: &[i32]) -> Option<Board>{
    for board in boards{
        if bingo(board, draws){
            return Some(*board);
        }
    }
    return None;
}

fn compute_board(board: &Board, draws: &[i32]) -> i32 {
    let mut sum = 0;
    for i in board{
        for j in i{
            if !draws.contains(&j){
                sum += j
            }
        }
    }
    sum * draws[draws.len() - 1]
}

fn task1(boards: &Vec<Board>, draws: &Vec<i32>){
    let mut num_draws = 0;
    loop {
        if let Some(bingo) = check_bingo(&boards, &draws[0..num_draws]){
            println!("Task1: {}", compute_board(&bingo, &draws[0..num_draws]));
            //println!("Board: {:?}", bingo);
            //println!("draw number: {}, number drawn: {}", num_draws, draws[num_draws]);
            return;
        } else {
            num_draws += 1;
        }
    }
}

fn task2(boards: &Vec<Board>, draws: &Vec<i32>){
    let mut first_bingo = Vec::<i32>::with_capacity(boards.len());
    for _ in boards{
        // fill Vector with 0s
        first_bingo.push(-1);
    }

    let mut num_draws = 0;
    while first_bingo.contains(&-1){
        for (i, board) in boards.iter().enumerate(){
            if bingo(board, &draws[0..num_draws]){
                if first_bingo[i] == -1{
                    first_bingo[i] = num_draws as i32;
                }
            }
        }
        num_draws += 1;
    }

    let losing_board = boards.iter().max_by_key(
            |x| first_bingo[boards.iter().position(|y| &y == x).unwrap()]);
    let score = compute_board(losing_board.unwrap(), &draws[0..num_draws - 1]);
    println!("Task1: {}", score);
}

fn main() -> std::io::Result<()>{
    let f = File::open("input.txt")?;
    let mut reader = BufReader::new(f);

    let mut line = String::new();
    reader.read_line(&mut line)?;

    let draws: Vec<i32> = line.split(",").into_iter()
                                         .map(|x| x.trim().parse::<i32>().unwrap())
                                         .collect();
    
    let mut rest = String::new();
    reader.read_to_string(&mut rest)?;
    let boards: Vec<Board> = get_boards(rest);

    task1(&boards, &draws);
    task2(&boards, &draws);

    Ok(())
}
