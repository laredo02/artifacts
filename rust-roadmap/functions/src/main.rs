// Main function
fn main() {
	println!("main_function");
	another_function(); another_function_with_parameters(200); println!("x + y = {}", sum(3, 5)); expr(6);
}

// function
fn another_function () {
	println!("another_function");
}

// function with parameters
fn another_function_with_parameters (x: i64) {
	println!("x(i64) = {}", x);
}

// function with return value
fn sum (x: i32, y: i32) -> i32 {
	x+y
}

// Expressions
fn expr (x: i32) -> i32 {
	let n: i32 = {
		let y = x;
		y 
	}
	n
}


