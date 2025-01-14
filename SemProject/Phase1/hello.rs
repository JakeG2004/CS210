// inline Comment

/*
this is a block comment!~
*/

use std::io;

// Main func
fn main()
{
    // Get mutable string variable from the string class
    // Mutable = changeable
    let mut input = String::new();

    // Loop to ensure that input is gotten
    while input.trim().is_empty()
    {
        // Prompt for name
        println!("Please enter your name: ");

        // Get the input from user and handle error
        io::stdin().read_line(&mut input)
            .expect("Failed to read line!");
    }

    // Print
    println!("Hello, {}!", input.trim());

}
