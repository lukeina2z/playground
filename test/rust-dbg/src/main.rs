use std::io;

fn main() {
    println!("VSCode Cargo Dbg: Guess the number!");

    println!("Please input your guess.");

    // let mut guess = String::new();

    let mut guess = "hello \t".to_string();

    io::stdin()
        .read_line(&mut guess)
        .expect("Failed to read line");

    println!("You guessed: {guess}");

    println!("2nd: Please input your guess.");

    io::stdin()
        .read_line(&mut guess)
        .expect("Failed to read line");

    println!("You guessed: {guess}");
}
