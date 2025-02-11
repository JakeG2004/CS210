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

    count_vowels(input);
}

fn count_vowels(in_string: String)
{
    // List of vowels
    let vowels = "aeiou";

    // Vowel counter
    let mut vowel_count = 0;

    // Make it lowercase
    let new_string = in_string.trim().to_lowercase();

    // Check every char for vowelness
    for c in new_string.chars()
    {
        if vowels.contains(c)
        {
            vowel_count += 1;
        }
    }

    // Print
    println!("The phrase {} has {} vowels.", in_string.trim(), vowel_count);
}
