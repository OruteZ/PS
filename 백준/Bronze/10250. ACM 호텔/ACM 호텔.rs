use std::io;

fn main() {
    let mut t_case = String::new();
    io::stdin()
        .read_line(&mut t_case)
        .expect("Failed to read line");

    let t_case: i32 = t_case.trim().parse().expect("Please type a number!");
    for _ in 0..t_case {
        solve();
    }
}

fn solve() {
    let mut input = String::new();

    io::stdin()
        .read_line(&mut input)
        .expect("fail");

    let mut input = input.trim().split_whitespace();
    
    let height : i32 = input.next().unwrap().parse().unwrap();
    let _width : i32 = input.next().unwrap().parse().unwrap();
    let n : i32 = input.next().unwrap().parse().unwrap();

    let room = n / height + if n % height == 0 {0} else {1};

    let level = n % height;
    let level = if level == 0 {height} else {level};

    let result = level * 100 + room;
    println!("{}", result);
}  