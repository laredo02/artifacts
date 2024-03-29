use rand::Rng;

fn main() {
	println!("is_undeage() = {}", is_underage(17));
	initialize(12);
	loop_function(20);
	while_function();
	for_function();
}

// IF statement
fn is_underage(age: u8) -> bool {
	if age > 18 {
		false
	} else if age > 90 {
		println!("Fucking old man/woman");
		false
	} else {
		true
	}
}

fn initialize (n: i32) -> i32 {
	let fin: i32 = if n>10 {
		get_random_number()
	} else {
		6
	};
	println!("init fin = {}", fin);
	fin
} 

fn get_random_number () -> i32 {
	let n: i32 = rand::thread_rng().gen_range(1, 101);
	n
}

// Loop statement
fn loop_function (iterations: i32) {
	let mut count: i32 = 0;
	loop {
		if count==iterations {
			break;
		} else {
			print!("{}", count);
		}
		count += 1;
	}
	println!();
}

// While statement
fn while_function () {
	let mut n = 100;
	while n>50 {
		n -= 1;
	}
	println!("n = {}", n);
}

// For statement
fn for_function () {
	let arr: [i32; 10] = [0,1,2,3,4,5,6,7,8,9];
	for i in arr.iter().rev() {
		print!("{}", i);
	}
	println!();
}




