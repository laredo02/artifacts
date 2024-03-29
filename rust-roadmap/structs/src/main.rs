fn main() {
	let worker = worker_builder(String::from("Miguel"), String::from("Laredo"), String::from("miguel.laredo@mailo.org"), 16, true, 70.1, 1.85);
	println!("{:?}", worker.bmi());
	let _color = Color(255, 255, 255);
}

fn worker_builder(name: String, surname: String, email: String, age: u8, active: bool, mass: f32, height: f32) -> Worker {
	Worker {
		name,
		surname,
		email,
		age,
		active,
		mass,
		height,
	}
}

#[derive(Debug)]
struct Worker {
	name: String,
	surname: String,
	email: String,
	age: u8,
	active: bool,
	mass: f32,
	height: f32,
}

impl Worker {
	fn bmi (&self) -> f32 {
		(self.mass/(self.height*self.height))
	}
}

struct Color(u8, u8, u8);
