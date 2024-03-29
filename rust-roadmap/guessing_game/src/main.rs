use std::io;
use std::cmp::Ordering;
use rand::Rng;

fn main() {
	println!("Guess the number!");
	let random_number= rand::thread_rng()
		.gen_range(1, 101);
	let mut count = 0;
	loop {
		println!("Guess: ");
		let mut guess = String::new();
		io::stdin().read_line(&mut guess)
			.expect("Failed to read line");
		let guess: u32 = guess.trim().parse()
			.expect("Please type a number");
		println!("You guessed {}", guess);
		count+=1;
		match guess.cmp(&random_number) {
			Ordering::Less => println!("Too small"),
			Ordering::Greater => println!("Too big"),
			Ordering::Equal => {
				println!("You win!");
				println!("{} tries", count);
				break;
			}
		}
	}
}

