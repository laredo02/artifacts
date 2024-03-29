fn main() {
	// mutable variable
	let mut n = 4;
	println!("unmuted mutable n = {}", n);
	n = 2;
	println!("muted n = {}", n);
	
	// inmutable variable shadonwing n
	let n = 3;
	println!("inmutable n = {}", n);
	
	// constant variable it can never be muted
	const CONSTANT: u32 = 100_000_000; 
	println!("CONSTANT = {}", CONSTANT);

	// variable shadowing
	// you can shadow unmutable variables
	let x = 5;
	let x = x + 1;
	let x = x + 1;
	println!("shadowed x = {}", x);

	// specify type in order to cast variable (i32)
	let input_number: i32 = " 12 ".trim().parse().expect("Not a number!"); 
	println!("input_number = {}", input_number);

	/* Integer types in Rust:
	*
	* from -2^(n-1) to 2^(n-1)-1
	* Length  signed unsigned
	* 8-bit     i8      u8
	* 16-bit    i16     u16
	* 32-bit    i32     u32
	* 64-bit    i64     u64
	* 128-bit   i128    u128
	* arch      isize   usize
	*/
	let int: i64 = 100_000_000_000_000;
	println!("i64 integer = {}", int);

	/*
	* Dec 98_222
	* Hex 0xff
	* Oct 0o77
	* Bin 0b1111_0000
	* Byte (u8 only) b'A'
	*/

	let hex: i32 = 100_000_000;
	println!("i32 hexadecimal = {}", hex);

	/* Floating-Point types in Rust: 
	*
	* Length type
	* 32-bit f32 
	* 64-bit f64
	*/

	// E is defined as 32-bit value
	const E: f32 = 2.71;
	// default floating-point type size is double(64-bit)
	const PI: f64 = 3.14159; 
	println!("e = {}", E);
	println!("PI = {}", PI);
	let big_decimal = 0.56812398479875983;
	println!("big_decimal = {}", big_decimal);


	println!("{} + {} = {}", 5, 4, 5+4);
	println!("{} - {} = {}", 5, 4, 5-4);
	println!("{} * {} = {}", 5, 4, 5*4);
	println!("{} / {} = {}", 5, 4, 5/4);
	println!("{} % {} = {}", 5, 4, 5%4);

	/* Boolean type
	* true / false
	*/
	println!("{} && {} = {}", true, false, true&&false);	

	/* Character type
	* UTF-8
	*/
	let character = 'þ';
	println!("character = {}", character);

	/* Tuples
	*
	*/

	let tup: (u8, i16, i32) = (0xff, 0xfff, 0xffff);
	let (byte, short, int) = tup;
	println!("Tuples\nbyte = {}", byte);
	println!("short = {}", short);
	println!("int = {}", int);

	let tup_0 = tup.0;
	println!("tup_0 = {}", tup_0);

	/* Arrays
	*
	*/

	let arr: [i32; 10] = [0,1,2,3,4,5,6,7,8,9];
	println!("arr[5] = {}", arr[5]);

	print();

}

///////////////////////////////
	// Functions
///////////////////////////////

fn print () {
	println!("Hello from print fn");
}

