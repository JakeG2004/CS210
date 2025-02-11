use std::io::{self, Write};

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
        print!("Please enter the string: ");

        // Print and flush stdio
        io::stdout().flush().expect("Failed to flush stdout");

        // Get the input from user and handle error
        io::stdin().read_line(&mut input)
            .expect("Failed to read line!");
    }

    // Bool to store result of function
    let result: bool = is_isogram(input.clone());

    // Print result
    if result
    {
        println!("\"{}\" is an isogram", input.trim());
    }

    else
    {
        println!("\"{}\" is not an isogram", input.trim());
    }
}

// Function to check if a given string is an isogram
fn is_isogram(in_string: String) -> bool
{
    // Create a vector to keep track of seen letters
    let mut seen_letters: Vec<char> = Vec::new();

    // Iterate through each character
    for c in in_string.to_lowercase().chars()
    {
        // If the character is in the vector, return false
        if seen_letters.contains(&c)
        {
            return false
        }

        // add it to the vector
        seen_letters.push(c);
    }

    // if no character, return true
    return true;
}
