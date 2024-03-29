fn main() {
	scope_function();
	string_builder();
	raii();
	let s = String::from("Note that the entire instance must be mutable;"); 
	references(&s);
}

fn scope_function () {
	let _n = 12;
	{
		let _d = 13;
	}
	//d here is out of scope
}

fn string_builder () {
	let mut string = String::from("Hola Mundo");
	string.push_str(" feo");
	println!("{}", string);
}

fn raii () {
	let x = 5;
	let y = x;
	println!("x = {}; y = {}", x, y);
	let s = String::from("Rust is cool");
	let s_ = s;
	//println!("{}", s); throws an error (to avoid this error see line )
	println!("{}", s_);
	error_correction();
}

fn error_correction () {
	let s = String::from("Rust isn't cool");
	let s_ = s.clone();
	println!("{}, {}", s, s_);
}

fn references (s: &String) -> usize {
	s.len()
}


