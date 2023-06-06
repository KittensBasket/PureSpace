# Module collision_test

## Method `bool is_intersect(const Hitbox&, const Hitbox&)`

- ### Test **№1**
	- Target: check for collision detection
	- Type: positive
	- Input: two Hitboxes (polygon, where vertices oriented ccw), which should intersect
	- Expected output: `true`

- ### Test **№2**
	- Target: check for collision detection
	- Type: positive
	- Input: two Hitboxes (polygon, where vertices oriented ccw), which shouldn't intersect
	- Expected output: `false`

# Module shader_test

## Method `void ShaderProgram(const std::string, const std::string)`

- ### Test **№1**
	- Target: check for unexistent file terminantion
	- Type: negative
	- Input: two file strings, where at least one is invalid
	- Expected output: `std::domain_error` exception

- ### Test **№2**
	- Target: check for shader program compile errors
	- Type: negative
	- Input: two file strings, where each is an existing file
	- Expected output: `ShaderProgramError` exception

- ### Test **№3**
	- Target: check for correct shader program compilation
	- Type: positive
	- Input: two file strings, where each is an existing file
	- Expected outout: none
