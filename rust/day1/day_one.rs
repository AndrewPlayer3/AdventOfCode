use std::env;
use std::fs;

fn main() {
    
    let contents = fs::read_to_string("input.txt")
        .expect("Something went wrong opening the file");
    
    println!("With text:\n{}", contents);
}